#include "win.h"

CWinSelect1Line::CWinSelect1Line()
{
	// �ʲ��ϥǥե�����ͤǤ���
	// ���֥������Ⱥ������Ĵ�����Ƥ���������
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
	setsize(10, 10);	// Window�������ʥǥե���ȡ�
	movewin(5, 2);		// Window���֡ʥǥե���ȡˡ�������ޡ����󣱡�
}

CWinSelect1Line::~CWinSelect1Line()
{
}

int CWinSelect1Line::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinSelect1Line::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinSelect1Line::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}

bool CWinSelect1Line::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinSelect1Line::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;	// �������벼����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinSelect1Line::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinSelect1Line::onkeypress_right()
{
	// �ġ��Υ饤��α�ü�ޤǥ�������
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// ����Ĺ�饤��α�ü�ޤǥ�������
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinSelect1Line::onkeypress_ok()
{
	m_return = m_index[m_cur.y];
	return false;	// �����롼�׽�λ
}
bool CWinSelect1Line::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

