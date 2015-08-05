#ifndef CWINGETPATH_H
#define CWINGETPATH_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "include/curses.h"
#include "Windows.h"

class CWinGetPath : public CWindows
{
public:
	CWinGetPath();
	virtual ~CWinGetPath();

	virtual int	drawwin();
	void	keyloop();

protected:

private:
};

#endif // CWINGETPATH_H
