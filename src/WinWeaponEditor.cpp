#include "win.h"

CWinWeaponEditor::CWinWeaponEditor(CData* data, CConfig* config, CFile* file)
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
	m_weaponnum = 0;         // 読み込んだアイテムの数

	m_data	 = data;	// データ格納
	m_config = config;	// コンフィグ格納
	m_file	 = file;	// ファイルハンドラ格納

	// ここでシナリオを読み込め（不要）

	// アイテム読み込み
	read_weapon_list();

	for (int i = 0; i < m_weaponnum; i++)
	{
		push(m_data->m_weapon[i].name, i);
	}
	push("新規作成", m_weaponnum);
}

CWinWeaponEditor::~CWinWeaponEditor()
{
}

int CWinWeaponEditor::drawwin()
{
	setlist(m_wpos.x, m_wpos.y, &m_dpos.x, &m_cur.y, &m_dpos.y, m_list, m_cp);
	return true;
}

void CWinWeaponEditor::push(const std::string str, const int id)
{
	push(str, id, m_cpair);
}
void CWinWeaponEditor::push(const std::string str, const int id, const int cpair)
{
	m_list.push_back(str);
	m_cp.push_back(cpair);
	m_index.push_back(id);

	if (m_maxwidth < CMyStr::length(str))
		m_maxwidth = CMyStr::length(str);
}
void CWinWeaponEditor::change(const std::string str, const int id, const int index)
{
	m_list[index] = str;
	m_index[index] = id;

	if (m_maxwidth < CMyStr::length(m_list[index]))
		m_maxwidth = CMyStr::length(m_list[index]);
}


// アイテム全て読み込み
void CWinWeaponEditor::read_weapon_list()
{
	m_weaponnum = m_file->read_weapon(m_data);
}

// アイテムファイル読み込み
void CWinWeaponEditor::read_weapon(int index)
{
	m_file->read_weapon(m_data, index);
}

// アイテムファイル書き込み
void CWinWeaponEditor::write_weapon(int index)
{
	m_file->write_weapon(m_data, index);
}

void CWinWeaponEditor::keyloop()
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

bool CWinWeaponEditor::onkeypress_left()
{
	if (m_dpos.x > 0)	m_dpos.x--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinWeaponEditor::onkeypress_down()
{
	if (m_cur.y < m_index.size() - 1)	m_cur.y++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinWeaponEditor::onkeypress_up()
{
	if (m_cur.y > 0)	m_cur.y--;
	drawwin();
	return true;	// キーループ継続
}
bool CWinWeaponEditor::onkeypress_right()
{
	// 個々のラインの右端までスクロール
	//if (m_list[m_cur.y].length() / 2 - m_dpos.x > m_winw - 2)	m_dpos.x++;
	// 最大長ラインの右端までスクロール
	if (m_winw - m_wpos.x - 1 + m_dpos.x < m_maxwidth)	m_dpos.x++;
	drawwin();
	return true;	// キーループ継続
}
bool CWinWeaponEditor::onkeypress_ok()
{
	CWinEditValue*	nw_editvalue;
	if (m_cur.y == m_weaponnum)
	{	// 新規作成
		Weapon tmp_weapon;
		int i;
		for (i = 0; i < MAX_WEAPONNAME; i++)
		{
			tmp_weapon.name[i] = '\0';
		}
		tmp_weapon.type = T_FIRE;
		tmp_weapon.kind = W_SWORD;
		tmp_weapon.rare = R_NORMAL;
		tmp_weapon.ap   = 0;
		tmp_weapon.an   = 0;
		tmp_weapon.ag   = 0;
		tmp_weapon.mp   = 0;
		tmp_weapon.mn   = 0;
		tmp_weapon.mg   = 0;
		tmp_weapon.hr   = 100;
		tmp_weapon.er   = 0;
		tmp_weapon.fp   = 0;
		tmp_weapon.option  = 0;
		tmp_weapon.price   = 0;
		for (i = 0; i < MAX_WEAPONPROF; i++)
		{
			tmp_weapon.prof[i] = '\0';
		}
		m_data->m_weapon.push_back(tmp_weapon);
	}
	for ( ; ; )
	{
		nw_editvalue = new CWinEditValue;
		// ポインタセット
		nw_editvalue->push("名前",	 m_data->m_weapon[m_cur.y].name,		TT_CHR, MAX_WEAPONNAME);
		nw_editvalue->push("属性",	&m_data->m_weapon[m_cur.y].type,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("種類",	&m_data->m_weapon[m_cur.y].kind,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("レアリティ",&m_data->m_weapon[m_cur.y].rare,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("攻撃力",	&m_data->m_weapon[m_cur.y].ap,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("攻撃回数",	&m_data->m_weapon[m_cur.y].an,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("防御力",	&m_data->m_weapon[m_cur.y].ag,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法力",	&m_data->m_weapon[m_cur.y].mp,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法回数",	&m_data->m_weapon[m_cur.y].mn,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("魔法防御力",&m_data->m_weapon[m_cur.y].mg,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("命中率",	&m_data->m_weapon[m_cur.y].hr,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("回避率",	&m_data->m_weapon[m_cur.y].er,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("素早さ",	&m_data->m_weapon[m_cur.y].fp,			TT_INT, MAX_INTNUM);
		nw_editvalue->push("--------------",	NULL,	TT_SPC, 1);
		nw_editvalue->push("追加効果",	&m_data->m_weapon[m_cur.y].option,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("価格",	&m_data->m_weapon[m_cur.y].price,		TT_INT, MAX_INTNUM);
		nw_editvalue->push("説明文",	 m_data->m_weapon[m_cur.y].prof,		TT_CHR, MAX_ITEMPROF);

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
			if (m_cur.y == m_weaponnum)
			{	// 新規追加だったら元に戻す
				m_data->m_weapon.pop_back();
			}
			else
			{	// 武器名再度読み込み（リストを元に戻す）
				read_weapon(m_cur.y);
			}
		}
		else if (tmp_ret == 1)
		{
			write_weapon(m_cur.y);
			change(std::string(m_data->m_weapon[m_cur.y].name), m_cur.y, m_cur.y);
			if (m_cur.y == m_weaponnum)
			{ // 新規追加だった
				m_weaponnum++;
				push("新規作成", m_weaponnum);
			}
		}
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
		return true;	// キーループ継続
	}
}
bool CWinWeaponEditor::onkeypress_cancel()
{
	return false;	// 終了
}



