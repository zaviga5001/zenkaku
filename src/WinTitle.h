#ifndef CWINTITLE_H
#define CWINTITLE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include "Windows.h"

class CWinTitle : public CWindows
{
public:
	CWinTitle();
	virtual ~CWinTitle();

	virtual int	drawwin();

	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

protected:

private:
};

#endif // CWINTITLE_H
