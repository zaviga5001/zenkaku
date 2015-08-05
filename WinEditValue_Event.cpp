#include "win.h"

CWinEditValue_Event::CWinEditValue_Event()
{
}

CWinEditValue_Event::~CWinEditValue_Event()
{
}

bool CWinEditValue_Event::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// カーソル下げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// スペーサならもういっちょ下げる
								// スペーサで終わるリストだと落ちるので注意
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Event::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// スペーサならもういっちょ上げる
								// スペーサで始まるリストだと落ちるので注意
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Event::onkeypress_right()
{
	if (m_cur.y == 0)
	{	// ID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;	// ID（左右はループする）
		m_return = 1;
		return false;	// キーループを終了して、次のIDで再表示する
	}
	m_return = 0;
	return true;	// キーループ継続
}
bool CWinEditValue_Event::onkeypress_left()
{
	if (m_cur.y == 0)
	{	// ID入れ換え
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;	// ID（左右はループする）
		m_return = 1;
		return false;	// キーループを終了して、次のIDで再表示する
	}
	m_return = 0;
	return true;	// キーループ継続
}
bool CWinEditValue_Event::onkeypress_ok()
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

		if (m_cur.y == 0)
		{
			m_return = 1;
			return false;	// キーループを終了して、次のIDで再表示する
		}
	}
	return true;	// キーループ継続
}
bool CWinEditValue_Event::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

