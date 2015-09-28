#include "win.h"

CWinEnemyEditor::CWinEnemyEditor(CData* data, CConfig* config, CFile* file)
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
	m_enemynum = 0;		// 読み込んだ敵キャラの数

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納

	// ここでシナリオを読み込め（不要）

	// 敵キャラ一括読み込みして、ついでにセレクトリスト用に保存する
	read_enemy_list();

	// アイテム一括読み込みしてセレクトリスト用に保存する
	read_item_list();

	// 属性リストをセレクトリスト用に保存する
	read_type_list();

	// 攻撃方法リストをセレクトリスト用に保存する
	read_fight_list();

	for (int i = 0; i < m_enemynum; i++)
	{
		push(std::string(m_data->m_enemy[i].name), i);
	}
	push("新規作成", m_enemynum);
}

CWinEnemyEditor::~CWinEnemyEditor()
{
}

int CWinEnemyEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinEnemyEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinEnemyEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (m_maxwidth < CMyStr::length(str))
		m_maxwidth = CMyStr::length(str);
}
void CWinEnemyEditor::change(const std::string str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	if (m_maxwidth < CMyStr::length(m_list[index]))
		m_maxwidth = CMyStr::length(m_list[index]);
}


// アイテム全て読み込み
void CWinEnemyEditor::read_item_list()
{
	m_itemnum = m_file->read_item(m_data);
	for (int i = 0; i < m_itemnum; i++)
	{
		m_itemlist.push_back(std::string(m_data->m_item[i].name));
	}
}

// 敵キャラ全て読み込み
void CWinEnemyEditor::read_enemy_list()
{
	m_enemynum = m_file->read_enemy(m_data);
	for (int i = 0; i < m_enemynum; i++)
	{
		m_enemylist.push_back(std::string(m_data->m_enemy[i].name));
	}
}

// 敵キャラファイル読み込み
void CWinEnemyEditor::read_enemy(int index)
{
	m_file->read_enemy(m_data, index);
}

// 敵キャラファイル書き込み
void CWinEnemyEditor::write_enemy(int index)
{
	m_file->write_enemy(m_data, index);
}

void CWinEnemyEditor::keyloop()
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

// 属性リスト作成
void CWinEnemyEditor::read_type_list()
{
	m_typenum = 8;

	m_typelist.push_back(Str_e_type(T_FIRE));
	m_typelist.push_back(Str_e_type(T_WATER));
	m_typelist.push_back(Str_e_type(T_WIND));
	m_typelist.push_back(Str_e_type(T_EARTH));
	m_typelist.push_back(Str_e_type(T_LIGHT));
	m_typelist.push_back(Str_e_type(T_DARK));
	m_typelist.push_back(Str_e_type(T_TIME));
	m_typelist.push_back(Str_e_type(T_SPACE));
}

// 攻撃方法リスト作成
void CWinEnemyEditor::read_fight_list()
{
}

bool CWinEnemyEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinEnemyEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinEnemyEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinEnemyEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinEnemyEditor::onkeypress_ok()
{
	CWinEditValue*	nw_editvalue;
	if (m_cur.y == m_enemynum)
	{	// 新規作成
		Enemy tmp_enemy;
		int i;
		for (i = 0; i < MAX_ENEMYNAME; i++)
		{
			tmp_enemy.name[i] = '\0';
		}
		tmp_enemy.type = 1;
		tmp_enemy.hp = 0;
		tmp_enemy.ap = 0;
		tmp_enemy.an = 0;
		tmp_enemy.ag = 0;
		tmp_enemy.mp = 0;
		tmp_enemy.mn = 0;
		tmp_enemy.mg = 0;
		tmp_enemy.hr = 0;
		tmp_enemy.er = 0;
		tmp_enemy.fp = 0;
		tmp_enemy.exp = 0;
		tmp_enemy.gold = 0;
		for (i = 0; i < ENEMY_ITEM; i++)
		{
			tmp_enemy.item[i].id = 0;
			tmp_enemy.item[i].num = 0;
			tmp_enemy.item_r[i] = 0;
		}
		for (i = 0; i < ENEMY_FIGHT; i++)
		{
			tmp_enemy.fight[i] = 0;
			tmp_enemy.fight_r[i] = 0;
		}
		tmp_enemy.flg = 0;
		tmp_enemy.next_enemy = 0;
		for (i = 0; i < ENEMY_CALL; i++)
		{
			tmp_enemy.call_enemy[i] = 0;
		}
		for (i = 0; i < MAX_ENEMYPROF; i++)
		{
			tmp_enemy.prof[i] = 0;
		}
		m_data->m_enemy.push_back(tmp_enemy);
	}
	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;

		// アイテムリスト登録（リスト番号０に登録）
		nw_editvalue->push_list(&m_itemlist);
		// 敵キャラリスト登録（リスト番号１に登録）
		nw_editvalue->push_list(&m_enemylist);
		// 属性リスト登録（リスト番号２に登録）
		nw_editvalue->push_list(&m_typelist);
		// 攻撃方法リスト登録（リスト番号３に登録）
		nw_editvalue->push_list(&m_fightlist);

		// ポインタセット
		nw_editvalue->push("名前",		 m_data->m_enemy[m_cur.y].name,		TT_CHR, MAX_ENEMYNAME);
		nw_editvalue->push("属性",		&m_data->m_enemy[m_cur.y].type,		TT_LST, 2); // リスト番号2を指定
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("体力（最大）",	&m_data->m_enemy[m_cur.y].hp,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃力（最大）",	&m_data->m_enemy[m_cur.y].ap,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃回数（最大）",	&m_data->m_enemy[m_cur.y].an,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("防御力（最大）",	&m_data->m_enemy[m_cur.y].ag,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法力（最大）",	&m_data->m_enemy[m_cur.y].mp,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法回数（最大）",	&m_data->m_enemy[m_cur.y].mn,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法防御力（最大）",&m_data->m_enemy[m_cur.y].mg,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("命中率（％）",	&m_data->m_enemy[m_cur.y].hr,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("回避率（％）",	&m_data->m_enemy[m_cur.y].er,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("素早さ（最大）",	&m_data->m_enemy[m_cur.y].fp,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("経験値",		&m_data->m_enemy[m_cur.y].exp,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持金",		&m_data->m_enemy[m_cur.y].gold,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("所持アイテム　：０",&m_data->m_enemy[m_cur.y].item[0].id,	TT_LST, 0); // リスト番号0を指定
		nw_editvalue->push("所持アイテム数：０",&m_data->m_enemy[m_cur.y].item[0].num,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム率：０",&m_data->m_enemy[m_cur.y].item_r[0],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム　：１",&m_data->m_enemy[m_cur.y].item[1].id,	TT_LST, 0);
		nw_editvalue->push("所持アイテム数：１",&m_data->m_enemy[m_cur.y].item[1].num,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム率：１",&m_data->m_enemy[m_cur.y].item_r[1],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム　：２",&m_data->m_enemy[m_cur.y].item[2].id,	TT_LST, 0);
		nw_editvalue->push("所持アイテム数：２",&m_data->m_enemy[m_cur.y].item[2].num,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム率：２",&m_data->m_enemy[m_cur.y].item_r[2],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム　：３",&m_data->m_enemy[m_cur.y].item[3].id,	TT_LST, 0);
		nw_editvalue->push("所持アイテム数：３",&m_data->m_enemy[m_cur.y].item[3].num,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム率：３",&m_data->m_enemy[m_cur.y].item_r[3],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム　：４",&m_data->m_enemy[m_cur.y].item[4].id,	TT_LST, 0);
		nw_editvalue->push("所持アイテム数：４",&m_data->m_enemy[m_cur.y].item[4].num,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("所持アイテム率：４",&m_data->m_enemy[m_cur.y].item_r[4],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("攻撃ID：０",	&m_data->m_enemy[m_cur.y].fight[0],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：０",	&m_data->m_enemy[m_cur.y].fight_r[0],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：１",	&m_data->m_enemy[m_cur.y].fight[1],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：１",	&m_data->m_enemy[m_cur.y].fight_r[1],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：２",	&m_data->m_enemy[m_cur.y].fight[2],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：２",	&m_data->m_enemy[m_cur.y].fight_r[2],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：３",	&m_data->m_enemy[m_cur.y].fight[3],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：３",	&m_data->m_enemy[m_cur.y].fight_r[3],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：４",	&m_data->m_enemy[m_cur.y].fight[4],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：４",	&m_data->m_enemy[m_cur.y].fight_r[4],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：５",	&m_data->m_enemy[m_cur.y].fight[5],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：５",	&m_data->m_enemy[m_cur.y].fight_r[5],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：６",	&m_data->m_enemy[m_cur.y].fight[6],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：６",	&m_data->m_enemy[m_cur.y].fight_r[6],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：７",	&m_data->m_enemy[m_cur.y].fight[7],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：７",	&m_data->m_enemy[m_cur.y].fight_r[7],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：８",	&m_data->m_enemy[m_cur.y].fight[8],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：８",	&m_data->m_enemy[m_cur.y].fight_r[8],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃ID：９",	&m_data->m_enemy[m_cur.y].fight[9],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃率：９",	&m_data->m_enemy[m_cur.y].fight_r[9],	TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("死後フラグ",	&m_data->m_enemy[m_cur.y].flg,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("死後次の敵ID",	&m_data->m_enemy[m_cur.y].next_enemy,	TT_INT, MAX_INTNUM);
		nw_editvalue->push("呼ぶ敵ID：０",	&m_data->m_enemy[m_cur.y].call_enemy[0],TT_LST, 1); // リスト番号0を指定
		nw_editvalue->push("呼ぶ敵ID：１",	&m_data->m_enemy[m_cur.y].call_enemy[1],TT_LST, 1);
		nw_editvalue->push("呼ぶ敵ID：２",	&m_data->m_enemy[m_cur.y].call_enemy[2],TT_LST, 1);
		nw_editvalue->push("呼ぶ敵ID：３",	&m_data->m_enemy[m_cur.y].call_enemy[3],TT_LST, 1);
		nw_editvalue->push("呼ぶ敵ID：４",	&m_data->m_enemy[m_cur.y].call_enemy[4],TT_LST, 1);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("プロフィール",	 m_data->m_enemy[m_cur.y].prof,		TT_CHR, MAX_ENEMYPROF);

		nw_editvalue->startwin(true);
		delete(nw_editvalue);
		
		// 敵キャラ書き出し
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
			if (m_cur.y == m_enemynum)
			{	// 新規追加だったら元に戻す
				m_data->m_enemy.pop_back();
			}
			else
			{	// 敵キャラ名再度読み込み（リストを元に戻す）
				read_enemy(m_cur.y);
			}
		}
		else if (tmp_ret == 1)
		{
			write_enemy(m_cur.y);
			change(std::string(m_data->m_enemy[m_cur.y].name), m_cur.y, m_cur.y);
			if (m_cur.y == m_enemynum)
			{ // 新規追加だった
				m_enemynum++;
				push("新規作成", m_enemynum);
			}
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinEnemyEditor::onkeypress_cancel()
{
	return false;	// 終了
}




