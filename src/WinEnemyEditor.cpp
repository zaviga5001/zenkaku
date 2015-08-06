#include "win.h"

CWinEnemyEditor::CWinEnemyEditor(CConfig* config)
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
	m_enemynum = 0;


	m_data = new CData;

	// �����ǥ��ʥꥪ���ɤ߹���

	// Ũ������ɤ߹���
	read_enemy();

	for (int i = 0; i < m_enemynum; i++)
	{
		push(m_data->m_enemy[i].name, i);
	}
	push("��������", m_enemynum);
}

CWinEnemyEditor::~CWinEnemyEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinEnemyEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinEnemyEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinEnemyEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinEnemyEditor::change(const CString str, const int id, const int index)
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


// Ũ�����ե������ɤ߹���
void CWinEnemyEditor::read_enemy()
{
	CFile*	fp;
	fp = new CFile;

	for (m_enemynum = 0; ; m_enemynum++)
	{
		if (!fp->read_enemy(m_data, m_enemynum))	break;
	}

	delete(fp);
}

// Ũ�����ե�����񤭹���
void CWinEnemyEditor::write_enemy(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_enemy(m_data, index);

	delete(fp);
}

void CWinEnemyEditor::keyloop()
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

bool CWinEnemyEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEnemyEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEnemyEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEnemyEditor::onkeypress_right()
{
	// �ġ��Υ饤��α�ü�ޤǥ�������
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// ����Ĺ�饤��α�ü�ޤǥ�������
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinEnemyEditor::onkeypress_ok()
{
	CWinEditValue*	nw_editvalue;

	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// �ݥ��󥿥��å�
		nw_editvalue->push("̾��",		&m_data->m_enemy[m_cur.y].name,		TT_CST, 1);
		nw_editvalue->push("°��",		&m_data->m_enemy[m_cur.y].type,		TT_BYT, 1);
		nw_editvalue->push("���ơ�����",	&m_data->m_enemy[m_cur.y].status,	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("���ϡʸ��ߡ�",	&m_data->m_enemy[m_cur.y].hp.p,		TT_INT, 1);
		nw_editvalue->push("���ϡʺ����",	&m_data->m_enemy[m_cur.y].hp.m,		TT_INT, 1);
		nw_editvalue->push("�����ϡʸ��ߡ�",	&m_data->m_enemy[m_cur.y].ap.p,		TT_INT, 1);
		nw_editvalue->push("�����ϡʺ����",	&m_data->m_enemy[m_cur.y].ap.m,		TT_INT, 1);
		nw_editvalue->push("�ɸ��ϡʸ��ߡ�",	&m_data->m_enemy[m_cur.y].gp.p,		TT_INT, 1);
		nw_editvalue->push("�ɸ��ϡʺ����",	&m_data->m_enemy[m_cur.y].gp.m,		TT_INT, 1);
		nw_editvalue->push("��ˡ�ϡʸ��ߡ�",	&m_data->m_enemy[m_cur.y].mp.p,		TT_INT, 1);
		nw_editvalue->push("��ˡ�ϡʺ����",	&m_data->m_enemy[m_cur.y].mp.m,		TT_INT, 1);
		nw_editvalue->push("�����ϡʸ��ߡ�",	&m_data->m_enemy[m_cur.y].ep.p,		TT_INT, 1);
		nw_editvalue->push("�����ϡʺ����",	&m_data->m_enemy[m_cur.y].ep.m,		TT_INT, 1);
		nw_editvalue->push("���ᤵ�ʸ��ߡ�",	&m_data->m_enemy[m_cur.y].fp.p,		TT_INT, 1);
		nw_editvalue->push("���ᤵ�ʺ����",	&m_data->m_enemy[m_cur.y].fp.m,		TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�и���",		&m_data->m_enemy[m_cur.y].exp,		TT_INT, 1);
		nw_editvalue->push("�����",		&m_data->m_enemy[m_cur.y].gold,		TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("��������ƥ�ID����",&m_data->m_enemy[m_cur.y].item[0].id,	TT_SHT, 1);
		nw_editvalue->push("��������ƥ������",&m_data->m_enemy[m_cur.y].item[0].num,	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�Ψ����",&m_data->m_enemy[m_cur.y].item_r[0],	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�ID����",&m_data->m_enemy[m_cur.y].item[1].id,	TT_SHT, 1);
		nw_editvalue->push("��������ƥ������",&m_data->m_enemy[m_cur.y].item[1].num,	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�Ψ����",&m_data->m_enemy[m_cur.y].item_r[1],	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�ID����",&m_data->m_enemy[m_cur.y].item[2].id,	TT_SHT, 1);
		nw_editvalue->push("��������ƥ������",&m_data->m_enemy[m_cur.y].item[2].num,	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�Ψ����",&m_data->m_enemy[m_cur.y].item_r[2],	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�ID����",&m_data->m_enemy[m_cur.y].item[3].id,	TT_SHT, 1);
		nw_editvalue->push("��������ƥ������",&m_data->m_enemy[m_cur.y].item[3].num,	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�Ψ����",&m_data->m_enemy[m_cur.y].item_r[3],	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�ID����",&m_data->m_enemy[m_cur.y].item[4].id,	TT_SHT, 1);
		nw_editvalue->push("��������ƥ������",&m_data->m_enemy[m_cur.y].item[4].num,	TT_CHR, 1);
		nw_editvalue->push("��������ƥ�Ψ����",&m_data->m_enemy[m_cur.y].item_r[4],	TT_CHR, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[0],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[0],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[1],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[1],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[2],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[2],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[3],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[3],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[4],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[4],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[5],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[5],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[6],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[6],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[7],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[7],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[8],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[8],	TT_CHR, 1);
		nw_editvalue->push("����ID����",	&m_data->m_enemy[m_cur.y].fight[9],	TT_SHT, 1);
		nw_editvalue->push("����Ψ����",	&m_data->m_enemy[m_cur.y].fight_r[9],	TT_CHR, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�ե饰",		&m_data->m_enemy[m_cur.y].flg,		TT_INT, 1);
		nw_editvalue->push("����ŨID",		&m_data->m_enemy[m_cur.y].next_enemy,	TT_INT, 1);
		nw_editvalue->push("�Ƥ�ŨID����",	&m_data->m_enemy[m_cur.y].call_enemy[0],TT_INT, 1);
		nw_editvalue->push("�Ƥ�ŨID����",	&m_data->m_enemy[m_cur.y].call_enemy[1],TT_INT, 1);
		nw_editvalue->push("�Ƥ�ŨID����",	&m_data->m_enemy[m_cur.y].call_enemy[2],TT_INT, 1);
		nw_editvalue->push("�Ƥ�ŨID����",	&m_data->m_enemy[m_cur.y].call_enemy[3],TT_INT, 1);
		nw_editvalue->push("�Ƥ�ŨID����",	&m_data->m_enemy[m_cur.y].call_enemy[4],TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("�ץ�ե�����",	&m_data->m_enemy[m_cur.y].prof,		TT_CST, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);

		// Ũ�����񤭽Ф�
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
			write_enemy(m_cur.y);
			change(m_data->m_enemy[m_cur.y].name, m_cur.y, m_cur.y);
			if (m_cur.y == m_enemynum)
			{ // �����ɲä��ä�
				m_enemynum++;
				push("��������", m_enemynum);

			}
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// �����롼�׷�³
	}
}
bool CWinEnemyEditor::onkeypress_cancel()
{
	return false;	// ��λ
}




void CWinEnemyEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



