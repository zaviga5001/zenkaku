#include "win.h"

CWinTitle::CWinTitle()
{
	m_winx = 1;
	m_winy = 1;
	m_winw = 20;
	m_winh = 10;
}

CWinTitle::~CWinTitle()
{
}

int CWinTitle::drawwin()
{
	setmessage(1, 1, "�����ȥ����", 1, 2);
	setmessage(2, 2, "�����ȥ����", 3, 4);
	setmessage(3, 3, "�����ȥ����", 5, 6);

	return true;
}

bool CWinTitle::onkeypress_ok()		{ return false; }	// �����롼�׽�λ
bool CWinTitle::onkeypress_cancel()	{ return false; }	// �����롼�׽�λ

