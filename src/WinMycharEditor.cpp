#include "win.h"

CWinMycharEditor::CWinMycharEditor(CData* data, CConfig* config, CFile* file)
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

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納

	// ここでシナリオを読み込め

	// マイキャラ読み込み
	read_mychar(0);

	// 表示
	push("シナリオID",		&m_data->m_mychar[0].id,	TT_INT,	1);
	push("種族",			&m_data->m_mychar[0].race,	TT_INT,	1);
	push("職業",			&m_data->m_mychar[0].job,	TT_INT,	1);
	push("属性",			&m_data->m_mychar[0].type,	TT_INT,	1);
	push("性別",			&m_data->m_mychar[0].gender,	TT_INT,	1);
	push("名前",			&m_data->m_mychar[0].name,	TT_STR,	1);
	push("タイル",			&m_data->m_mychar[0].tile,	TT_STR,	1);
	push("文字色",			&m_data->m_mychar[0].ch,	TT_INT,	1);
	push("背景色",			&m_data->m_mychar[0].bg,	TT_INT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("ステータス",		&m_data->m_mychar[0].status,	TT_INT,	1);
	push("レベル",			&m_data->m_mychar[0].level,	TT_INT,	1);
	push("経験値",			&m_data->m_mychar[0].exp,	TT_INT,	1);
	push("体力（現在）",		&m_data->m_mychar[0].hp.p,	TT_INT,	1);
	push("体力（一時的最大）",	&m_data->m_mychar[0].hp.t,	TT_INT,	1);
	push("体力（最大）",		&m_data->m_mychar[0].hp.m,	TT_INT,	1);
	push("スキル（現在）",		&m_data->m_mychar[0].sp.p,	TT_INT,	1);
	push("スキル（一時的最大）",	&m_data->m_mychar[0].sp.t,	TT_INT,	1);
	push("スキル（最大）",		&m_data->m_mychar[0].sp.m,	TT_INT,	1);
	push("攻撃力（現在）",		&m_data->m_mychar[0].ap.p,	TT_INT,	1);
	push("攻撃力（一時的最大）",	&m_data->m_mychar[0].ap.t,	TT_INT,	1);
	push("攻撃力（最大）",		&m_data->m_mychar[0].ap.m,	TT_INT,	1);
	push("防御力（現在）",		&m_data->m_mychar[0].gp.p,	TT_INT,	1);
	push("防御力（一時的最大）",	&m_data->m_mychar[0].gp.t,	TT_INT,	1);
	push("防御力（最大）",		&m_data->m_mychar[0].gp.m,	TT_INT,	1);
	push("魔法力（現在）",		&m_data->m_mychar[0].mp.p,	TT_INT,	1);
	push("魔法力（一時的最大）",	&m_data->m_mychar[0].mp.t,	TT_INT,	1);
	push("魔法力（最大）",		&m_data->m_mychar[0].mp.m,	TT_INT,	1);
	push("回避力（現在）",		&m_data->m_mychar[0].ep.p,	TT_INT,	1);
	push("回避力（一時的最大）",	&m_data->m_mychar[0].ep.t,	TT_INT,	1);
	push("回避力（最大）",		&m_data->m_mychar[0].ep.m,	TT_INT,	1);
	push("素早さ（現在）",		&m_data->m_mychar[0].fp.p,	TT_INT,	1);
	push("素早さ（一時的最大）",	&m_data->m_mychar[0].fp.t,	TT_INT,	1);
	push("素早さ（最大）",		&m_data->m_mychar[0].fp.m,	TT_INT,	1);
	push("器用さ（現在）",		&m_data->m_mychar[0].dp.p,	TT_INT,	1);
	push("器用さ（一時的最大）",	&m_data->m_mychar[0].dp.t,	TT_INT,	1);
	push("器用さ（最大）",		&m_data->m_mychar[0].dp.m,	TT_INT,	1);
	push("満腹度",			&m_data->m_mychar[0].food,	TT_INT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("右手武器",		&m_data->m_mychar[0].rweapon,	TT_INT,	1);
	push("左手武器",		&m_data->m_mychar[0].lweapon,	TT_INT,	1);
	push("兜",			&m_data->m_mychar[0].helm,	TT_INT,	1);
	push("防具",			&m_data->m_mychar[0].armor,	TT_INT,	1);
	push("マント",			&m_data->m_mychar[0].mant,	TT_INT,	1);
	push("靴",			&m_data->m_mychar[0].boots,	TT_INT,	1);
	push("装飾品",			&m_data->m_mychar[0].equip,	TT_INT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("習得魔法",		&m_data->m_mychar[0].magic,	TT_INT,	1);
	push("魔法経験値",		&m_data->m_mychar[0].magicexp,	TT_INT,	1);
	push("属性奥義",		&m_data->m_mychar[0].fight,	TT_INT,	1);
	push("属性経験値",		&m_data->m_mychar[0].fightexp,	TT_INT,	1);
	push("習得スキル",		&m_data->m_mychar[0].skill,	TT_INT,	1);
	push("スキル経験値",		&m_data->m_mychar[0].skillexp,	TT_INT,	1);
	push("呪い",			&m_data->m_mychar[0].curse,	TT_INT,	1);
	push("------------------",	NULL,				TT_SPC,	1);
	push("プロフィール",		&m_data->m_mychar[0].prof,	TT_STR,	1);

}

CWinMycharEditor::~CWinMycharEditor()
{
}

int CWinMycharEditor::drawwin()
{
	setedit(m_wpos.x, m_wpos.y, &m_cur.y, &m_dpos.y, m_name, m_value, m_cp);
	return true;
}

void CWinMycharEditor::push(const std::string str, void * ptr, const int chr, const int num)
{
	push(str, ptr, chr, num, m_cpair);
}
void CWinMycharEditor::push(const std::string str, void * ptr, const int chr, const int num, const int cpair)
{
	m_name.push_back(str);
	m_ptr.push_back(ptr);
	m_my_tt.push_back(chr);
	m_size.push_back(num);
	m_value.push_back(encode(ptr, chr, num));
	m_cp.push_back(cpair);
}

std::string CWinMycharEditor::encode(void * ptr, const int chr, const int num)
{
	std::string	tmp_buf;

	switch(chr)
	{
		case TT_STR:	// Char型が連結した文字列
			tmp_buf = *(std::string*)ptr;
			break;
		case TT_SPC:	// スペーサー
		case TT_VCT:	// ベクタ追加
			tmp_buf = "";
			break;
		case TT_INT:	// Int型
			tmp_buf = mystd::to_string(*(int*)ptr);
			break;
		default:
			break;
	}
	return (tmp_buf);
}

void CWinMycharEditor::decode(std::string* str, void *ptr, const int chr)
{
	switch(chr)
	{
		case TT_STR:
			*(std::string*)ptr = *(std::string*)str;
			break;
		case TT_INT:
			*(int*)ptr = atoi(str->c_str());
		default:
			break;
	}
}


// マイキャラファイル読み込み
void CWinMycharEditor::read_mychar(int id)
{
	m_file->read_mychar(m_data, id);
}

// マイキャラファイル書き込み
void CWinMycharEditor::write_mychar(int id)
{
	m_file->write_mychar(m_data, id);
}

void CWinMycharEditor::keyloop()
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

bool CWinMycharEditor::onkeypress_left()
{
	drawwin();
	return true;	// キーループ継続
}
bool CWinMycharEditor::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;
	if (m_my_tt[m_cur.y] == TT_SPC)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMycharEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	if (m_my_tt[m_cur.y] == TT_SPC)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinMycharEditor::onkeypress_right()
{
	drawwin();
	return true;	// キーループ継続
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
	return true;	// キーループ継続
}
bool CWinMycharEditor::onkeypress_cancel()
{
	// マイキャラ書き出し
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
		write_mychar(0);
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



