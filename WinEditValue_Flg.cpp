#include "win.h"

CWinEditValue_Flg::CWinEditValue_Flg(CData* data)
{
	m_data = data;
}

CWinEditValue_Flg::~CWinEditValue_Flg()
{
}

bool CWinEditValue_Flg::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Flg::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Flg::onkeypress_right()
{
	if (m_cur.y == 0)
	{       // ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] + 1;      // ID�ʺ����ϥ롼�פ����
		m_return = false;       // ���줬false�ʤ鵢�äƤ���
		return false;           // �����롼�װ�ö��λ
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Flg::onkeypress_left()
{
	if (m_cur.y == 0)
	{       // ID���촹��
		*(int*)m_ptr[m_cur.y] = *(int*)m_ptr[m_cur.y] - 1;      // ID�ʺ����ϥ롼�פ����
		m_return = false;       // ���줬false�ʤ鵢�äƤ���
		return false;           // �����롼�װ�ö��λ
	}
	return true;	// �����롼�׷�³
}
bool CWinEditValue_Flg::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] != TT_SPC)
	{
		CWinGetPath*    nw_getpath;

		nw_getpath = new CWinGetPath;
		nw_getpath->settitle(m_name[m_cur.y]);
		m_value[m_cur.y] = nw_getpath->startdialog(true);
		decode(&m_value[m_cur.y], m_ptr[m_cur.y], m_my_tt[m_cur.y]);
		delete(nw_getpath);
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
	}
	m_return = false;       // ���줬false�ʤ鵢�äƤ���
	return false;           // �����롼�װ�ö��λ
}

bool CWinEditValue_Flg::onkeypress_cancel()
{
	m_return = true;	// ���٤Ȥ����ؤϵ���ʤ�������
	return false;		// �����롼�׽�λ
}

