#ifndef CCONFIG_H
#define CCONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "include/curses.h"


class CConfig
{
public:
	CConfig();
	virtual ~CConfig();

	bool	m_title;		// タイトル画面表示有無
	int	m_scenario;		// プレイするシナリオ

protected:

private:

};
#endif // CCONFIG_H
