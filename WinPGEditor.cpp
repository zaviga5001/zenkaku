#include "win.h"

CWinPGEditor::CWinPGEditor(CConfig* config)
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

	// �ѡ��ƥ����ɤ߹���
	for (m_data->m_enemypgnum = 0; ; m_data->m_enemypgnum++)
	{
		if (!read_pg(m_data->m_enemypgnum))	break;

		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", m_data->m_enemypgnum);
		push(CString(tmp_buf), m_data->m_enemypgnum);
	}
	push("��������", m_data->m_enemypgnum);
}

CWinPGEditor::~CWinPGEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinPGEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinPGEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinPGEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinPGEditor::change(const CString str, const int id, const int index)
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


// �ѡ��ƥ����ե������ɤ߹���
bool CWinPGEditor::read_pg(int index)
{
	CFile*	fp;
	fp = new CFile;

	int ret = fp->read_pg(m_data, index);

	delete(fp);

	return(ret);
}

// �ѡ��ƥ����ե�����񤭹���
void CWinPGEditor::write_pg(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_pg(m_data, index);

	delete(fp);
}

void CWinPGEditor::keyloop()
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

bool CWinPGEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPGEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPGEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPGEditor::onkeypress_right()
{
	// �ġ��Υ饤��α�ü�ޤǥ�������
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// ����Ĺ�饤��α�ü�ޤǥ�������
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinPGEditor::onkeypress_ok()
{
	int	tmp_vct;
	int	tmp_ret;
	char	tmp_str[4];
	CString	tmp_cs;

	EnemyPG*	tmp_pg;
	EnemyPG		tmp_pgo;
	EnemyPGValue	tmp_pgvo;
	if (m_cur.y == m_data->m_enemypgnum)
	{ // �����ɲ�
		tmp_pg = &tmp_pgo;
		tmp_pgo.elm.push_back(tmp_pgvo);
	}
	else
	{ // ��¸�쥳����
		tmp_pg = &m_data->m_enemypg[m_cur.y];
	}

	CWinEditValue*	nw_editvalue;

	for ( ; ; )
	{
		tmp_vct = 0;
		tmp_ret = 0;

		nw_editvalue = new CWinEditValue;
		// �ݥ��󥿥��å�
		for (int i = 0; i < tmp_pg->elm.size(); i++)
		{
			sprintf(tmp_str, "%02d", i);
			tmp_cs = tmp_str;
			nw_editvalue->push("�ѡ��ƥ�ID" + tmp_cs,	&tmp_pg->elm[i].party,		TT_INT, 1);
			nw_editvalue->push("�ѡ��ƥ�Ψ" + tmp_cs,	&tmp_pg->elm[i].party_r,	TT_CHR, 1);
		}
		nw_editvalue->push("�ѡ��ƥ��ɲ�", &tmp_vct, TT_VCT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);

		if (tmp_vct == 1)
		{ // editvalue�����vector�ɲä��ؼ����줿
			EnemyPGValue	tmp_pgvo2;
			tmp_pg->elm.push_back(tmp_pgvo2);
			tmp_ret = 1;
		}
		else
		{
			// �ѡ��ƥ��񤭽Ф�
			CWinSelect1Item* nw_select1item;
			nw_select1item = new CWinSelect1Item;
			nw_select1item->setsize(20, 5);
			nw_select1item->m_msg = msg[MY_MSG_SYS_SAVE_YN].msg;
			nw_select1item->m_split = 2;
			nw_select1item->m_wpos.y = 3;
			nw_select1item->push(msg[MY_MSG_SYS_YES].msg, 1);
			nw_select1item->push(msg[MY_MSG_SYS_NO].msg,  2);
			tmp_ret = nw_select1item->startwin(true);
			delete(nw_select1item);
		}

		if (tmp_ret == 0)
		{
			continue;
		}
		else if (tmp_ret == 1)
		{
			if (m_cur.y == m_data->m_enemypgnum)
			{ // �����ɲä��ä�
				char tmp_buf[6];
				sprintf(tmp_buf, "%05d", m_cur.y);
				change(tmp_buf, m_cur.y, m_cur.y);
				m_data->m_enemypgnum++;

				push("��������", m_data->m_enemypgnum);

				m_data->m_enemypg.push_back(*tmp_pg);
			}
			write_pg(m_cur.y);
			if (tmp_vct == 1)
			{ // editvalue�����vector�ɲä��ؼ����줿
				continue;
			}
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// �����롼�׷�³
	}
}
bool CWinPGEditor::onkeypress_cancel()
{
	return false;	// ��λ
}




void CWinPGEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



