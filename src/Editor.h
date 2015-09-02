#ifndef CEDITOR_H
#define CEDITOR_H
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

class CEditor
{
public:
	CEditor();
	CEditor(CConfig* config);
	virtual ~CEditor();

	bool	main();			// メインループ

	CConfig* m_config;		// コンフィグ

protected:

private:

};
#endif // CEDITOR_H
