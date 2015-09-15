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
	setedit(m_wpos.x, m_wpos.y, &m_cur.y, &m_dpos.y, m_name, m_value, m_cp);
	return true;
}

void CWinEditValue::push(const std::string str, void * ptr, const int chr, const int num)
{
	push(str, ptr, chr, num, m_cpair);
}
void CWinEditValue::push(const std::string str, void * ptr, const int chr, const int num, const int cpair)
{
	m_name.push_back(str);
	m_ptr.push_back(ptr);
	m_my_tt.push_back(chr);
	m_size.push_back(num);
	m_value.push_back(encode(ptr, chr, num));
	m_cp.push_back(cpair);
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
			memcpy(ptr, str->c_str(), str->length()+1); // lengthは間違ってるけど影響ないからこのまま
			break;
		case TT_INT:
			*(int*)ptr = atoi(str->c_str());
		default:
			break;
	}
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
	if (m_my_tt[m_cur.y] != TT_SPC && m_my_tt[m_cur.y] != TT_VCT)
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
	else if (m_my_tt[m_cur.y] == TT_VCT)
	{
		*(int*)m_ptr[m_cur.y] = 1;
		return false;	// Vectorを追加するために一旦終了
	}

	return true;	// キーループ継続
}
bool CWinEditValue::onkeypress_cancel()
{
	return m_disable_cansel;
}

