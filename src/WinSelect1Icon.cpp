#include "win.h"

CWinSelect1Icon::CWinSelect1Icon()
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_maxwidth = 0;
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.x  = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;
	m_winy   = 0;
	m_winw   = 5;
	m_winh   = 10;
	m_disable_cansel = false;
	m_cols   = 10;
	setsize(0, 0);		// Windowサイズ（デフォルト）
	movewin(5, 2);		// Window位置（デフォルト）（中央、マージン１）
}

CWinSelect1Icon::~CWinSelect1Icon()
{
}

int CWinSelect1Icon::drawwin()
{
	seticon(m_wpos, &m_cur, &m_dpos, m_list, m_cp, m_cols);
	return true;
}

void CWinSelect1Icon::push(const std::string str, const int id)
{
	push(str, m_cpair, id);
}
void CWinSelect1Icon::push(const std::string str, const int cpair, const int id)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.length())
	m_maxwidth = str.length() / 2;
}

bool CWinSelect1Icon::onkeypress_left()
{
	if (m_cur.x > 0)	m_cur.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Icon::onkeypress_down()
{
	if (m_cur.y < m_list.size() / m_cols - 1)      m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Icon::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Icon::onkeypress_right()
{
	if (m_cur.x < m_cols - 1)      m_cur.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Icon::onkeypress_ok()
{
	m_return = m_index[m_cur.x];
	return false;	// キーループ終了
}
bool CWinSelect1Icon::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

