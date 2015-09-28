#include "win.h"

CWinEditValue::CWinEditValue()
{
	// 以下はデフォルト値です。
	// オブジェクト作成後に調整してください。
	m_dpos.x = 0;
	m_dpos.y = 0;
	m_cur.y  = 0;
	m_wpos.x = 1;
	m_wpos.y = 1;
	m_winx   = 0;
	m_winy   = 0;
	m_winw   = 5;
	m_winh   = 10;
	m_disable_cansel = false;
	setsize(0, 0);		// Windowサイズ（デフォルト）
	movewin(5, 1);		// Window位置（デフォルト）（中央、マージン１）
}

CWinEditValue::~CWinEditValue()
{
}

int CWinEditValue::drawwin()
{
	setedit(m_wpos.x, m_wpos.y, &m_cur.y, &m_dpos.y, m_name, m_value, m_cp, m_size);
	return true;
}

void CWinEditValue::push(const std::string str, void * ptr, const int chr, const int num)
{
	push(str, ptr, chr, num, m_cpair);
}
void CWinEditValue::push(const std::string str, void * ptr, const int chr, const int num, const int cpair)
{
	m_name.push_back(str);				// 項目の名称
	m_ptr.push_back(ptr);				// 値を格納するポインタ
	m_my_tt.push_back(chr);				// 値の種類（TT_）
	m_size.push_back(num);				// 値の桁数
	m_value.push_back(encode(ptr, chr, num));	// 値の表記
	m_cp.push_back(cpair);				// 値の色ペア
}

std::string CWinEditValue::encode(void * ptr, const int chr, const int num)
{
	std::string	tmp_buf;

	switch(chr)
	{
		case TT_STR:	// String
			tmp_buf = *(std::string*)ptr;
			break;
		case TT_CHR:	// CharString
			tmp_buf = std::string((char*)ptr);
			break;
		case TT_SPC:	// スペーサー
		case TT_VCT:	// ベクタ追加
			tmp_buf = "";
			break;
		case TT_INT:	// Int型
			tmp_buf = mystd::to_string(*(int*)ptr);
			break;
		case TT_LST:	// List型
			tmp_buf = (*m_selectlist[num])[*(int*)ptr];
			break;
		default:
			break;
	}
	return (tmp_buf);
}

void CWinEditValue::decode(std::string* str, void *ptr, const int chr)
{
	switch(chr)
	{
		case TT_STR:
			*(std::string*)ptr = *str;
			break;
		case TT_CHR:
			memcpy(ptr, str->c_str(), str->length()+1); // 終端文字を足す
			break;
		case TT_INT:
			*(int*)ptr = atoi(str->c_str());
		case TT_LST:
			*(int*)ptr = atoi(str->c_str());
		default:
			break;
	}
}

// 選択式フィールド用のリスト作成
void CWinEditValue::push_list(std::vector<std::string> * ptr)
{
	m_selectlist.push_back(ptr);
}

bool CWinEditValue::onkeypress_down()
{
	if (m_cur.y < m_name.size() - 1)	m_cur.y++;	// カーソル下げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y++;	// スペーサならもういっちょ下げる

	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_up()
{
	if (m_cur.y > 0)			m_cur.y--;	// カーソル上げる
	if (m_my_tt[m_cur.y] == TT_SPC)		m_cur.y--;	// スペーサならもういっちょ上げる

	drawwin();
	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_right()
{
	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_left()
{
	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_ok()
{
	if (m_my_tt[m_cur.y] == TT_VCT)
	{
		*(int*)m_ptr[m_cur.y] = 1;
		return false;	// Vectorを追加するために一旦終了
	}
	else if (m_my_tt[m_cur.y] == TT_LST)
	{
		CWinSelect1Line*	nw_select1line;

		nw_select1line = new CWinSelect1Line;
		nw_select1line->settitle(m_name[m_cur.y]);
		// セレクトリストを作成する
		for (int i = 0; i < (*m_selectlist[m_size[m_cur.y]]).size(); i++)
		{
			nw_select1line->push((*m_selectlist[m_size[m_cur.y]])[i], i);
		}
		nw_select1line->setsize(30, 14);
		nw_select1line->movewin(5, 1);
		int tmpnum = nw_select1line->startwin(true);
		if (tmpnum >= 0)
		{
			*(int*)m_ptr[m_cur.y] = tmpnum;
			m_value[m_cur.y] = (*m_selectlist[m_size[m_cur.y]])[tmpnum];
		}
		delete(nw_select1line);
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
	}
	else if (m_my_tt[m_cur.y] != TT_SPC)
	{
		CWinGetPath*	nw_getpath;

		nw_getpath = new CWinGetPath;
		nw_getpath->settitle(m_name[m_cur.y]);
		// 入力フィールドの大きさを計算する（とりあえず1文字3byteで計算）
		int tmp_w = 0, tmp_h = 0;
		if (m_size[m_cur.y] / 3 > 40)
		{
			tmp_w = 40 + 2;
			tmp_h = m_size[m_cur.y] / (40*3) + 3; // 端数と罫線分
		}
		else
		{
			tmp_w = m_size[m_cur.y] / 3 + 2;
			tmp_h = 3;
		}
		nw_getpath->setsize(tmp_w, tmp_h);
		nw_getpath->movewin(5, 1);
		nw_getpath->setcharbytes(m_size[m_cur.y]);
		m_value[m_cur.y] = nw_getpath->startdialog(true);
		decode(&m_value[m_cur.y], m_ptr[m_cur.y], m_my_tt[m_cur.y]);
		delete(nw_getpath);
		drawwin();
		touchwin(m_this);
		wrefresh(m_this);
	}

	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_cancel()
{
	return m_disable_cansel;
}

