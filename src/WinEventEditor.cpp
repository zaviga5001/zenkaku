#include "win.h"

CWinEventEditor::CWinEventEditor(CConfig* config)
{
	// �ʲ��ϥǥե�����ͤǤ���
	// ���֥������Ⱥ������Ĵ�����Ƥ���������
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winy   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winw   = COLS / 2;	// ����������Ѥǥ�����ȡ�
	m_winh   = LINES;	// ��ι⤵
	m_maxwidth = 0;		// ʸ����κ�����

	m_data = new CData;

	m_data->m_eventnum = 0;

	// �����ǥ��ʥꥪ���ɤ߹���

	// ���٥���ɤ߹���
	read_event();

	for (int i = 0; i < m_data->m_eventnum; i++)
	{
		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", i);
		push(CString(tmp_buf), i);
	}
	push("��������", m_data->m_eventnum);
}

CWinEventEditor::~CWinEventEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinEventEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinEventEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinEventEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinEventEditor::change(const CString str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	m_maxwidth = 0;
	for (int i = 0; i < m_list[i].Len(); i++)
	{
		if (adjx(m_maxwidth) < m_list[i].Len())
			m_maxwidth = m_list[i].Len() / 2;
	}
}


// ���٥�ȥե������ɤ߹���
void CWinEventEditor::read_event()
{
	CFile*	fp;
	fp = new CFile;

	fp->read_event(m_data);

	delete(fp);
}

// ���٥�ȥե�����񤭹���
void CWinEventEditor::write_event(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_event(m_data, index);

	delete(fp);
}

void CWinEventEditor::keyloop()
{
	timeout(-1);    // �������Ϥ��Ԥ�

	for( ; ; )
	{
		int ch = wgetch(m_this);
		switch(ch)
		{
			case MYKEY_LEFT:
				if (!onkeypress_left())		return;
				break;
			case MYKEY_DOWN:
				if (!onkeypress_down())		return;
				break;
			case MYKEY_UP:
				if (!onkeypress_up())		return;
				break;
			case MYKEY_RIGHT:
				if (!onkeypress_right())	return;
				break;
			case MYKEY_OK:
				if (!onkeypress_ok())		return;
				break;
			case MYKEY_CANCEL:
				if (!onkeypress_cancel())	return;
				break;
			default:
				continue;
				break;
		}
	}
}

bool CWinEventEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEventEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEventEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEventEditor::onkeypress_right()
{
	// �ġ��Υ饤��α�ü�ޤǥ�������
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// ����Ĺ�饤��α�ü�ޤǥ�������
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEventEditor::onkeypress_ok()
{
	EventData*	tmp_ev;
	EventData	tmp_evo;
	CWinEditValue*	nw_editvalue;

	// ����������֤Υ��٥�Ⱦ����ɤ߹���
	if (m_cur.y == m_data->m_eventnum)
	{ // �����ɲ�
		tmp_ev = &tmp_evo;
	}
	else
	{
		tmp_ev = &m_data->m_event[m_cur.y];
	}

	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// �ݥ��󥿥��å�
		nw_editvalue->push("���������",	&tmp_ev->action,	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("���ơ���",		&tmp_ev->elm[0],	TT_INT, 1);
		nw_editvalue->push("���ơ���",		&tmp_ev->elm[1],	TT_INT, 1);
		nw_editvalue->push("���ơ���",		&tmp_ev->elm[2],	TT_INT, 1);
		nw_editvalue->push("���ơ���",		&tmp_ev->elm[3],	TT_INT, 1);
		nw_editvalue->push("���ơ���",		&tmp_ev->elm[4],	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�ե饰",		&tmp_ev->flg,		TT_INT, 1);
		nw_editvalue->push("False ���٥��",	&tmp_ev->falseid,	TT_INT, 1);
		nw_editvalue->push("True  ���٥��",	&tmp_ev->trueid,	TT_INT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		// ���٥�Ƚ񤭽Ф�
		CWinSelect1Item* nw_select1item;
		nw_select1item = new CWinSelect1Item;
		nw_select1item->setsize(20, 5);
		nw_select1item->m_msg = msg[MY_MSG_SYS_SAVE_YN].msg;
		nw_select1item->m_split = 2;
		nw_select1item->m_wpos.y = 3;
		nw_select1item->push(msg[MY_MSG_SYS_YES].msg, 1);
		nw_select1item->push(msg[MY_MSG_SYS_NO].msg,  2);
		int tmp_ret = nw_select1item->startwin(true);
		delete(nw_select1item);

		if (tmp_ret == 0)
		{
			continue;
		}
		else if (tmp_ret == 1)
		{
			if (m_cur.y == m_data->m_eventnum)
			{ // �����ɲä��ä�
				char tmp_buf[6];
				sprintf(tmp_buf, "%05d", m_cur.y);
				change(tmp_buf, m_cur.y, m_cur.y);
				m_data->m_eventnum++;
				push("��������", m_data->m_eventnum);

				m_data->m_event.push_back(*tmp_ev);
			}
			write_event(m_cur.y);
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// �����롼�׷�³
	}
}
bool CWinEventEditor::onkeypress_cancel()
{
	return false;	// ��λ
}




void CWinEventEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



