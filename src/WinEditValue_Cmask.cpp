#include "win.h"

CWinEditValue_Cmask::CWinEditValue_Cmask()
{
}

CWinEditValue_Cmask::~CWinEditValue_Cmask()
{
}

bool CWinEditValue_Cmask::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// ���ڡ����ʤ�⤦���ä��粼����
								// ���ڡ����ǽ����ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Cmask::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// ���ڡ����ʤ�⤦���ä���夲��
								// ���ڡ����ǻϤޤ�ꥹ�Ȥ��������Τ����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Cmask::onkeypress_right()
{
	// �ޥ���ȿž
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
	m_return = true;	// ���äƤ���
	return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
}
bool CWinEditValue_Cmask::onkeypress_left()
{
	// �ޥ���ȿž
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
	m_return = true;	// ���äƤ���
	return false;	// �����롼�פ�λ���ơ����Υ�����Ǻ�ɽ������
}
bool CWinEditValue_Cmask::onkeypress_ok()
{
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Cmask::onkeypress_cancel()
{
	m_return = false;	// ID
	return m_disable_cansel;
}

