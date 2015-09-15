#ifndef CTITLE_H
#define CTITLE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <ncurses.h>
#include "common.h"
#include "win.h"
#include "Config.h"
#include "Data.h"

class CTitle
{
public:
	CTitle();
	virtual ~CTitle();
	
	bool	disp_title(CConfig* config);
	bool	select_game(CData* data, CConfig* config, CFile* file);

	std::vector<ScnList>	m_scnlist;	// シナリオリスト

protected:

private:

};
#endif // CTITLE_H
