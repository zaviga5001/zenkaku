#include "win.h"

CWinItemEditor::CWinItemEditor(CConfig* config)
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

	m_data->m_itemnum = 0;

	// ここでシナリオを読み込め

	// 敵キャラ読み込み
	read_item();

	for (int i = 0; i < m_data->m_itemnum; i++)
	{
		push(m_data->m_item[i].name, i);
	}
	push("新規作成", m_data->m_itemnum);
}

CWinItemEditor::~CWinItemEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinItemEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinItemEditor::push(const CString str, const int id)
{
	push(str, id, m_cpair);
}
void CWinItemEditor::push(const CString str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.Len())
		m_maxwidth = str.Len() / 2;
}
void CWinItemEditor::change(const CString str, const int id, const int index)
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


// アイテムファイル読み込み
void CWinItemEditor::read_item()
{
	CFile*	fp;
	fp = new CFile;

	fp->read_item(m_data);

	delete(fp);
}

// アイテムファイル書き込み
void CWinItemEditor::write_item()
{
	CFile*	fp;
	fp = new CFile;

	fp->write_item(m_data);

	delete(fp);
}

void CWinItemEditor::keyloop()
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

bool CWinItemEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinItemEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinItemEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinItemEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].Len() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinItemEditor::onkeypress_ok()
{
	ItemData*	tmp_it;
	ItemData	tmp_ito;

	CWinEditValue*	nw_editvalue;

	// カーソル位置のアイテム情報読み込み
	if (m_cur.y == m_data->m_itemnum)
	{ // 新規追加
		tmp_it = &tmp_ito;
	}
	else
	{
		tmp_it = &m_data->m_item[m_cur.y];
	}

	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// ポインタセット
		nw_editvalue->push("名前",	&tmp_it->name,		TT_CST, 1);
		nw_editvalue->push("種類",	&tmp_it->type,		TT_INT, 1);
		nw_editvalue->push("価格",	&tmp_it->price,		TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("内容：０",	&tmp_it->elm[0],	TT_INT, 1);
		nw_editvalue->push("内容：１",	&tmp_it->elm[1],	TT_INT, 1);
		nw_editvalue->push("内容：２",	&tmp_it->elm[2],	TT_INT, 1);
		nw_editvalue->push("内容：３",	&tmp_it->elm[3],	TT_INT, 1);
		nw_editvalue->push("内容：４",	&tmp_it->elm[4],	TT_INT, 1);

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
			change(tmp_it->name, m_cur.y, m_cur.y);
			if (m_cur.y == m_data->m_itemnum)
			{ // 新規追加だった
				m_data->m_itemnum++;
				push("新規作成", m_data->m_itemnum);

				m_data->m_item.push_back(*tmp_it);
			}
			write_item();
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinItemEditor::onkeypress_cancel()
{
	return false;	// 終了
}




void CWinItemEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



