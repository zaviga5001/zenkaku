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
bool CTitle::select_game(CData* data, CConfig* config, CFile* file)
{
	char	tmp_buf[10];
	std::string	sname;
	DIR*	dir;
	dirent*	dent;
	std::string	dentcs;
	ScnList	tmp_scn;

	CWinSelect1Line*	nw_select1line;
	nw_select1line		= new CWinSelect1Line;

	nw_select1line->setsize(0, 0); // 最大
	nw_select1line->movewin(5, 0); // 中央
	nw_select1line->settitle(std::string(msg[MY_MSG_SYS_SEL_SCENARIO].msg));


	if (config->m_mode == 0)
	{	// Game
		// シナリオとシナリオIDをリストアップする
		std::string path = zenkaku_home + "/scenario/";
		dir = opendir(path.c_str());
		for (int i = 1; ; )
		{
			dent = readdir(dir);
			if (dent == NULL)	break;
			dentcs = dent->d_name;
			if (dentcs == "." || dentcs == "..")	continue;

			tmp_scn = file->read_scenario_list(path + dentcs);
			tmp_scn.id = atoi(dentcs.c_str());
			if (tmp_scn.id != 0)
			{
				m_scnlist.push_back(tmp_scn);
				nw_select1line->push(tmp_scn.name.c_str(), i);
				i++;
			}
		}
		closedir(dir);
	}
	else
	{	// Editor
		nw_select1line->push("マップエディタ", 1);
		nw_select1line->push("イベントエディタ", 2);
		nw_select1line->push("マイキャラエディタ", 3);
		nw_select1line->push("敵キャラエディタ", 4);
		nw_select1line->push("パーティエディタ", 5);
		nw_select1line->push("パーティグループエディタ", 6);
		nw_select1line->push("アイテムエディタ", 7);
		nw_select1line->push("メッセージエディタ", 8);
		nw_select1line->push("シナリオエディタ", 9);
	}

	nw_select1line->m_disable_cansel = true;

	while(1)
	{
		// シナリオ一覧を表示する
		data->m_scn_index = nw_select1line->startwin(true);

		if (config->m_mode == 0)
		{	// Game
			// シナリオの内容を表示する
			CWinSelect1Item* nw_select1item;
			nw_select1item = new CWinSelect1Item;
			nw_select1item->setsize(38, 22);
			nw_select1item->movewin(5, 0);  // 中央
			nw_select1item->m_msg = m_scnlist[data->m_scn_index - 1].doc;
			nw_select1item->m_split = 19;
			nw_select1item->m_wpos.y = 20;
			nw_select1item->settitle(m_scnlist[data->m_scn_index - 1].name);
			nw_select1item->push(msg[MY_MSG_SYS_YES].msg, 1);
			nw_select1item->push(msg[MY_MSG_SYS_NO].msg,  2);
			int tmp_ret = nw_select1item->startwin(true);
			delete(nw_select1item);
			if (tmp_ret == 1)	break;
		}
		else
		{	// Editor
			break;
		}
	}

	// ポインタ解放
	delete(nw_select1line);

	refresh();
	return true;
}




