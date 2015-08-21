#include "win.h"

CWinShopEditor::CWinShopEditor(CConfig* config)
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

	// ショップ読み込み
	for (m_shopnum_in_file = 0; ; m_shopnum_in_file++)
	{
		if (!read_shop(m_shopnum_in_file))	break;

		push(m_data->m_shop.name, m_shopnum_in_file);
	}
	push("新規作成", m_shopnum_in_file);
}

CWinShopEditor::~CWinShopEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinShopEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinShopEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinShopEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.length())
		m_maxwidth = str.length() / 2;
}
void CWinShopEditor::change(const std::string str, const int id, const int index)
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


// ショップファイル読み込み
bool CWinShopEditor::read_shop(int index)
{
	CFile*	fp;
	fp = new CFile;

	int ret = fp->read_shop(m_data, index);

	delete(fp);

	return(ret);
}

// ショップファイル書き込み
void CWinShopEditor::write_shop(int index)
{
	CFile*	fp;
	fp = new CFile;

	fp->write_shop(m_data, index);

	delete(fp);
}

void CWinShopEditor::keyloop()
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

bool CWinShopEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShopEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShopEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShopEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinShopEditor::onkeypress_ok()
{
	int		tmp_vct;
	int		tmp_ret;
	char		tmp_str[4];
	std::string		tmp_cs;

	ShopData*	tmp_sh;
	ShopData	tmp_sho;
	ShopValue	tmp_shvo;
	CWinEditValue*	nw_editvalue;

	// カーソル位置のショップ情報読み込み
	if (m_cur.y == m_shopnum_in_file)
	{ // 新規追加
		tmp_sh = &tmp_sho;
		tmp_sh->elm.push_back(tmp_shvo);
	}
	else
	{
		read_shop(m_cur.y);
		tmp_sh = &m_data->m_shop;
	}

	for ( ; ; )
	{
		tmp_vct = 0;
		tmp_ret = 0;

		nw_editvalue = new CWinEditValue;
		// ポインタセット
		nw_editvalue->push("名前",	&tmp_sh->name,		TT_CST, 1);
		nw_editvalue->push("種類",	&tmp_sh->type,		TT_INT, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		for (int i = 0; i < tmp_sh->elm.size(); i++)
		{
			sprintf(tmp_str, "%02d", i);
			tmp_cs = tmp_str;
			nw_editvalue->push("アイテムID" + tmp_cs,	&tmp_sh->elm[i].item,		TT_INT, 1);
			nw_editvalue->push("在庫数" + tmp_cs,		&tmp_sh->elm[i].stock,		TT_INT, 1);
			nw_editvalue->push("特別価格" + tmp_cs,		&tmp_sh->elm[i].spprice,	TT_INT, 1);
		}
		nw_editvalue->push("アイテム追加", &tmp_vct, TT_VCT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		if (tmp_vct == 1)
		{ // editvalueの中でvector追加が指示された
			ShopValue	tmp_shvo2;
			tmp_sh->elm.push_back(tmp_shvo2);
			tmp_ret = 1;
		}
		else
		{
			// アイテム書き出し
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
			change(tmp_sh->name, m_cur.y, m_cur.y);
			if (m_cur.y == m_shopnum_in_file)
			{ // 新規追加だった
				m_data->m_shop = *tmp_sh;
				m_shopnum_in_file++;

				push("新規作成", m_shopnum_in_file);

			}
			write_shop(m_cur.y);
			if (tmp_vct == 1)
			{ // editvalueの中でvector追加が指示された
				continue;
			}
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinShopEditor::onkeypress_cancel()
{
	return false;	// 終了
}




void CWinShopEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}



