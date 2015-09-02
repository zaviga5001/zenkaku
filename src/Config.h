#ifndef CCONFIG_H
#define CCONFIG_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>


class CConfig
{
public:
	CConfig();
	virtual ~CConfig();

	int	m_mode = 0;		// 動作モード（0:Game 1:Editor）

	bool	m_title;		// タイトル画面表示有無
	int	m_scenario;		// プレイするシナリオ

protected:

private:

};
#endif // CCONFIG_H
