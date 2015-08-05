#include "win.h"

CWinPartyEditor::CWinPartyEditor(CConfig* config)
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

	// �����ǥ��ʥꥪ���ɤ߹���

	// �ѡ��ƥ��ɤ߹���
	for (m_partynum_in_file = 0; ; m_partynum_in_file++)
	{
		if (!read_party(m_partynum_in_file))	break;

		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", m_partynum_in_file);
		push(CString(tmp_buf), m_partynum_in_file);
	}
	push("��������", m_partynum_in_file);
}

CWinPartyEditor::~CWinPartyEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinPartyEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinPartyEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinPartyEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinPartyEditor::change(const CString str, const int id, const int index)
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


// �ѡ��ƥ��ե������ɤ߹���
bool CWinPartyEditor::read_party(int index)
{
	CFile*	fp;
	fp = new CFile;

	int ret = fp->read_party(m_data, index);

	delete(fp);

	return(ret);
}

// �ѡ��ƥ��ե�����񤭹���
void CWinPartyEditor::write_party(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_party(m_data, index);

	delete(fp);
}

void CWinPartyEditor::keyloop()
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

bool CWinPartyEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPartyEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPartyEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPartyEditor::onkeypress_right()
{
	// �ġ��Υ饤��α�ü�ޤǥ�������
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// ����Ĺ�饤��α�ü�ޤǥ�������
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPartyEditor::onkeypress_ok()
{
	EnemyParty*	tmp_ep;
	EnemyParty	tmp_epo;
	CWinEditValue*	nw_editvalue;

	// ����������֤Υѡ��ƥ������ɤ߹���
	if (m_cur.y == m_partynum_in_file)
	{ // �����ɲ�
		tmp_ep = &tmp_epo;
	}
	else
	{
		read_party(m_cur.y);
		tmp_ep = &m_data->m_enemyparty;
	}

	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// �ݥ��󥿥��å�
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[0],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[1],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[2],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[3],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[4],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[5],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[6],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[7],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[8],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[9],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[10],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[11],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[12],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[13],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[14],	TT_INT, 1);
		nw_editvalue->push("Ũ����",		&tmp_ep->enemy[15],	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�����ƥࡧ��",	&tmp_ep->item[0],	TT_INT, 1);
		nw_editvalue->push("�����ƥ�Ψ����",	&tmp_ep->item_r[0],	TT_INT, 1);
		nw_editvalue->push("�����ƥࡧ��",	&tmp_ep->item[1],	TT_INT, 1);
		nw_editvalue->push("�����ƥ�Ψ����",	&tmp_ep->item_r[1],	TT_INT, 1);
		nw_editvalue->push("�����ƥࡧ��",	&tmp_ep->item[2],	TT_INT, 1);
		nw_editvalue->push("�����ƥ�Ψ����",	&tmp_ep->item_r[2],	TT_INT, 1);
		nw_editvalue->push("�����ƥࡧ��",	&tmp_ep->item[3],	TT_INT, 1);
		nw_editvalue->push("�����ƥ�Ψ����",	&tmp_ep->item_r[3],	TT_INT, 1);
		nw_editvalue->push("�����ƥࡧ��",	&tmp_ep->item[4],	TT_INT, 1);
		nw_editvalue->push("�����ƥ�Ψ����",	&tmp_ep->item_r[4],	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�ե饰",		&tmp_ep->flg,		TT_INT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		// �����ƥ�񤭽Ф�
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
			if (m_cur.y == m_partynum_in_file)
			{ // �����ɲä��ä�
				char tmp_buf[6];
				sprintf(tmp_buf, "%05d", m_partynum_in_file);
				change(tmp_buf, m_partynum_in_file, m_partynum_in_file);
				m_partynum_in_file++;
				push("��������", m_data->m_itemnum);
			}
			write_party(m_cur.y);
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// �����롼�׷�³
	}
}
bool CWinPartyEditor::onkeypress_cancel()
{
	return false;	// ��λ
}




void CWinPartyEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



