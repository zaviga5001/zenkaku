#include "win.h"

CWinPartyEditor::CWinPartyEditor(CConfig* config)
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;		// 窓の表示開始位置（常に0）
	m_winy   = 0;		// 窓の表示開始位置（常に0）
	m_winw   = COLS / 2;	// 窓の幅（全角でカウント）
	m_winh   = LINES;	// 窓の高さ
	m_maxwidth = 0;		// 文字列の最大幅

	m_data = new CData;

	// ここでシナリオを読み込め

	// パーティ読み込み
	for (m_partynum_in_file = 0; ; m_partynum_in_file++)
	{
		if (!read_party(m_partynum_in_file))	break;

		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", m_partynum_in_file);
		push(std::string(tmp_buf), m_partynum_in_file);
	}
	push("新規作成", m_partynum_in_file);
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

void CWinPartyEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinPartyEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.length())
		m_maxwidth = str.length() / 2;
}
void CWinPartyEditor::change(const std::string str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	m_maxwidth = 0;
	for (int i = 0; i < m_list[i].length(); i++)
	{
		if (adjx(m_maxwidth) < m_list[i].length())
			m_maxwidth = m_list[i].length() / 2;
	}
}


// パーティファイル読み込み
bool CWinPartyEditor::read_party(int index)
{
	CFile*	fp;
	fp = new CFile;

	int ret = fp->read_party(m_data, index);

	delete(fp);

	return(ret);
}

// パーティファイル書き込み
void CWinPartyEditor::write_party(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_party(m_data, index);

	delete(fp);
}

void CWinPartyEditor::keyloop()
{
	timeout(-1);    // キー入力で待つ

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
	return true;	// キーループ継続
}
bool CWinPartyEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPartyEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPartyEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPartyEditor::onkeypress_ok()
{
	EnemyParty*	tmp_ep;
	EnemyParty	tmp_epo;
	CWinEditValue*	nw_editvalue;

	// カーソル位置のパーティ情報読み込み
	if (m_cur.y == m_partynum_in_file)
	{ // 新規追加
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
		// ポインタセット
		nw_editvalue->push("敵：０",		&tmp_ep->enemy[0],	TT_INT, 1);
		nw_editvalue->push("敵：１",		&tmp_ep->enemy[1],	TT_INT, 1);
		nw_editvalue->push("敵：２",		&tmp_ep->enemy[2],	TT_INT, 1);
		nw_editvalue->push("敵：３",		&tmp_ep->enemy[3],	TT_INT, 1);
		nw_editvalue->push("敵：４",		&tmp_ep->enemy[4],	TT_INT, 1);
		nw_editvalue->push("敵：５",		&tmp_ep->enemy[5],	TT_INT, 1);
		nw_editvalue->push("敵：６",		&tmp_ep->enemy[6],	TT_INT, 1);
		nw_editvalue->push("敵：７",		&tmp_ep->enemy[7],	TT_INT, 1);
		nw_editvalue->push("敵：８",		&tmp_ep->enemy[8],	TT_INT, 1);
		nw_editvalue->push("敵：９",		&tmp_ep->enemy[9],	TT_INT, 1);
		nw_editvalue->push("敵：Ａ",		&tmp_ep->enemy[10],	TT_INT, 1);
		nw_editvalue->push("敵：Ｂ",		&tmp_ep->enemy[11],	TT_INT, 1);
		nw_editvalue->push("敵：Ｃ",		&tmp_ep->enemy[12],	TT_INT, 1);
		nw_editvalue->push("敵：Ｄ",		&tmp_ep->enemy[13],	TT_INT, 1);
		nw_editvalue->push("敵：Ｅ",		&tmp_ep->enemy[14],	TT_INT, 1);
		nw_editvalue->push("敵：Ｆ",		&tmp_ep->enemy[15],	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("アイテム：０",	&tmp_ep->item[0],	TT_INT, 1);
		nw_editvalue->push("アイテム率：０",	&tmp_ep->item_r[0],	TT_INT, 1);
		nw_editvalue->push("アイテム：１",	&tmp_ep->item[1],	TT_INT, 1);
		nw_editvalue->push("アイテム率：１",	&tmp_ep->item_r[1],	TT_INT, 1);
		nw_editvalue->push("アイテム：２",	&tmp_ep->item[2],	TT_INT, 1);
		nw_editvalue->push("アイテム率：２",	&tmp_ep->item_r[2],	TT_INT, 1);
		nw_editvalue->push("アイテム：３",	&tmp_ep->item[3],	TT_INT, 1);
		nw_editvalue->push("アイテム率：３",	&tmp_ep->item_r[3],	TT_INT, 1);
		nw_editvalue->push("アイテム：４",	&tmp_ep->item[4],	TT_INT, 1);
		nw_editvalue->push("アイテム率：４",	&tmp_ep->item_r[4],	TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("フラグ",		&tmp_ep->flg,		TT_INT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		// アイテム書き出し
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
			{ // 新規追加だった
				char tmp_buf[6];
				sprintf(tmp_buf, "%05d", m_partynum_in_file);
				change(tmp_buf, m_partynum_in_file, m_partynum_in_file);
				m_partynum_in_file++;
				push("新規作成", m_data->m_itemnum);
			}
			write_party(m_cur.y);
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinPartyEditor::onkeypress_cancel()
{
	return false;	// 終了
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



