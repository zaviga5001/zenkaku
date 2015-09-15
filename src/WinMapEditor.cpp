#include "win.h"

CWinMapEditor::CWinMapEditor(CData* data, CConfig* config, CFile* file)
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_dpos.x = 0;		// マップ上の表示開始位置（窓の左上にくる）
	m_dpos.y = 0;		// マップ上の表示開始位置（窓の左上にくる）
	m_cur.x  = 0;		// カーソルの位置
	m_cur.y  = 0;		// カーソルの位置
	m_winx   = 0;		// 窓の表示開始位置（常に0）
	m_winy   = 0;		// 窓の表示開始位置（常に0）
	m_winw   = COLS / 2;	// 窓の幅（全角でカウント）
	m_winh   = LINES;	// 窓の高さ

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
		m_fieldname[i] = "　";
	}

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納
}

CWinMapEditor::~CWinMapEditor()
{
	if (m_this != NULL)	delwin(m_this);
	if (m_posdata != NULL)	delete[] m_posdata;
}

int CWinMapEditor::drawwin()
{
	// カーソル反転
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_REVERSE);
	// 画面再描画
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
			mvwaddnstr(m_this, y - m_dpos.y, adjx(x - m_dpos.x), "　", 2);
		}
		else
		{
			int tileno = gettile(x, y);

			int cpair = getcpair((int)m_tiledata[tileno].ch, (int)m_tiledata[tileno].bg);
			wattrset(m_this, COLOR_PAIR(cpair));
			mvwaddnstr(m_this, y - m_dpos.y, adjx(x - m_dpos.x), m_tiledata[tileno].tile.c_str(), 2);
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

	// スペシャルポジションIDかどうか判定
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
	timeout(-1);    // キー入力で待つ

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
				// タイル追加
				int tmp_copyid;
				if (m_data->get_flg(m_posdata[xyton(m_cur.x, m_cur.y)].flg) == true)
					tmp_copyid = m_posdata[xyton(m_cur.x, m_cur.y)].trueid;
				else
					tmp_copyid = m_posdata[xyton(m_cur.x, m_cur.y)].falseid;

				m_tiledata[m_tilenum] = m_tiledata[tmp_copyid];
				m_tilenum++;

				// 追加完了メッセージ
				nw_msg = new CWinMsg;
				nw_msg->m_msg = msg[MY_MSG_SYS_ADD_TILE].msg;
				nw_msg->setdefcpair(1, 0);
				nw_msg->startwin(true);
				delete(nw_msg);
				refreshwin();
				drawwin();
				break;
			case 'b':
				// フラグビットエディタ
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
						// IDが変更された
						if (tmp_id < 0)
							tmp_id = FLG_BITS * 32 - 1;
						if (tmp_id > FLG_BITS * 32 - 1)
							tmp_id = 0;

						tmp_old_id = tmp_id;
						continue;
					}

					// フラグ変更
					m_data->set_flg(tmp_id, tmp_value);

					if (tmp_ret)	break;
				}

				refreshwin();
				drawwin();
				break;
			case 'c':
				// コピー
				m_posbuf = m_posdata[xyton(m_cur.x, m_cur.y)];
				break;
			case 'v':
				// ペースト
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
				// アンドゥ
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
				// イベントエディタ
			case 'f':
				// イベントエディタ
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// マップが存在した
					int	tmp_id = 0;

					for ( ; ; )
					{
						nw_editvalue_event = new CWinEditValue_Event;
						if (ch == 'e')
						{
							nw_editvalue_event->push("StopEvent:ID",	&tmp_id,			TT_INT, 1);
							nw_editvalue_event->push("StopEvent:FLG ",	&m_sevent[tmp_id].flg,		TT_INT, 1);
							nw_editvalue_event->push("StopEvent:FLG BIT ",	&m_sevent[tmp_id].torf,		TT_INT, 1);
							nw_editvalue_event->push("StopEvent:HEIGHT",	&m_sevent[tmp_id].h,		TT_INT, 1);
							nw_editvalue_event->push("StopEvent:EVENT NO",	&m_sevent[tmp_id].event,	TT_INT, 1);
						}
						else
						{
							nw_editvalue_event->push("PointEvent:ID ",	&tmp_id,			TT_INT, 1);
							nw_editvalue_event->push("PointEvent:FLG",	&m_pevent[tmp_id].flg,		TT_INT, 1);
							nw_editvalue_event->push("PointEvent:FLG BIT",	&m_pevent[tmp_id].torf,		TT_INT, 1);
							nw_editvalue_event->push("PointEvent:HEIGHT ",	&m_pevent[tmp_id].h,		TT_INT, 1);
							nw_editvalue_event->push("PointEvent:EVENT NO ",&m_pevent[tmp_id].event,	TT_INT, 1);
						}

						int tmp_ret	= nw_editvalue_event->startwin(true);
						delete(nw_editvalue_event);

						if (tmp_ret == 1)
						{
							// IDが変更された
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
				{	// マップが読み込まれていない警告
					warn_no_map();
				}
				break;
			case 'h':
				nw_msg = new CWinMsg;
				nw_msg->m_msg = "Ａ：タイル追加nＢ：フラグビットエディタnＣ：コピーnＶ：ペーストnＵ：アンドゥnＱ：コピーマスクエディタnＥ：イベントエディタnＬ：ロードnＭ：マップ情報エディタnＮ：地名エディタnＰ：パレット表示nＴ：タイルエディタnＳ：スペシャルポジションエディタnＸ：ポジションエディタnＺ：セーブ終了";
				nw_msg->setsize(20,16);
				nw_msg->startwin(true);
				delete(nw_msg);
				refreshwin();
				drawwin();
				break;
			case 'l':
				// マップ番号を入力する
				nw_getpath = new CWinGetPath;
				nw_getpath->settitle(std::string(msg[MY_MSG_SYS_INP_MAPNO].msg));
				m_path = nw_getpath->startdialog(true);
				m_path = "data/qwert123/map/" + m_path;
				delete(nw_getpath);
			
			
				// マップサイズ、NextMapを取得
				m_mapdata = m_file->get_map_size(m_path);
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{
					// 以前のポジションテーブルがあれば、まず破棄する
					if (m_posdata != NULL)	delete[] m_posdata;
					// ポジションテーブル再生成
					m_posdata = new PosData[m_mapdata.height * m_mapdata.width];
					// マップの中身を読み込み
					m_tilenum = m_file->read_map(m_path, &m_mapdata, m_posdata, m_spposdata, m_tiledata, m_pevent, m_sevent, m_fieldname);
				}
				m_cur.x = 1;
				m_cur.y = 1;
				refreshwin();
				drawwin();
				break;
			case 'm':
				// マップ情報エディタ
				nw_editvalue = new CWinEditValue;

				nw_editvalue->push("NEXTMAP 上", &m_mapdata.nextmap_u, TT_INT, 1);
				nw_editvalue->push("NEXTMAP 下", &m_mapdata.nextmap_d, TT_INT, 1);
				nw_editvalue->push("NEXTMAP 左", &m_mapdata.nextmap_l, TT_INT, 1);
				nw_editvalue->push("NEXTMAP 右", &m_mapdata.nextmap_r, TT_INT, 1);

				nw_editvalue->startwin(true);
				delete(nw_editvalue);
				refreshwin();
				drawwin();
				break;
			case 'n':
				// 地名エディタ
				nw_editvalue = new CWinEditValue;

				char tmp_str[4];
				for (int i = 0; i < MAX_FNAME; i++)
				{
					sprintf(tmp_str, "%02d", i);
					nw_editvalue->push(std::string(tmp_str), &m_fieldname[i], TT_STR, 1);
				}
				nw_editvalue->startwin(true);
				delete(nw_editvalue);
				refreshwin();
				drawwin();
				break;
			case 'p':
				// パレット表示
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// マップが存在した
					nw_select1icon = new CWinSelect1Icon;
					nw_select1icon->setsize(10, 10);
					for (int i = 0; i < COLOR_NUM * COLOR_NUM; i++)
					{
						nw_select1icon->m_cols = 8;
						nw_select1icon->push("● ", i, i);
					}
					nw_select1icon->startwin(true);
					delete(nw_select1icon);
					refreshwin();
					drawwin();
				}
				else
				{	// マップが読み込まれていない警告
					warn_no_map();
				}
				break;
			case 'q':
				// コピーマスクエディタ
				for ( ; ; )
				{
					nw_editvalue_cmask = new CWinEditValue_Cmask();

					nw_editvalue_cmask->push("FLG ",	&m_posmsk.flg,		TT_INT, 1);
					nw_editvalue_cmask->push("FALSE ID",	&m_posmsk.falseid,	TT_INT, 1);
					nw_editvalue_cmask->push("TRUE  ID",	&m_posmsk.trueid,	TT_INT, 1);
					nw_editvalue_cmask->push("NAME",	&m_posmsk.name,		TT_STR, 1);
					nw_editvalue_cmask->push("ENEMY ",	&m_posmsk.enemy,	TT_INT, 1);
					nw_editvalue_cmask->push("ENCOUNT ",	&m_posmsk.encount,	TT_INT, 1);
					nw_editvalue_cmask->setsize(20, 8);
					tmp_ret = nw_editvalue_cmask->startwin(true);
					delete(nw_editvalue_cmask);

					if (!tmp_ret)	break;
				}

				refreshwin();
				drawwin();
				break;
			case 't':
				// タイルエディタ
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// マップが存在した
					int	tmp_id = gettile(m_cur.x, m_cur.y);

					for ( ; ; )
					{
						nw_editvalue_tile = new CWinEditValue_Tile;
						nw_editvalue_tile->push("FALSE ID",	&tmp_id,			TT_INT, 1);
						nw_editvalue_tile->push("FALSE CHAR",	&m_tiledata[tmp_id].tile,	TT_STR, 1, getcpair(m_tiledata[tmp_id].ch, m_tiledata[tmp_id].bg));
						nw_editvalue_tile->push("FALSE CH",	&m_tiledata[tmp_id].ch,		TT_INT, 1, getcpair(m_tiledata[tmp_id].ch, 0));
						nw_editvalue_tile->push("FALSE BG",	&m_tiledata[tmp_id].bg,		TT_INT, 1, getcpair(m_tiledata[tmp_id].bg, 0));
						nw_editvalue_tile->push("FALSE ATTR",	&m_tiledata[tmp_id].attr,	TT_INT, 1);
						nw_editvalue_tile->push("FALSE HEIGHT",	&m_tiledata[tmp_id].height,	TT_INT, 1);
						nw_editvalue_tile->push("FALSE MOVE",	&m_tiledata[tmp_id].move,	TT_INT, 1);

						int tmp_ret_id	= nw_editvalue_tile->startwin(true);
						delete(nw_editvalue_tile);

						if (tmp_ret_id == 1)
						{
							// タイルが変更された
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
				{	// マップが読み込まれていない警告
					warn_no_map();
				}
				break;
			case 's':
				// スペシャルポジションデータエディタ
			case 'x':
				// ポジションデータエディタ
				if (m_mapdata.height > 0 && m_mapdata.width > 0)
				{	// マップが存在した
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
								nw_getpath->settitle(std::string(msg[MY_MSG_SYS_INP_SPOS].msg));
								std::string spos = nw_getpath->startdialog(true);
								delete(nw_getpath);
								posi = atoi(spos.c_str());
								if (posi < 0 || posi >= MAX_SPPOS)
								{
									posi = -1;
									continue;
								}
								tmp_posdata = &m_spposdata[posi];
							}
						}

						nw_editvalue_pos = new CWinEditValue_Pos;
						// 参照フラグ
						nw_editvalue_pos->push("FLAG",		&tmp_posdata->flg,	TT_INT, 1);
						nw_editvalue_pos->push("FALSE ID",	&tmp_posdata->falseid,	TT_INT, 1);
						nw_editvalue_pos->push("TRUE  ID",	&tmp_posdata->trueid,	TT_INT, 1);
						nw_editvalue_pos->push("F NAME",	&tmp_posdata->name,	TT_INT, 1);
						nw_editvalue_pos->push("ENEMY ",	&tmp_posdata->enemy,	TT_INT, 1);
						nw_editvalue_pos->push("ENCOUNT ",	&tmp_posdata->encount,	TT_INT, 1);
						nw_editvalue_pos->push("--------------",	NULL,	TT_SPC, 1);

						if (tmp_posdata->falseid >= 100000)
							nw_editvalue_pos->push("FALSE CHAR",	 &tmp_posdata->falseid,	TT_INT, 1);
						else
							nw_editvalue_pos->push("FALSE CHAR",	 &m_tiledata[tmp_posdata->falseid].tile,	TT_STR, 1, getcpair(m_tiledata[tmp_posdata->falseid].ch, m_tiledata[tmp_posdata->falseid].bg));

						if (tmp_posdata->trueid >= 100000)
							nw_editvalue_pos->push("TRUE  CHAR",	 &tmp_posdata->trueid,	TT_INT, 1);
						else
							nw_editvalue_pos->push("TRUE  CHAR",	 &m_tiledata[tmp_posdata->trueid ].tile,	TT_STR, 1, getcpair(m_tiledata[tmp_posdata->trueid ].ch, m_tiledata[tmp_posdata->trueid ].bg));

						nw_editvalue_pos->push("F NAMESTR ",	 &m_fieldname[(int)tmp_posdata->name],	TT_STR, 1);

						int tmp_ret = nw_editvalue_pos->startwin(true);
						delete(nw_editvalue_pos);

						if (tmp_ret == 1)
						{
							// Falseタイルが変更された
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
							// Trueタイルが変更された
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
				{	// マップが読み込まれていない警告
					warn_no_map();
				}
				break;
			case 'z':
				// マップの中身を書き出し
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
						m_file->write_map( m_path, &m_mapdata, m_posdata, m_spposdata, m_tiledata, m_pevent, m_sevent, m_fieldname, m_tilenum );
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
		m_cur.x--;			// カーソル左
		if (m_cur.x < m_dpos.x)
		{
			m_dpos.x--;		// 左スクロール
			refreshwin();
		}
	}
	drawwin();
	return true;	// キーループ継続
}
bool CWinMapEditor::onkeypress_down()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.y < m_dpos.y + LINES && m_cur.y < m_mapdata.height - 1){
		m_cur.y++;			// カーソル下げる
		if (m_cur.y > m_dpos.y + LINES - 1)
		{
			m_dpos.y++;		// 下スクロール
			refreshwin();
		}
	}
	drawwin();
	return true;	// キーループ継続
}
bool CWinMapEditor::onkeypress_up()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.y > 0){
		m_cur.y--;			// カーソル上げる
		if (m_cur.y < m_dpos.y)
		{
			m_dpos.y--;		// 上スクロール
			refreshwin();
		}
	}
	drawwin();
	return true;	// キーループ継続
}
bool CWinMapEditor::onkeypress_right()
{
	chg_attr(m_cur.x - m_dpos.x, m_cur.y - m_dpos.y, WA_NORMAL);
	if (m_cur.x < m_dpos.x + COLS / 2 && m_cur.x < m_mapdata.width - 1){
		m_cur.x++;			// カーソル右
		if (m_cur.x > m_dpos.x + COLS / 2 - 1)
		{
			m_dpos.x++;		// 右スクロール
			refreshwin();
		}
	}
	drawwin();
	return true;	// キーループ継続
}

// 二次元の座標を一次元の配列要素に変換する（オーバーライド）
int CWinMapEditor::xyton(int x, int y){
	return (y * m_mapdata.width + x);
}



