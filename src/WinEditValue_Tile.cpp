#include "win.h"

CWinEditValue_Tile::CWinEditValue_Tile()
{
}

CWinEditValue_Tile::~CWinEditValue_Tile()
{
}

bool CWinEditValue_Tile::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// ���ڡ����ʤ�⤦���ä��粼����
								// ���ڡ����ǽ����ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Tile::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// ���ڡ����ʤ�⤦���ä���夲��
								// ���ڡ����ǻϤޤ�ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Tile::onkeypress_right()
{
	if (m_cur.y == 0)
	{	// ������ID���촹��
		*(int*)m_ptr[m_cur.y] += 1;	// ID�ʺ����ϥ롼�פ����
		m_return = true;	// ���äƤ���
		return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Tile::onkeypress_left()
{
	if (m_cur.y == 0)
	{	// ������ID���촹��
		*(int*)m_ptr[m_cur.y] -= 1;	// ID�ʺ����ϥ롼�פ����
		m_return = true;	// ���äƤ���
		return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Tile::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] != TT_SPC)
	{
		if (m_cur.y != 0)
		{
			CWinGetPath*	nw_getpath;

			nw_getpath = new CWinGetPath;
			nw_getpath->settitle(m_name[m_cur.y]);
			m_value[m_cur.y] = nw_getpath->startdialog(true);
			decode(&m_value[m_cur.y], m_ptr[m_cur.y], m_my_tt[m_cur.y]);
			delete(nw_getpath);

			if (m_cur.y == 2 || m_cur.y == 3)
			{
				m_cp[m_cur.y] = getcpair(*(char*)m_ptr[m_cur.y], 0);
				m_cp[1] = getcpair(*(char*)m_ptr[2], *(char*)m_ptr[3]);
			}
			if (m_cur.y == 12 || m_cur.y == 13)
			{
				m_cp[m_cur.y] = getcpair(*(char*)m_ptr[m_cur.y], 0);
				m_cp[11] = getcpair(*(char*)m_ptr[12], *(char*)m_ptr[13]);
			}

			drawwin();
			touchwin(m_this);
			wrefresh(m_this);
		}
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Tile::onkeypress_cancel()
{
	m_return = false;	// ID
	return m_disable_cansel;
}

