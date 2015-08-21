#include "win.h"

CWinMsg::CWinMsg()
{
	m_winx = 1;
	m_winy = 1;
	m_winw = 30;
	m_winh = 3;
	m_dpos = 0;
	movewin(5, 1);
}

CWinMsg::~CWinMsg()
{
}

int CWinMsg::drawwin()
{
	std::string	strbuf;

	strbuf = m_msg;
	for ( ; ; )
	{
		clearwin();

		strbuf = strbuf.substr(m_dpos, strbuf.length());
		m_dpos = setmessage_n(1, 1, strbuf);
		if (m_dpos >= strbuf.length())	break;
	}

	return true;
}

bool CWinMsg::onkeypress_ok()		{ return false; }	// キーループ終了
bool CWinMsg::onkeypress_cancel()	{ return false; }	// キーループ終了

