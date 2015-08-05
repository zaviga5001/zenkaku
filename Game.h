#ifndef CGAME_H
#define CGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "include/curses.h"
#include "common.h"
#include "Config.h"

class CGame
{
public:
	CGame();
	CGame(CConfig* config);
	virtual ~CGame();

	bool	main();			// ゲームループ

protected:

private:

};
#endif // CGAME_H
