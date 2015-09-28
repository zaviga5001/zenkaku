#include "win.h"

CWinSelect1Line::CWinSelect1Line()
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_maxwidth = 0;
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;
	m_winy   = 0;
	m_winw   = 5;
	m_winh   = 10;
	m_disable_cansel = false;
	setsize(10, 10);	// Windowサイズ（デフォルト）
	movewin(5, 2);		// Window位置（デフォルト）（中央、マージン１）
}

CWinSelect1Line::~CWinSelect1Line()
{
}

int CWinSelect1Line::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinSelect1Line::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinSelect1Line::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.length())
		m_maxwidth = str.length() / 2;
}

bool CWinSelect1Line::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Line::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;	// カーソル下げる
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Line::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Line::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Line::onkeypress_ok()
{
	m_return = m_index[m_cur.y];
	return false;	// キーループ終了
}
bool CWinSelect1Line::onkeypress_cancel()
{
	m_return = -1;
	return m_disable_cansel;
}

