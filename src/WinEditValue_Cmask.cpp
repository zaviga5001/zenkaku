#include "win.h"

CWinEditValue_Cmask::CWinEditValue_Cmask()
{
}

CWinEditValue_Cmask::~CWinEditValue_Cmask()
{
}

bool CWinEditValue_Cmask::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// カーソル下げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// スペーサならもういっちょ下げる
								// スペーサで終わるリストだと落ちるので注意
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Cmask::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// スペーサならもういっちょ上げる
								// スペーサで始まるリストだと落ちるので注意
	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue_Cmask::onkeypress_right()
{
	// マスク反転
	if (m_cur.y == 0 ||
	    m_cur.y == 1 ||
	    m_cur.y == 2 ||
	    m_cur.y == 4   )
	{
		*(int*)m_ptr[m_cur.y] = ~ *(int*)m_ptr[m_cur.y];
	}
	else
	{
		*(char*)m_ptr[m_cur.y] = ~ *(char*)m_ptr[m_cur.y];
	}
	m_return = true;	// 帰ってくる
	return false;	// キーループを終了して、次のタイルで再表示する
}
bool CWinEditValue_Cmask::onkeypress_left()
{
	// マスク反転
	if (m_cur.y == 0 ||
	    m_cur.y == 1 ||
	    m_cur.y == 2 ||
	    m_cur.y == 4   )
	{
		*(int*)m_ptr[m_cur.y] = ~ *(int*)m_ptr[m_cur.y];
	}
	else
	{
		*(char*)m_ptr[m_cur.y] = ~ *(char*)m_ptr[m_cur.y];
	}
	m_return = true;	// 帰ってくる
	return false;	// キーループを終了して、次のタイルで再表示する
}
bool CWinEditValue_Cmask::onkeypress_ok()
{
	return true;	// キーループ継続
}
bool CWinEditValue_Cmask::onkeypress_cancel()
{
	m_return = false;	// ID
	return m_disable_cansel;
}

