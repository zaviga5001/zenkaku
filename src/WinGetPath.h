#ifndef CWINGETPATH_H
#define CWINGETPATH_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include "Windows.h"

class CWinGetPath : public CWindows
{
public:
	CWinGetPath();
	virtual ~CWinGetPath();

	virtual int	drawwin();
	void	setcharbytes(int num);
	void	keyloop();

	int	m_charbytes;

protected:

private:
};

#endif // CWINGETPATH_H
