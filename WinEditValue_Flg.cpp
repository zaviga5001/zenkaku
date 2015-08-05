#include "win.h"

CWinEditValue_Flg::CWinEditValue_Flg(CData* data)
{
	m_data = data;
}

CWinEditValue_Flg::~CWinEditValue_Flg()
{
}

bool CWinEditValue_Flg::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// カーソル下げる
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Flg::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Flg::onkeypress_right()
{
	if (m_cur.y == 0)
	{       // ID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;      // ID（左右はループする）
		m_return = false;       // これがfalseなら帰ってくる
		return false;           // キーループ一旦終了
	}
	return true;	// キーループ継続
}
bool CWinEditValue_Flg::onkeypress_left()
{
	if (m_cur.y == 0)
	{       // ID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;      // ID（左右はループする）
		m_return = false;       // これがfalseなら帰ってくる
		return false;           // キーループ一旦終了
	}
	return true;	// キーループ継続
}
bool CWinEditValue_Flg::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] != TT_SPC)
	{
		CWinGetPath*    nw_getpath;

		nw_getpath = new CWinGetPath;
		nw_getpath->settitle(m_name[m_cur.y]);
		m_value[m_cur.y] = nw_getpath->startdialog(true);
		decode(&m_value[m_cur.y], m_ptr[m_cur.y], m_my_tt[m_cur.y]);
		delete(nw_getpath);
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
	}
	m_return = false;       // これがfalseなら帰ってくる
	return false;           // キーループ一旦終了
}

bool CWinEditValue_Flg::onkeypress_cancel()
{
	m_return = true;	// 二度とここへは帰らない。。。
	return false;		// キーループ終了
}

