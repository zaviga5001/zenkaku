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

	bool	m_title;		// �����ȥ����ɽ��̵ͭ
	int	m_scenario;		// �ץ쥤���륷�ʥꥪ

protected:

private:

};
#endif // CCONFIG_H
