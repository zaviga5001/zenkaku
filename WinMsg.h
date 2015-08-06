#ifndef CWINMSG_H
#define CWINMSG_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include "Windows.h"

class CWinMsg : public CWindows
{
public:
	CWinMsg();
	virtual ~CWinMsg();

	virtual int	drawwin();

	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

	CString	m_msg;			// ���b�Z�[�W�{��

protected:
	int	m_dpos;			// �\���J�n�����̈ʒu

private:
};

#endif // CWINMSG_H
