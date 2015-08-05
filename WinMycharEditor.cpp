#include "win.h"

CWinMycharEditor::CWinMycharEditor(CConfig* config)
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

	m_data = new CData;

	// �����ǥ��ʥꥪ���ɤ߹���

	// �ޥ�������ɤ߹���
	read_mychar();

	// ɽ��
	push("���ʥꥪID",		&m_data->m_mychar[0].id,	TT_INT,	1);
	push("��²",			&m_data->m_mychar[0].race,	TT_INT,	1);
	push("����",			&m_data->m_mychar[0].job,	TT_INT,	1);
	push("°��",			&m_data->m_mychar[0].type,	TT_BYT,	1);
	push("����",			&m_data->m_mychar[0].gender,	TT_INT,	1);
	push("̾��",			&m_data->m_mychar[0].name,	TT_CST,	1);
	push("������",			&m_data->m_mychar[0].tile,	TT_CHR,	2);
	push("ʸ����",			&m_data->m_mychar[0].ch,	TT_CHR,	1);
	push("�طʿ�",			&m_data->m_mychar[0].bg,	TT_CHR,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("���ơ�����",		&m_data->m_mychar[0].status,	TT_INT,	1);
	push("��٥�",			&m_data->m_mychar[0].level,	TT_CHR,	1);
	push("�и���",			&m_data->m_mychar[0].exp,	TT_INT,	1);
	push("���ϡʸ��ߡ�",		&m_data->m_mychar[0].hp.p,	TT_INT,	1);
	push("���ϡʰ��Ū�����",	&m_data->m_mychar[0].hp.t,	TT_INT,	1);
	push("���ϡʺ����",		&m_data->m_mychar[0].hp.m,	TT_INT,	1);
	push("������ʸ��ߡ�",		&m_data->m_mychar[0].sp.p,	TT_INT,	1);
	push("������ʰ��Ū�����",	&m_data->m_mychar[0].sp.t,	TT_INT,	1);
	push("������ʺ����",		&m_data->m_mychar[0].sp.m,	TT_INT,	1);
	push("�����ϡʸ��ߡ�",		&m_data->m_mychar[0].ap.p,	TT_INT,	1);
	push("�����ϡʰ��Ū�����",	&m_data->m_mychar[0].ap.t,	TT_INT,	1);
	push("�����ϡʺ����",		&m_data->m_mychar[0].ap.m,	TT_INT,	1);
	push("�ɸ��ϡʸ��ߡ�",		&m_data->m_mychar[0].gp.p,	TT_INT,	1);
	push("�ɸ��ϡʰ��Ū�����",	&m_data->m_mychar[0].gp.t,	TT_INT,	1);
	push("�ɸ��ϡʺ����",		&m_data->m_mychar[0].gp.m,	TT_INT,	1);
	push("��ˡ�ϡʸ��ߡ�",		&m_data->m_mychar[0].mp.p,	TT_INT,	1);
	push("��ˡ�ϡʰ��Ū�����",	&m_data->m_mychar[0].mp.t,	TT_INT,	1);
	push("��ˡ�ϡʺ����",		&m_data->m_mychar[0].mp.m,	TT_INT,	1);
	push("�����ϡʸ��ߡ�",		&m_data->m_mychar[0].ep.p,	TT_INT,	1);
	push("�����ϡʰ��Ū�����",	&m_data->m_mychar[0].ep.t,	TT_INT,	1);
	push("�����ϡʺ����",		&m_data->m_mychar[0].ep.m,	TT_INT,	1);
	push("���ᤵ�ʸ��ߡ�",		&m_data->m_mychar[0].fp.p,	TT_INT,	1);
	push("���ᤵ�ʰ��Ū�����",	&m_data->m_mychar[0].fp.t,	TT_INT,	1);
	push("���ᤵ�ʺ����",		&m_data->m_mychar[0].fp.m,	TT_INT,	1);
	push("���Ѥ��ʸ��ߡ�",		&m_data->m_mychar[0].dp.p,	TT_INT,	1);
	push("���Ѥ��ʰ��Ū�����",	&m_data->m_mychar[0].dp.t,	TT_INT,	1);
	push("���Ѥ��ʺ����",		&m_data->m_mychar[0].dp.m,	TT_INT,	1);
	push("��ʢ��",			&m_data->m_mychar[0].food,	TT_BYT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("�������",		&m_data->m_mychar[0].rweapon,	TT_SHT,	1);
	push("�������",		&m_data->m_mychar[0].lweapon,	TT_SHT,	1);
	push("��",			&m_data->m_mychar[0].helm,	TT_SHT,	1);
	push("�ɶ�",			&m_data->m_mychar[0].armor,	TT_SHT,	1);
	push("�ޥ��",			&m_data->m_mychar[0].mant,	TT_SHT,	1);
	push("��",			&m_data->m_mychar[0].boots,	TT_SHT,	1);
	push("������",			&m_data->m_mychar[0].equip,	TT_SHT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("������ˡ",		&m_data->m_mychar[0].magic,	TT_BYT,	1);
	push("��ˡ�и���",		&m_data->m_mychar[0].magicexp,	TT_BYT,	1);
	push("°������",		&m_data->m_mychar[0].fight,	TT_BYT,	1);
	push("°���и���",		&m_data->m_mychar[0].fightexp,	TT_BYT,	1);
	push("����������",		&m_data->m_mychar[0].skill,	TT_BYT,	1);
	push("������и���",		&m_data->m_mychar[0].skillexp,	TT_BYT,	1);
	push("����",			&m_data->m_mychar[0].curse,	TT_BYT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("�ץ�ե�����",		&m_data->m_mychar[0].prof,	TT_CST,	1);

}

CWinMycharEditor::~CWinMycharEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinMycharEditor::drawwin()
{
	setedit(m_wpos.x, m_wpos.y, &m_cur.y, &m_dpos.y, m_name, m_value, m_cp);
	return true;
}

void CWinMycharEditor::push(const CString str, void * ptr, const int chr, const int num)
{
	push(str, ptr, chr, num, m_cpair);
}
void CWinMycharEditor::push(const CString str, void * ptr, const int chr, const int num, const int cpair)
{
	m_name.push_back(str);
	m_ptr.push_back(ptr);
	m_my_tt.push_back(chr);
	m_size.push_back(num);
	m_value.push_back(encode(ptr, chr, num));
	m_cp.push_back(cpair);
}

CString CWinMycharEditor::encode(void * ptr, const int chr, const int num)
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
		default:
			break;
	}
	return (CString(tmp_buf));
}

void CWinMycharEditor::decode(CString* str, void *ptr, const int chr)
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


// �ޥ������ե������ɤ߹���
void CWinMycharEditor::read_mychar()
{
	CFile*	mycharfp;
	mycharfp = new CFile;

	mycharfp->read_mychar(m_data);


	delete(mycharfp);
}

// �ޥ������ե�����񤭹���
void CWinMycharEditor::write_mychar()
{
	CFile*	mycharfp;
	mycharfp = new CFile;

	mycharfp->write_mychar(m_data);


	delete(mycharfp);
}

void CWinMycharEditor::keyloop()
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

bool CWinMycharEditor::onkeypress_left()
{
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMycharEditor::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;
	if (m_my_tt[m_cur.y] == TT_SPC)	m_cur.y++;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMycharEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	if (m_my_tt[m_cur.y] == TT_SPC)	m_cur.y--;
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMycharEditor::onkeypress_right()
{
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMycharEditor::onkeypress_ok()
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
	}
	return true;	// �����롼�׷�³
}
bool CWinMycharEditor::onkeypress_cancel()
{
	// �ޥ������񤭽Ф�
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

	if (tmp_ret == 1)
	{
		write_mychar();
		return false;
	}
	else if (tmp_ret == 2)
	{
		return false;
	}
	drawwin();
	touchwin(m_this);
	wrefresh(m_this);
	return true;
}




void CWinMycharEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



