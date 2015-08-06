#include "win.h"

CWinSelect1Item::CWinSelect1Item()
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_maxwidth = 0;
	m_dpos.x = 0;
	m_cur.x  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;
	m_winy   = 0;
	m_winw   = 5;
	m_winh   = 10;
	m_split  = 0;
	m_disable_cansel = false;
	setsize(10, 10);	// Windowサイズ（デフォルト）
	movewin(5, 2);		// Window位置（デフォルト）（中央、マージン１）
}

CWinSelect1Item::~CWinSelect1Item()
{
}

int CWinSelect1Item::drawwin()
{
	if (m_msg.Len() > 0)	setmessage_n(1, 1, m_msg);
	if (m_split > 0)	splitwin(m_split);
	setselect(m_wpos.x, m_wpos.y, &m_cur.x, &m_dpos.x, m_list, m_cp);
	return true;
}

void CWinSelect1Item::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinSelect1Item::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}

bool CWinSelect1Item::onkeypress_left()
{
	if (m_cur.x > 0)	m_cur.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Item::onkeypress_down()
{
	return true;	// キーループ継続
}
bool CWinSelect1Item::onkeypress_up()
{
	return true;	// キーループ継続
}
bool CWinSelect1Item::onkeypress_right()
{
	if (m_cur.x < m_list.size() - 1)      m_cur.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinSelect1Item::onkeypress_ok()
{
	m_return = m_index[m_cur.x];
	return false;	// キーループ終了
}
bool CWinSelect1Item::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

