#include "win.h"

CWinEditValue::CWinEditValue()
{
	// �ʲ��ϥǥե�����ͤǤ���
	// ���֥������Ⱥ������Ĵ�����Ƥ���������
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
	setsize(0, 0);		// Window�������ʥǥե���ȡ�
	movewin(5, 1);		// Window���֡ʥǥե���ȡˡ�������ޡ����󣱡�
}

CWinEditValue::~CWinEditValue()
{
}

int CWinEditValue::drawwin()
{
	setedit(m_wpos.x, m_wpos.y, &m_cur.y, &m_dpos.y, m_name, m_value, m_cp);
	return true;
}

void CWinEditValue::push(const CString str, void * ptr, const int chr, const int num)
{
	push(str, ptr, chr, num, m_cpair);
}
void CWinEditValue::push(const CString str, void * ptr, const int chr, const int num, const int cpair)
{
	m_name.push_back(str);
	m_ptr.push_back(ptr);
	m_my_tt.push_back(chr);
	m_size.push_back(num);
	m_value.push_back(encode(ptr, chr, num));
	m_cp.push_back(cpair);
}

CString CWinEditValue::encode(void * ptr, const int chr, const int num)
{
	char	tmp_buf[256];

	switch(chr)
	{
		case TT_CST:
			return (*(CString*)ptr);
			break;
		case TT_SPC:
			tmp_buf[0] = 0;
			break;
		case TT_BYT:
			sprintf(tmp_buf, "%d", *(BYTE*)ptr);
			break;
		case TT_CHR:
			sprintf(tmp_buf, "%d", *(char*)ptr);
			break;
		case TT_STR:
			memcpy(tmp_buf, (char*)ptr, num);
			tmp_buf[num] = 0;
			break;
		case TT_INT:
			sprintf(tmp_buf, "%d", *(int*)ptr);
			break;
		case TT_UINT:
			sprintf(tmp_buf, "%u", *(int*)ptr);
			break;
		case TT_SHT:
			sprintf(tmp_buf, "%d", *(short*)ptr);
			break;
		case TT_LNG:
			sprintf(tmp_buf, "%ld", *(long*)ptr);
			break;
		case TT_VCT:
			tmp_buf[0] = ' ';
			tmp_buf[1] = ' ';
			tmp_buf[2] = 0;
			break;
		default:
			break;
	}
	return (CString(tmp_buf));
}

void CWinEditValue::decode(CString* str, void *ptr, const int chr)
{
	switch(chr)
	{
		case TT_CST:
			*(CString*)ptr = *(CString*)str;
			break;
		case TT_BYT:
			*(BYTE*)ptr = atoi(LPCSTR(*str));
			break;
		case TT_CHR:
			*(char*)ptr = atoi(LPCSTR(*str));
			break;
		case TT_STR:
			memcpy(ptr, *str, str->Len());
			break;
		case TT_INT:
			*(int*)ptr = atoi(LPCSTR(*str));
		case TT_UINT:
			*(int*)ptr = atoi(LPCSTR(*str));
			break;
		case TT_SHT:
			*(short*)ptr = atoi(LPCSTR(*str));
			break;
		case TT_LNG:
			*(long*)ptr = atol(LPCSTR(*str));
			break;
		default:
			break;
	}
}

bool CWinEditValue::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// �������벼����
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// ���ڡ����ʤ�⤦���ä��粼����

	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// ��������夲��
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// ���ڡ����ʤ�⤦���ä���夲��

	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEditValue::onkeypress_right()
{
	return true;	// �����롼�׷�³
}
bool CWinEditValue::onkeypress_left()
{
	return true;	// �����롼�׷�³
}
bool CWinEditValue::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] != TT_SPC && m_my_tt[m_cur.y] != TT_VCT)
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
	}
	else if (m_my_tt[m_cur.y] == TT_VCT)
	{
		*(int*)m_ptr[m_cur.y] = 1;
		return false;	// Vector���ɲä��뤿��˰�ö��λ
	}

	return true;	// �����롼�׷�³
}
bool CWinEditValue::onkeypress_cancel()
{
	return m_disable_cansel;
}

