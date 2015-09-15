#include "win.h"

CWinPGEditor::CWinPGEditor(CData* data, CConfig* config, CFile* file)
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

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納

	// ここでシナリオを読み込め

	// パーティ群読み込み
	for (m_data->m_enemypgnum = 0; ; m_data->m_enemypgnum++)
	{
		if (!read_pg(m_data->m_enemypgnum))	break;

		char tmp_buf[6];
		sprintf(tmp_buf, "%05d", m_data->m_enemypgnum);
		push(std::string(tmp_buf), m_data->m_enemypgnum);
	}
	push("新規作成", m_data->m_enemypgnum);
}

CWinPGEditor::~CWinPGEditor()
{
}

int CWinPGEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinPGEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinPGEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (adjx(m_maxwidth) < str.length())
		m_maxwidth = str.length() / 2;
}
void CWinPGEditor::change(const std::string str, const int id, const int index)
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


// パーティ群ファイル読み込み
bool CWinPGEditor::read_pg(int index)
{
	int ret = m_file->read_pg(m_data, index);

	return(ret);
}

// パーティ群ファイル書き込み
void CWinPGEditor::write_pg(int index)
{
	m_file->write_pg(m_data, index);
}

void CWinPGEditor::keyloop()
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

bool CWinPGEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPGEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPGEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPGEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinPGEditor::onkeypress_ok()
{
	int	tmp_vct;
	int	tmp_ret;
	char	tmp_str[4];
	std::string	tmp_cs;

	EnemyPG*	tmp_pg;
	EnemyPG		tmp_pgo;
	EnemyPGValue	tmp_pgvo;
	if (m_cur.y == m_data->m_enemypgnum)
	{ // 新規追加
		tmp_pg = &tmp_pgo;
		tmp_pgo.elm.push_back(tmp_pgvo);
	}
	else
	{ // 既存レコード
		tmp_pg = &m_data->m_enemypg[m_cur.y];
	}

	CWinEditValue*	nw_editvalue;

	for ( ; ; )
	{
		tmp_vct = 0;
		tmp_ret = 0;

		nw_editvalue = new CWinEditValue;
		// ポインタセット
		for (int i = 0; i < tmp_pg->elm.size(); i++)
		{
			sprintf(tmp_str, "%02d", i);
			tmp_cs = tmp_str;
			nw_editvalue->push("パーティID" + tmp_cs,	&tmp_pg->elm[i].party,		TT_INT, 1);
			nw_editvalue->push("パーティ率" + tmp_cs,	&tmp_pg->elm[i].party_r,	TT_INT, 1);
		}
		nw_editvalue->push("パーティ追加", &tmp_vct, TT_VCT, 1);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);

		if (tmp_vct == 1)
		{ // editvalueの中でvector追加が指示された
			EnemyPGValue	tmp_pgvo2;
			tmp_pg->elm.push_back(tmp_pgvo2);
			tmp_ret = 1;
		}
		else
		{
			// パーティ書き出し
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
			{ // 新規追加だった
				char tmp_buf[6];
				sprintf(tmp_buf, "%05d", m_cur.y);
				change(tmp_buf, m_cur.y, m_cur.y);
				m_data->m_enemypgnum++;

				push("新規作成", m_data->m_enemypgnum);

				m_data->m_enemypg.push_back(*tmp_pg);
			}
			write_pg(m_cur.y);
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
bool CWinPGEditor::onkeypress_cancel()
{
	return false;	// 終了
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



