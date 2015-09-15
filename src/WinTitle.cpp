#include "win.h"

CWinTitle::CWinTitle()
{
	m_winx = 0;
	m_winy = 0;
	m_winw = 40;
	m_winh = 24;
}

CWinTitle::~CWinTitle()
{
}

int CWinTitle::drawwin()
{
	setmessage(1, 1, "タイトル画面", 1, 2);
	setmessage(2, 2, "タイトル画面", 3, 4);
	setmessage(3, 3, "タイトル画面", 5, 6);

	return true;
}

bool CWinTitle::onkeypress_ok()		{ return false; }	// キーループ終了
bool CWinTitle::onkeypress_cancel()	{ return false; }	// キーループ終了

