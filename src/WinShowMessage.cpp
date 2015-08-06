#include "win.h"

CWinShowMessage::CWinShowMessage()
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_maxwidth = 0;
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.x  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;
	m_winy   = 0;
	m_winw   = 5;
	m_winh   = 10;
	m_disable_cansel = false;
	setsize(10, 10);	// Windowサイズ（デフォルト）
	movewin(5, 2);		// Window位置（デフォルト）（中央、マージン１）

	m_pause.push_back("続きを読む");
}

CWinShowMessage::~CWinShowMessage()
{
}

int CWinShowMessage::drawwin()
{
	m_split = m_winh - 3;
	m_drawarea.x = m_winw - 2;
	m_drawarea.y = m_winh - 4;
	splitwin(m_split);

	int dpos = 0, len = 0;
	for (int i = 0; i < m_msg.Len(); )
	{
		if (m_msg[i] == 'k')
		{	// キー入力待ち記号
			i++;
			continue;
		}
		if (m_msg[i] == 'p' || m_msg[i] == 'n')
		{	// 改ページ記号 改行記号
			i++;
			m_msgvct.push_back(m_msg.Sub(dpos, i));
			dpos = i;
			len = 0;
			continue
		}
		if (len >= m_drawarea.x)
		{	// 表示エリアの右端まで到達
			i++;
			m_msgvct.push_back(m_msg.Sub(dpos, i));
			dpos = i;
			len = 0;
			continue
		}
		if (m_msg[i] == 't')
		{	// ウェイトタイム記号
			i += 4;
			continue;
		}
		if (m_msg[i] == 'c')
		{	// 色指定記号
			i += 3;
			continue;
		}

		len += 2;
		i   += 2;
	}
	if (dpos < i)	m_msgvct.push_back(m_msg.Sub(dpos, i));

	setmessage_n(1, 1, m_msg);
	return true;
}

void CWinShowMessage::drawmsg()
{
	int dpos = 0;
	for (int i = 0; i < m_msgvct.size(); i++)
	{
		// スクロールポジション調整
		if (m_type == TYPE_SCROLL && i < m_dpos.y)	continue;

		for (int j = 0; j < m_msgvct[i].Len(); j++)
		{
			if (m_msgvct[i][j] == 'k')
			{	// キー入力待ち記号
				if (m_type == TYPE_SCROLL)
				{
					j++;
					continue;
				}
				else
				{
					setselect(m_wpos.x, m_wpos.y, &m_cur.x, &m_dpos.x, m_pause, m_cp);
					keyloop();
					j++;
					continue;
				}
			}
			if (m_msgvct[i][j] == 'p')
			{	// 改ページ記号
				if (m_type == TYPE_SCROLL)
				{
					j++;
					continue;
				}
				else
				{
					setselect(m_wpos.x, m_wpos.y, &m_cur.x, &m_dpos.x, m_pause, m_cp);
					keyloop();
					j++;
					continue;
				}
			}
			if (m_msgvct[i][j] == 'n')
			{	// 改行記号
			}
			if (len >= m_drawarea.x)
			{	// 表示エリアの右端まで到達
				i++;
				m_msgvct.push_back(m_msg.Sub(dpos, i));
				dpos = i;
				len = 0;
				continue
			}
			if (m_msg[i] == 't')
			{	// ウェイトタイム記号
				i += 4;
				continue;
			}
			if (m_msg[i] == 'c')
			{	// 色指定記号
				i += 3;
				continue;
			}

			len += 2;
			i   += 2;
		}
	}

	setselect(m_wpos.x, m_wpos.y, &m_cur.x, &m_dpos.x, m_list, m_cp);
	return true;
}

void CWinShowMessage::drawitem()
{
	setselect(m_wpos.x, m_wpos.y, &m_cur.x, &m_dpos.x, m_list, m_cp);
}

void CWinShowMessage::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinShowMessage::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}

bool CWinShowMessage::onkeypress_left()
{
	if (m_cur.x > 0)	m_cur.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShowMessage::onkeypress_down()
{
	return true;	// キーループ継続
}
bool CWinShowMessage::onkeypress_up()
{
	return true;	// キーループ継続
}
bool CWinShowMessage::onkeypress_right()
{
	if (m_cur.x < m_list.size() - 1)      m_cur.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShowMessage::onkeypress_ok()
{
	m_return = m_index[m_cur.x];
	return false;	// キーループ終了
}
bool CWinShowMessage::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

