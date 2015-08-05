#include "win.h"

CWinMessageEditor::CWinMessageEditor(CConfig* config)
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;		// 窓の表示開始位置（常に0）
	m_winy   = 0;		// 窓の表示開始位置（常に0）
	m_winw   = COLS / 2;	// 窓の幅（全角でカウント）
	m_winh   = LINES;	// 窓の高さ
	m_maxwidth = 0;		// 文字列の最大幅

	m_data = new CData;

	m_data->m_messnum = 0;

	// ここでシナリオを読み込め

	// メッセージ読み込み
	read_mess();

	for (int i = 0; i < m_data->m_messnum; i++)
	{
		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", i);
		
		push(CString(tmp_buf) + ":" + m_data->m_mess[i].msg, i);
	}
	push("新規作成", m_data->m_messnum);
}

CWinMessageEditor::~CWinMessageEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinMessageEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinMessageEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinMessageEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinMessageEditor::change(const CString str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	m_maxwidth = 0;
	for (int i = 0; i < m_list[i].Len(); i++)
	{
		if (adjx(m_maxwidth) < m_list[i].Len())
			m_maxwidth = m_list[i].Len() / 2;
	}
}


// メッセージファイル読み込み
void CWinMessageEditor::read_mess()
{
	CFile*	fp;
	fp = new CFile;

	fp->read_mess(m_data);

	delete(fp);
}

// メッセージファイル書き込み
void CWinMessageEditor::write_mess()
{
	CFile*	fp;
	fp = new CFile;

	fp->write_mess(m_data);

	delete(fp);
}

void CWinMessageEditor::keyloop()
{
	timeout(-1);    // キー入力で待つ

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
			case MYKEY_OK:
				if (!onkeypress_ok())		return;
				break;
			case MYKEY_CANCEL:
				if (!onkeypress_cancel())	return;
				break;
			case 'd':
			{
				CWinMsg* nw_winmsg;
				nw_winmsg = new CWinMsg;
				nw_winmsg->setsize(20, 5);
				nw_winmsg->m_msg = m_data->m_mess[m_cur.y].msg;
				int tmp_ret = nw_winmsg->startwin(true);
				delete(nw_winmsg);
				drawwin();
				touchwin(m_this);
				wrefresh(m_this);

				continue;
				break;
			}
			default:
				continue;
				break;
		}
	}
}

bool CWinMessageEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMessageEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMessageEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMessageEditor::onkeypress_right()
{
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 2 < m_maxwidth - m_dpos.x)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMessageEditor::onkeypress_ok()
{
	MessData*	tmp_ms;
	MessData	tmp_mso;
	char tmp_buf[6];

	CWinGetPath*	nw_getpath;

	// カーソル位置のメッセージ読み込み
	if (m_cur.y == m_data->m_messnum)
	{ // 新規追加
		tmp_ms = &tmp_mso;
	}
	else
	{
		tmp_ms = &m_data->m_mess[m_cur.y];
	}

	for ( ; ; )
	{
		// ポインタセット
		nw_getpath = new CWinGetPath;
		nw_getpath->setsize(400, 200);

		sprintf(tmp_buf, "%06d", m_cur.y);
		nw_getpath->settitle(CString(tmp_buf));

		tmp_ms->msg = nw_getpath->startdialog(true);
		delete(nw_getpath);

		
		// アイテム書き出し
		CWinSelect1Item* nw_select1item;
		nw_select1item = new CWinSelect1Item;
		nw_select1item->setsize(20, 5);
		nw_select1item->m_msg = msg[MY_MSG_SYS_SAVE_YN].msg;
		nw_select1item->m_split = 2;
		nw_select1item->m_wpos.y = 3;
		nw_select1item->push(msg[MY_MSG_SYS_YES].msg, 1);
		nw_select1item->push(msg[MY_MSG_SYS_NO].msg,  2);
		int tmp_ret = nw_select1item->startwin(true);
		delete(nw_select1item);

		if (tmp_ret == 0)
		{
			continue;
		}
		else if (tmp_ret == 1)
		{
			sprintf(tmp_buf, "%05d", m_cur.y);
			change(CString(tmp_buf) + ":" + tmp_ms->msg, m_cur.y, m_cur.y);
			if (m_cur.y == m_data->m_messnum)
			{ // 新規追加だった
				m_data->m_messnum++;
				push("新規作成", m_data->m_messnum);

				m_data->m_mess.push_back(*tmp_ms);
			}
			write_mess();
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinMessageEditor::onkeypress_cancel()
{
	return false;	// 終了
}




void CWinMessageEditor::warn(CString tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = tmp_msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}
void CWinMessageEditor::warn(enum msg_id tmp_msg)
{
	warn(msg[tmp_msg].msg);
}
void CWinMessageEditor::warn(CString tmp_msg, int num)
{
	char		tmp_str[128];
	sprintf(tmp_str, "%d", num);
	warn(tmp_msg + ":" + CString(tmp_str));
}



