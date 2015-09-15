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
#include "Data.h"

class CGame
{
public:
	CGame();
	CGame(CData* data, CConfig* config, CFile* file);
	virtual ~CGame();

	bool	main();			// ゲームループ

	CConfig* m_config;		// コンフィグ
	CData*	m_data;			// データ
	CFile*	m_file;			// ファイルハンドラ

protected:

private:

};
#endif // CGAME_H
