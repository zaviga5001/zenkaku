#include "win.h"

CWinScenarioEditor::CWinScenarioEditor(CConfig* config)
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_winx   = 0;		// 窓の表示開始位置（常に0）
	m_winy   = 0;		// 窓の表示開始位置（常に0）
	m_winw   = COLS / 2;	// 窓の幅（全角でカウント）
	m_winh   = LINES;	// 窓の高さ

	m_data = new CData;
}

CWinScenarioEditor::~CWinScenarioEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinScenarioEditor::drawwin()
{
	// 画面再描画
	wrefresh(m_this);
	return true;
}


void CWinScenarioEditor::keyloop()
{
	timeout(-1);    // キー入力で待つ

	CWinMsg*		nw_msg;
	CWinGetPath*		nw_getpath;
	CFile*			mycharfp;

	for( ; ; )
	{
		int ch = wgetch(m_this);
		switch(ch)
		{
			case MYKEY_LEFT:
				if (!onkeypress_left())		return;
				break;
			case MYKEY_DOWN:
				if (!onkeypress_down())		return;
				break;
			case MYKEY_UP:
				if (!onkeypress_up())		return;
				break;
			case MYKEY_RIGHT:
				if (!onkeypress_right())	return;
				break;
			case 'z':
				return;
				break;
			default:
				continue;
				break;
		}
	}
}

// マイキャラファイルから読み込み
int CWinScenarioEditor::read_mychar()
{
	CFile*	mycharfp;
	mycharfp = new CFile;

//	for (int i = 1; ; i++)
//	{
//		char	tmp_str[10];
//		sprintf(tmp_str, "%d", i);
//		m_path = "mychar/" + tmp_str + ".bin";
//	}

	delete(mycharfp);

	return 0;
}

void CWinScenarioEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}

bool CWinScenarioEditor::onkeypress_left()
{
	drawwin();
	return true;	// キーループ継続
}
bool CWinScenarioEditor::onkeypress_down()
{
	drawwin();
	return true;	// キーループ継続
}
bool CWinScenarioEditor::onkeypress_up()
{
	drawwin();
	return true;	// キーループ継続
}
bool CWinScenarioEditor::onkeypress_right()
{
	drawwin();
	return true;	// キーループ継続
}



