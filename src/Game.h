#ifndef CGAME_H
#define CGAME_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include "common.h"
#include "win.h"
#include "Config.h"

class CGame
{
public:
	CGame();
	CGame(CConfig* config);
	virtual ~CGame();

	bool	main();			// ゲームループ

	CConfig* m_config;		// コンフィグ

protected:

private:

};
#endif // CGAME_H
