#include "win.h"

CWinGetPath::CWinGetPath()
{
	m_winx = 1;
	m_winy = 1;
	m_winw = 30;
	m_winh = 3;
	movewin(5, 1);		// Window位置（デフォルト）（中央、マージン１）
}

CWinGetPath::~CWinGetPath()
{
}

int CWinGetPath::drawwin()
{
	wrefresh(m_this);
	return true;
}

void CWinGetPath::keyloop()
{
	char strbuf[1024];

	nocbreak();
	curs_set(1);
	echo();

	mvwgetnstr(m_this, 1, adjx(1), strbuf, 1024);
	wrefresh(m_this);
	m_returnstr = strbuf;

	cbreak();
	curs_set(0);
	noecho();
}


