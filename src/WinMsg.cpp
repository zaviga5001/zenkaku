#include "win.h"

// 改行対応のメッセージBOX
CWinMsg::CWinMsg()
{
	m_winx = 1;
	m_winy = 1;
	m_winw = 30;
	m_winh = 3;
	m_dpos = 0;
	movewin(5, 1);	// pos(5 = center), from
}

CWinMsg::~CWinMsg()
{
}

int CWinMsg::drawwin()
{
	std::string	strbuf;
	int	endnum = CMyStr::length(m_msg);

	strbuf = m_msg;
	for ( ; ; )
	{
		clearwin();

		strbuf = CMyStr::substr(m_msg, m_dpos);
		m_dpos = setmessage_n(1, 1, strbuf);
		if (m_dpos >= endnum)	break;
	}

	return true;
}

bool CWinMsg::onkeypress_ok()		{ return false; }	// キーループ終了
bool CWinMsg::onkeypress_cancel()	{ return false; }	// キーループ終了

