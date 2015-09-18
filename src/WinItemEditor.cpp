#include "win.h"

CWinItemEditor::CWinItemEditor(CData* data, CConfig* config, CFile* file)
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
	m_itemnum = 0;         // 読み込んだアイテムの数

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納

	// ここでシナリオを読み込め（不要）

	// アイテム読み込み
	read_item_list();

	for (int i = 0; i < m_itemnum; i++)
	{
		push(m_data->m_item[i].name, i);
	}
	push("新規作成", m_itemnum);
}

CWinItemEditor::~CWinItemEditor()
{
}

int CWinItemEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinItemEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinItemEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (m_maxwidth < CMyStr::length(str))
		m_maxwidth = CMyStr::length(str);
}
void CWinItemEditor::change(const std::string str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	if (m_maxwidth < CMyStr::length(m_list[index]))
		m_maxwidth = CMyStr::length(m_list[index]);
}


// アイテム全て読み込み
void CWinItemEditor::read_item_list()
{
	m_itemnum = m_file->read_item(m_data);
}

// アイテムファイル読み込み
void CWinItemEditor::read_item(int index)
{
	m_file->read_item(m_data, index);
}

// アイテムファイル書き込み
void CWinItemEditor::write_item(int index)
{
	m_file->write_item(m_data, index);
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
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinItemEditor::onkeypress_ok()
{
	CWinEditValue*	nw_editvalue;
	if (m_cur.y == m_itemnum)
	{	// 新規作成
		Item tmp_item;
		int i;
		for (i = 0; i < MAX_ITEMNAME; i++)
		{
			tmp_item.name[i] = '\0';
		}
		tmp_item.type = IT_FOOD;
		tmp_item.price = 0;
		for (i = 0; i < ITEM_ELM; i++)
		{
			tmp_item.elm[i] = 0;
		}
		for (i = 0; i < MAX_ITEMPROF; i++)
		{
			tmp_item.prof[i] = '\0';
		}
		m_data->m_item.push_back(tmp_item);
	}
	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// ポインタセット
		nw_editvalue->push("名前",	 m_data->m_item[m_cur.y].name,		TT_CHR, MAX_ITEMNAME);
		nw_editvalue->push("種類",	&m_data->m_item[m_cur.y].type,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("価格",	&m_data->m_item[m_cur.y].price,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("内容：０",	&m_data->m_item[m_cur.y].elm[0],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("内容：１",	&m_data->m_item[m_cur.y].elm[1],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("内容：２",	&m_data->m_item[m_cur.y].elm[2],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("内容：３",	&m_data->m_item[m_cur.y].elm[3],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("内容：４",	&m_data->m_item[m_cur.y].elm[4],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("説明文",	 m_data->m_item[m_cur.y].prof,		TT_CHR, MAX_ITEMPROF);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		// アイテム書き出し
		CWinSelect1Item* nw_select1item;
		nw_select1item = new CWinSelect1Item;
		nw_select1item->setsize(20, 5);
		nw_select1item->movewin(5, 1);
		nw_select1item->m_msg = msg[MY_MSG_SYS_SAVE_YN].msg;
		nw_select1item->m_split = 2;
		nw_select1item->m_wpos.y = 3;
		nw_select1item->push(msg[MY_MSG_SYS_YES].msg,    1);
		nw_select1item->push(msg[MY_MSG_SYS_NO].msg,     2);
		nw_select1item->push(msg[MY_MSG_SYS_CANSEL].msg, 0);
		int tmp_ret = nw_select1item->startwin(true);
		delete(nw_select1item);

		if (tmp_ret == 0)
		{
			continue;
		}
		else if (tmp_ret == 2)
		{
			if (m_cur.y == m_itemnum)
			{	// 新規追加だったら元に戻す
				m_data->m_item.pop_back();
			}
			else
			{	// アイテム名再度読み込み（リストを元に戻す）
				read_item(m_cur.y);
			}
		}
		else if (tmp_ret == 1)
		{
			write_item(m_cur.y);
			change(std::string(m_data->m_item[m_cur.y].name), m_cur.y, m_cur.y);
			if (m_cur.y == m_itemnum)
			{ // 新規追加だった
				m_itemnum++;
				push("新規作成", m_itemnum);
			}
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



