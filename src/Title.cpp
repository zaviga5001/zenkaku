#include "Title.h"

CTitle::CTitle()
{
}

CTitle::~CTitle()
{
}

// タイトル画面を表示
//
bool CTitle::disp_title(CConfig* config)
{
	if (config->m_title == false)	return true;

	CWinTitle*	title;
	title = new CWinTitle;
	title->startwin(true);
	delete(title);
	refresh();
	return true;
}

// シナリオを選択する
//
bool CTitle::select_game(CConfig* config)
{
	char	tmp_buf[10];
	CString	sname;
	DIR*	dir;
	dirent*	dent;
	CString	dentcs;
	ScnList	tmp_scn;

	CFile*			scenario;
	scenario		= new CFile;
	CWinSelect1Line*	nw_select1line;
	nw_select1line		= new CWinSelect1Line;

	nw_select1line->setsize(40, 28);
	nw_select1line->settitle(CString(msg[MY_MSG_SYS_SEL_SCENARIO].msg));

	// シナリオとシナリオIDをリストアップする
	CString path = zenkaku_home + "/scenario/";
	dir = opendir(path);

	for (int i = 1; ; )
	{
		dent = readdir(dir);
		if (dent == NULL)	break;
		dentcs = dent->d_name;
		if (dentcs == "." || dentcs == "..")	continue;

		tmp_scn = scenario->read_scenario_list(path + dentcs);
		tmp_scn.id = atoi((LPCSTR)dentcs);
		if (tmp_scn.id != 0)
		{
			m_scnlist.push_back(tmp_scn);
			nw_select1line->push(tmp_scn.name, i);
			i++;
		}
	}
	closedir(dir);

	nw_select1line->m_disable_cansel = true;

	while(1)
	{
		config->m_scenario = nw_select1line->startwin(true);

		CWinSelect1Item* nw_select1item;
		nw_select1item = new CWinSelect1Item;
		nw_select1item->setsize(40, 26);
		nw_select1item->m_msg = m_scnlist[config->m_scenario - 1].doc;
		nw_select1item->m_split = 23;
		nw_select1item->m_wpos.y = 24;
		nw_select1item->settitle(m_scnlist[config->m_scenario - 1].name);
		nw_select1item->push(msg[MY_MSG_SYS_YES].msg, 1);
		nw_select1item->push(msg[MY_MSG_SYS_NO].msg,  2);
		int tmp_ret = nw_select1item->startwin(true);
		delete(nw_select1item);
		
		if (tmp_ret == 1)	break;
	}

	// ポインタ解放
	delete(nw_select1line);
	delete(scenario);

	refresh();
	return true;
}




