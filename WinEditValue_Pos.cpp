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
		if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
		if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// ���ڡ����ʤ�⤦���ä��粼����
									// ���ڡ����ǽ����ꥹ�Ȥ��������Τ����
	}
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Pos::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// ���ڡ����ʤ�⤦���ä���夲��
								// ���ڡ����ǻϤޤ�ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Pos::onkeypress_right()
{
	if (m_cur.y == 1 || m_cur.y == 2)
	{	// ������ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;	// ID�ʺ����ϥ롼�פ����
		m_return = m_cur.y;
		return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
	}
	m_return = 0;
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Pos::onkeypress_left()
{
	if (m_cur.y == 1 || m_cur.y == 2)
	{	// ������ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;	// ID�ʺ����ϥ롼�פ����
		m_return = m_cur.y;
		return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
	}
	m_return = 0;
	return true;	// �����롼�׷�³
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
			return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
		}
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Pos::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

