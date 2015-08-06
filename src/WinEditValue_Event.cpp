#include "win.h"

CWinEditValue_Event::CWinEditValue_Event()
{
}

CWinEditValue_Event::~CWinEditValue_Event()
{
}

bool CWinEditValue_Event::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// ���ڡ����ʤ�⤦���ä��粼����
								// ���ڡ����ǽ����ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Event::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// ���ڡ����ʤ�⤦���ä���夲��
								// ���ڡ����ǻϤޤ�ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Event::onkeypress_right()
{
	if (m_cur.y == 0)
	{	// ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;	// ID�ʺ����ϥ롼�פ����
		m_return = 1;
		return false;	// �����롼�פ�λ���ơ�����ID�Ǻ�ɽ������
	}
	m_return = 0;
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Event::onkeypress_left()
{
	if (m_cur.y == 0)
	{	// ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;	// ID�ʺ����ϥ롼�פ����
		m_return = 1;
		return false;	// �����롼�פ�λ���ơ�����ID�Ǻ�ɽ������
	}
	m_return = 0;
	return true;	// �����롼�׷�³
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
			return false;	// �����롼�פ�λ���ơ�����ID�Ǻ�ɽ������
		}
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Event::onkeypress_cancel()
{
	m_return = 0;
	return m_disable_cansel;
}

