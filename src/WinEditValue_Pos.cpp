#include "win.h"

CWinEditValue_Pos::CWinEditValue_Pos()
{
}

CWinEditValue_Pos::~CWinEditValue_Pos()
{
}

bool CWinEditValue_Pos::onkeypress_down()
{
	if (m_cur.y < 5)
	{
		if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// カーソル下げる
		if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// スペーサならもういっちょ下げる
									// スペーサで終わるリストだと落ちるので注意
	}
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Pos::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// スペーサならもういっちょ上げる
								// スペーサで始まるリストだと落ちるので注意
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Pos::onkeypress_right()
{
	if (m_cur.y == 1 || m_cur.y == 2)
	{	// タイルID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;	// ID（左右はループする）
		m_return = m_cur.y;
		return false;	// キーループを終了して、次のタイルで再表示する
	}
	m_return = 0;
	return true;	// キーループ継続
}
bool CWinEditValue_Pos::onkeypress_left()
{
	if (m_cur.y == 1 || m_cur.y == 2)
	{	// タイルID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;	// ID（左右はループする）
		m_return = m_cur.y;
		return false;	// キーループを終了して、次のタイルで再表示する
	}
	m_return = 0;
	return true;	// キーループ継続
}
bool CWinEditValue_Pos::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] != TT_SPC)
	{
		CWinGetPath*	nw_getpath;

		nw_getpath = new CWinGetPath;
		nw_getpath->settitle(m_name[m_cur.y]);
		m_value[m_cur.y] = nw_getpath->startdialog(true);
		decode(&m_value[m_cur.y], m_ptr[m_cur.y], m_my_tt[m_cur.y]);
		delete(nw_getpath);
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);

		if (m_cur.y == 1 || m_cur.y == 2)
		{
			m_return = m_cur.y;
			return false;	// キーループを終了して、次のタイルで再表示する
		}
	}
	return true;	// キーループ継続
}
bool CWinEditValue_Pos::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

