#include "win.h"

CWinMapEditor::CWinMapEditor(CConfig* config)
{
	// �ʲ��ϥǥե�����ͤǤ���
	// ���֥������Ⱥ������Ĵ�����Ƥ���������
	m_dpos.x = 0;		// �ޥå׾��ɽ�����ϰ��֡���κ���ˤ����
	m_dpos.y = 0;		// �ޥå׾��ɽ�����ϰ��֡���κ���ˤ����
	m_cur.x  = 0;		// ��������ΰ���
	m_cur.y  = 0;		// ��������ΰ���
	m_winx   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winy   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winw   = COLS / 2;	// ����������Ѥǥ�����ȡ�
	m_winh   = LINES;	// ��ι⤵

	m_posdata = NULL;
	m_posbuf.flg     = 0;
	m_posbuf.trueid  = 0;
	m_posbuf.falseid = 0;
	m_posbuf.name    = 0;
	m_posbuf.enemy   = 0;
	m_posbuf.encount = 0;
	m_posundobuf = m_posbuf;
	m_posmsk.flg     = 0xFFFFFFFF;
	m_posmsk.trueid  = 0xFFFFFFFF;
	m_posmsk.falseid = 0xFFFFFFFF;
	m_posmsk.name    = 0xFF;
	m_posmsk.enemy   = 0xFFFFFFFF;
	m_posmsk.encount = 0xFF;

	m_mapdata.height = 0;
	m_mapdata.width  = 0;
	m_mapdata.nextmap_u = 0;
	m_mapdata.nextmap_d = 0;
	m_mapdata.nextmap_l = 0;
	m_mapdata.nextmap_r = 0;

	for (int i = 0; i < MAX_FNAME; i++)
	{
		m_fieldname[i] = "��";
	}

	m_data = new CData;
}

CWinMapEditor::~CWinMapEditor()
{
	if (m_this != NULL)	delwin(m_this);
	if (m_data != NULL)	delete(m_data);
	if (m_posdata != NULL)	delete[] m_posdata;
}

int CWinMapEditor::drawwin()
{
	// ��������ȿž
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_REVERSE);
	// ���̺�����
	wrefresh(m_this);
	return true;
}

void CWinMapEditor::refreshwin()
{
	for (int i = 0; i < m_winh - m_winy; i++)
	{
		for (int j = 0; j < m_winw - m_winx; j++)
		{
			refreshpos(m_dpos.x + j, m_dpos.y + i);
		}
	}
}

void CWinMapEditor::refreshpos(int x, int y)
{
	if (m_dpos.x <= x && x < m_dpos.x + m_winw - m_winx &&
	    m_dpos.y <= y && y < m_dpos.y + m_winh - m_winy   )
	{
		if (x > m_mapdata.width  - 1 ||
		    y > m_mapdata.height - 1   )
		{
			wattrset(m_this, COLOR_PAIR(0));
			mvwaddnstr(m_this, y - m_dpos.y, adjx(x - m_dpos.x), "��", 2);
		}
		else
		{
			int tileno = gettile(x, y);

			int cpair = getcpair((int)m_tiledata[tileno].ch, (int)m_tiledata[tileno].bg);
			wattrset(m_this, COLOR_PAIR(cpair));
			mvwaddnstr(m_this, y - m_dpos.y, adjx(x - m_dpos.x), m_tiledata[tileno].tile, 2);
		}
	}
}

int CWinMapEditor::gettile(int x, int y)
{
	int tileno;
	if (m_data->get_flg(m_posdata[xyton(x, y)].flg) == true)
		tileno = m_posdata[xyton(x, y)].trueid;
	else
		tileno = m_posdata[xyton(x, y)].falseid;

	// ���ڥ����ݥ������ID���ɤ���Ƚ��
	for ( ; ; )
	{
		if (tileno >= 100000)
		{
			tileno -= 100000;
			if (m_data->get_flg(m_spposdata[tileno].flg) == true)
				tileno = m_spposdata[tileno].trueid;
			else
				tileno = m_spposdata[tileno].falseid;
		}
		else
		{
			break;
		}
	}

	return (tileno);
}


void CWinMapEditor::keyloop()
{
	timeout(-1);    // �������Ϥ��Ԥ�

	CWinEditValue*		nw_editvalue;
	CWinEditValue_Flg*	nw_editvalue_flg;
	CWinEditValue_Tile*	nw_editvalue_tile;
	CWinEditValue_Event*	nw_editvalue_event;
	CWinEditValue_Pos*	nw_editvalue_pos;
	CWinEditValue_Cmask*	nw_editvalue_cmask;
	CWinSelect1Icon*	nw_select1icon;
	CWinSelect1Item*	nw_select1item;
	CWinMsg*		nw_msg;
	CWinGetPath*		nw_getpath;
	CFile*			mapfp;

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
			case 'a':
				// �������ɲ�
				int tmp_copyid;
				if (m_data->get_flg(m_posdata[xyton(m_cur.x, m_cur.y)].flg) == true)
					tmp_copyid = m_posdata[xyton(m_cur.x, m_cur.y)].trueid;
				else
					tmp_copyid = m_posdata[xyton(m_cur.x, m_cur.y)].falseid;

				m_tiledata[m_tilenum] = m_tiledata[tmp_copyid];
				m_tilenum++;

				// �ɲô�λ��å�����
				nw_msg = new CWinMsg;
				nw_msg->m_msg = msg[MY_MSG_SYS_ADD_TILE].msg;
				nw_msg->setdefcpair(1, 0);
				nw_msg->startwin(true);
				delete(nw_msg);
				refreshwin();
				drawwin();
				break;
			case 'b':
				// �ե饰�ӥåȥ��ǥ���
				int	tmp_id, tmp_old_id, tmp_value, tmp_ret;
				tmp_id     = 1;
				tmp_old_id = 1;
				for ( ; ; )
				{
					nw_editvalue_flg = new CWinEditValue_Flg(m_data);

					tmp_value = m_data->get_flg(tmp_id);

					nw_editvalue_flg->push("ID",		&tmp_id,	TT_INT, 1);
					nw_editvalue_flg->push("Value ",	&tmp_value,	TT_INT, 1);
					nw_editvalue_flg->setsize(12, 5);
					tmp_ret = nw_editvalue_flg->startwin(true);
					delete(nw_editvalue_flg);

					if (tmp_id != tmp_old_id)
					{
						// ID���ѹ����줿
						if (tmp_id < 0)
							tmp_id = FLG_BITS * 32 - 1;
						if (tmp_id > FLG_BITS * 32 - 1)
							tmp_id = 0;

						tmp_old_id = tmp_id;
						continue;
					}

					// �ե饰�ѹ�
					m_data->set_flg(tmp_id, tmp_value);

					if (tmp_ret)	break;
				}

				refreshwin();
				drawwin();
				break;
			case 'c':
				// ���ԡ�
				m_posbuf = m_posdata[xyton(m_cur.x, m_cur.y)];
				break;
			case 'v':
				// �ڡ�����
				m_posundobuf	= m_posdata[xyton(m_cur.x, m_cur.y)];
				if (m_posmsk.flg)	m_posdata[xyton(m_cur.x, m_cur.y)].flg		= m_posbuf.flg;
				if (m_posmsk.falseid)	m_posdata[xyton(m_cur.x, m_cur.y)].falseid	= m_posbuf.falseid;
				if (m_posmsk.trueid)	m_posdata[xyton(m_cur.x, m_cur.y)].trueid	= m_posbuf.trueid;
				if (m_posmsk.name)	m_posdata[xyton(m_cur.x, m_cur.y)].name		= m_posbuf.name;
				if (m_posmsk.enemy)	m_posdata[xyton(m_cur.x, m_cur.y)].enemy	= m_posbuf.enemy;
				if (m_posmsk.encount)	m_posdata[xyton(m_cur.x, m_cur.y)].encount	= m_posbuf.encount;
				refreshwin();
				drawwin();
				break;
			case 'u':
				// ����ɥ�
				if (m_posmsk.flg)	m_posdata[xyton(m_cur.x, m_cur.y)].flg		= m_posundobuf.flg;
				if (m_posmsk.falseid)	m_posdata[xyton(m_cur.x, m_cur.y)].falseid	= m_posundobuf.falseid;
				if (m_posmsk.trueid)	m_posdata[xyton(m_cur.x, m_cur.y)].trueid	= m_posundobuf.trueid;
				if (m_posmsk.name)	m_posdata[xyton(m_cur.x, m_cur.y)].name		= m_posundobuf.name;
				if (m_posmsk.enemy)	m_posdata[xyton(m_cur.x, m_cur.y)].enemy	= m_posundobuf.enemy;
				if (m_posmsk.encount)	m_posdata[xyton(m_cur.x, m_cur.y)].encount	= m_posundobuf.encount;
				refreshwin();
				drawwin();
				break;
			case 'e':
				// ���٥�ȥ��ǥ���
			case 'f':
				// ���٥�ȥ��ǥ���
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// �ޥåפ�¸�ߤ���
					int	tmp_id = 0;

					for ( ; ; )
					{
						nw_editvalue_event = new CWinEditValue_Event;
						if (ch == 'e')
						{
							nw_editvalue_event->push("StopEvent:ID",	&tmp_id,			TT_INT, 1);
							nw_editvalue_event->push("StopEvent:FLG ",	&m_sevent[tmp_id].flg,		TT_INT, 1);
							nw_editvalue_event->push("StopEvent:FLG BIT ",	&m_sevent[tmp_id].torf,		TT_CHR, 1);
							nw_editvalue_event->push("StopEvent:HEIGHT",	&m_sevent[tmp_id].h,		TT_INT, 1);
							nw_editvalue_event->push("StopEvent:EVENT NO",	&m_sevent[tmp_id].event,	TT_INT, 1);
						}
						else
						{
							nw_editvalue_event->push("PointEvent:ID ",	&tmp_id,			TT_INT, 1);
							nw_editvalue_event->push("PointEvent:FLG",	&m_pevent[tmp_id].flg,		TT_INT, 1);
							nw_editvalue_event->push("PointEvent:FLG BIT",	&m_pevent[tmp_id].torf,		TT_CHR, 1);
							nw_editvalue_event->push("PointEvent:HEIGHT ",	&m_pevent[tmp_id].h,		TT_INT, 1);
							nw_editvalue_event->push("PointEvent:EVENT NO ",&m_pevent[tmp_id].event,	TT_INT, 1);
						}

						int tmp_ret	= nw_editvalue_event->startwin(true);
						delete(nw_editvalue_event);

						if (tmp_ret == 1)
						{
							// ID���ѹ����줿
							if (tmp_id < 0)
								tmp_id = MAX_MAPEVENT - 1;
							if (tmp_id > MAX_MAPEVENT - 1)
								tmp_id = 0;

							refreshwin();
							drawwin();
						}
						else
						{
							refreshwin();
							drawwin();
							break;
						}
					}
				}
				else
				{	// �ޥåפ��ɤ߹��ޤ�Ƥ��ʤ��ٹ�
					warn_no_map();
				}
				break;
			case 'h':
				nw_msg = new CWinMsg;
				nw_msg->m_msg = "�����������ɲ�n�¡��ե饰�ӥåȥ��ǥ���n�á����ԡ�n�֡��ڡ�����n�ա�����ɥ�n�ѡ����ԡ��ޥ������ǥ���n�š����٥�ȥ��ǥ���n�̡�����n�͡��ޥå׾��󥨥ǥ���n�Ρ���̾���ǥ���n�С��ѥ�å�ɽ��n�ԡ������륨�ǥ���n�ӡ����ڥ����ݥ�����󥨥ǥ���n�ء��ݥ�����󥨥ǥ���n�ڡ������ֽ�λ";
				nw_msg->setsize(20,100);
				nw_msg->startwin(true);
				delete(nw_msg);
				refreshwin();
				drawwin();
				break;
			case 'l':
				mapfp = new CFile;
				// �ޥå��ֹ�����Ϥ���
				nw_getpath = new CWinGetPath;
				nw_getpath->settitle(CString(msg[MY_MSG_SYS_INP_MAPNO].msg));
				m_path = nw_getpath->startdialog(true);
				m_path = "data/qwert123/map/" + m_path;
				delete(nw_getpath);
			
			
				// �ޥåץ�������NextMap�����
				m_mapdata = mapfp->get_map_size(m_path);
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{
					// �����Υݥ������ơ��֥뤬����С��ޤ��˴�����
					if (m_posdata != NULL)	delete[] m_posdata;
					// �ݥ������ơ��֥������
					m_posdata = new PosData[m_mapdata.height * m_mapdata.width];
					// �ޥåפ���Ȥ��ɤ߹���
					m_tilenum = mapfp->read_map(m_path, &m_mapdata, m_posdata, m_spposdata, m_tiledata, m_pevent, m_sevent, m_fieldname);
				}
				delete(mapfp);
				m_cur.x = 0;
				m_cur.y = 0;
				refreshwin();
				drawwin();
				break;
			case 'm':
				// �ޥå׾��󥨥ǥ���
				nw_editvalue = new CWinEditValue;

				nw_editvalue->push("NEXTMAP ��", &m_mapdata.nextmap_u, TT_CHR, 1);
				nw_editvalue->push("NEXTMAP ��", &m_mapdata.nextmap_d, TT_CHR, 1);
				nw_editvalue->push("NEXTMAP ��", &m_mapdata.nextmap_l, TT_CHR, 1);
				nw_editvalue->push("NEXTMAP ��", &m_mapdata.nextmap_r, TT_CHR, 1);

				nw_editvalue->startwin(true);
				delete(nw_editvalue);
				refreshwin();
				drawwin();
				break;
			case 'n':
				// ��̾���ǥ���
				nw_editvalue = new CWinEditValue;

				char tmp_str[4];
				for (int i = 0; i < MAX_FNAME; i++)
				{
					sprintf(tmp_str, "%02d", i);
					nw_editvalue->push(CString(tmp_str), &m_fieldname[i], TT_CST, 1);
				}
				nw_editvalue->startwin(true);
				delete(nw_editvalue);
				refreshwin();
				drawwin();
				break;
			case 'p':
				// �ѥ�å�ɽ��
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// �ޥåפ�¸�ߤ���
					nw_select1icon = new CWinSelect1Icon;
					nw_select1icon->setsize(10, 10);
					for (int i = 0; i < COLOR_NUM * COLOR_NUM; i++)
					{
						nw_select1icon->m_cols = 8;
						nw_select1icon->push("��", i, i);
					}
					nw_select1icon->startwin(true);
					delete(nw_select1icon);
					refreshwin();
					drawwin();
				}
				else
				{	// �ޥåפ��ɤ߹��ޤ�Ƥ��ʤ��ٹ�
					warn_no_map();
				}
				break;
			case 'q':
				// ���ԡ��ޥ������ǥ���
				for ( ; ; )
				{
					nw_editvalue_cmask = new CWinEditValue_Cmask();

					nw_editvalue_cmask->push("FLG ",	&m_posmsk.flg,		TT_INT, 1);
					nw_editvalue_cmask->push("FALSE ID",	&m_posmsk.falseid,	TT_INT, 1);
					nw_editvalue_cmask->push("TRUE  ID",	&m_posmsk.trueid,	TT_INT, 1);
					nw_editvalue_cmask->push("NAME",	&m_posmsk.name,		TT_CHR, 1);
					nw_editvalue_cmask->push("ENEMY ",	&m_posmsk.enemy,	TT_INT, 1);
					nw_editvalue_cmask->push("ENCOUNT ",	&m_posmsk.encount,	TT_CHR, 1);
					nw_editvalue_cmask->setsize(20, 8);
					tmp_ret = nw_editvalue_cmask->startwin(true);
					delete(nw_editvalue_cmask);

					if (!tmp_ret)	break;
				}

				refreshwin();
				drawwin();
				break;
			case 't':
				// �����륨�ǥ���
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// �ޥåפ�¸�ߤ���
					int	tmp_id = gettile(m_cur.x, m_cur.y);

					for ( ; ; )
					{
						nw_editvalue_tile = new CWinEditValue_Tile;
						nw_editvalue_tile->push("FALSE ID",	&tmp_id,			TT_INT, 1);
						nw_editvalue_tile->push("FALSE CHAR",	 m_tiledata[tmp_id].tile,	TT_STR, 2, getcpair(m_tiledata[tmp_id].ch, m_tiledata[tmp_id].bg));
						nw_editvalue_tile->push("FALSE CH",	&m_tiledata[tmp_id].ch,		TT_CHR, 1, getcpair(m_tiledata[tmp_id].ch, 0));
						nw_editvalue_tile->push("FALSE BG",	&m_tiledata[tmp_id].bg,		TT_CHR, 1, getcpair(m_tiledata[tmp_id].bg, 0));
						nw_editvalue_tile->push("FALSE ATTR",	&m_tiledata[tmp_id].attr,	TT_CHR, 1);
						nw_editvalue_tile->push("FALSE HEIGHT",	&m_tiledata[tmp_id].height,	TT_CHR, 1);
						nw_editvalue_tile->push("FALSE MOVE",	&m_tiledata[tmp_id].move,	TT_CHR, 1);

						int tmp_ret_id	= nw_editvalue_tile->startwin(true);
						delete(nw_editvalue_tile);

						if (tmp_ret_id == 1)
						{
							// �����뤬�ѹ����줿
							if (tmp_id < 0)			tmp_id = m_tilenum - 1;
							if (tmp_id > m_tilenum - 1)	tmp_id = 0;

							refreshpos(m_cur.x, m_cur.y);
							drawwin();
						}
						else
						{
							refreshwin();
							drawwin();
							break;
						}
					}
				}
				else
				{	// �ޥåפ��ɤ߹��ޤ�Ƥ��ʤ��ٹ�
					warn_no_map();
				}
				break;
			case 's':
				// ���ڥ����ݥ������ǡ������ǥ���
			case 'x':
				// �ݥ������ǡ������ǥ���
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// �ޥåפ�¸�ߤ���
					PosData* tmp_posdata;
					int posi = -1;
					for ( ; ; )
					{
						if (ch == 'x')
						{
							posi = xyton(m_cur.x, m_cur.y);
							tmp_posdata = &m_posdata[posi];
						}
						else
						{
							if (posi == -1)
							{
								nw_getpath = new CWinGetPath();
								nw_getpath->settitle(CString(msg[MY_MSG_SYS_INP_SPOS].msg));
								CString spos = nw_getpath->startdialog(true);
								delete(nw_getpath);
								posi = atoi(LPCSTR(spos));
								if (posi < 0 || posi >= MAX_SPPOS)
								{
									posi = -1;
									continue;
								}
								tmp_posdata = &m_spposdata[posi];
							}
						}

						nw_editvalue_pos = new CWinEditValue_Pos;
						// ���ȥե饰
						nw_editvalue_pos->push("FLAG",		&tmp_posdata->flg,	TT_INT, 1);
						nw_editvalue_pos->push("FALSE ID",	&tmp_posdata->falseid,	TT_INT, 1);
						nw_editvalue_pos->push("TRUE  ID",	&tmp_posdata->trueid,	TT_INT, 1);
						nw_editvalue_pos->push("F NAME",	&tmp_posdata->name,	TT_INT, 1);
						nw_editvalue_pos->push("ENEMY ",	&tmp_posdata->enemy,	TT_INT, 1);
						nw_editvalue_pos->push("ENCOUNT ",	&tmp_posdata->encount,	TT_CHR, 1);
						nw_editvalue_pos->push("--------------",	NULL,	TT_SPC, 1);

						if (tmp_posdata->falseid >= 100000)
							nw_editvalue_pos->push("FALSE CHAR",	 &tmp_posdata->falseid,	TT_INT, 1);
						else
							nw_editvalue_pos->push("FALSE CHAR",	 m_tiledata[tmp_posdata->falseid].tile,	TT_STR, 2, getcpair(m_tiledata[tmp_posdata->falseid].ch, m_tiledata[tmp_posdata->falseid].bg));

						if (tmp_posdata->trueid >= 100000)
							nw_editvalue_pos->push("TRUE  CHAR",	 &tmp_posdata->trueid,	TT_INT, 1);
						else
							nw_editvalue_pos->push("TRUE  CHAR",	 m_tiledata[tmp_posdata->trueid ].tile,	TT_STR, 2, getcpair(m_tiledata[tmp_posdata->trueid ].ch, m_tiledata[tmp_posdata->trueid ].bg));

						nw_editvalue_pos->push("F NAMESTR ",	 &m_fieldname[(int)tmp_posdata->name],	TT_CST, 1);

						int tmp_ret = nw_editvalue_pos->startwin(true);
						delete(nw_editvalue_pos);

						if (tmp_ret == 1)
						{
							// False�����뤬�ѹ����줿
							if      (tmp_posdata->falseid == 99999)
								tmp_posdata->falseid = 100000 + MAX_SPPOS - 1;
							else if (tmp_posdata->falseid > 100000 + MAX_SPPOS - 1)
								tmp_posdata->falseid = 100000;
							else if (tmp_posdata->falseid >= 100000)
								;
							else if (tmp_posdata->falseid < 0)
								tmp_posdata->falseid = m_tilenum - 1;
							else if (tmp_posdata->falseid > m_tilenum - 1)
								tmp_posdata->falseid = 0;

							refreshpos(m_cur.x, m_cur.y);
							drawwin();
						}
						else if (tmp_ret == 2)
						{
							// True�����뤬�ѹ����줿
							if      (tmp_posdata->trueid == 99999)
								tmp_posdata->trueid = 100000 + MAX_SPPOS - 1;
							else if (tmp_posdata->trueid > 100000 + MAX_SPPOS - 1)
								tmp_posdata->trueid = 100000;
							else if (tmp_posdata->trueid >= 100000)
								;
							else if (tmp_posdata->trueid < 0)
								tmp_posdata->trueid = m_tilenum - 1;
							else if (tmp_posdata->trueid > m_tilenum - 1)
								tmp_posdata->trueid = 0;

							refreshpos(m_cur.x, m_cur.y);
							drawwin();
						}
						else
						{
							refreshwin();
							drawwin();
							break;
						}
					}
				}
				else
				{	// �ޥåפ��ɤ߹��ޤ�Ƥ��ʤ��ٹ�
					warn_no_map();
				}
				break;
			case 'z':
				// �ޥåפ���Ȥ�񤭽Ф�
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{
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
						mapfp = new CFile;
						mapfp->write_map( m_path, &m_mapdata, m_posdata, m_spposdata, m_tiledata, m_pevent, m_sevent, m_fieldname, m_tilenum );
						delete(mapfp);
						return;
					}
					else if (tmp_ret == 2)
					{
						return;
					}
				}
				refreshwin();
				drawwin();
				break;
			default:
				continue;
				break;
		}
	}
}

void CWinMapEditor::warn_no_map()
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[MY_MSG_SYS_NO_MAP].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	refreshwin();
	drawwin();
}

bool CWinMapEditor::onkeypress_left()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.x > 0){
		m_cur.x--;			// �������뺸
		if (m_cur.x < m_dpos.x)
		{
			m_dpos.x--;		// ����������
			refreshwin();
		}
	}
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMapEditor::onkeypress_down()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.y < m_dpos.y + LINES && m_cur.y < m_mapdata.height - 1){
		m_cur.y++;			// �������벼����
		if (m_cur.y > m_dpos.y + LINES - 1)
		{
			m_dpos.y++;		// ����������
			refreshwin();
		}
	}
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMapEditor::onkeypress_up()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.y > 0){
		m_cur.y--;			// ��������夲��
		if (m_cur.y < m_dpos.y)
		{
			m_dpos.y--;		// �她������
			refreshwin();
		}
	}
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinMapEditor::onkeypress_right()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.x < m_dpos.x + COLS / 2 && m_cur.x < m_mapdata.width - 1){
		m_cur.x++;			// �������뱦
		if (m_cur.x > m_dpos.x + COLS / 2 - 1)
		{
			m_dpos.x++;		// ����������
			refreshwin();
		}
	}
	drawwin();
	return true;	// �����롼�׷�³
}

// �󼡸��κ�ɸ��켡�����������Ǥ��Ѵ�����ʥ����С��饤�ɡ�
int CWinMapEditor::xyton(int x, int y){
	return (y * m_mapdata.width + x);
}



