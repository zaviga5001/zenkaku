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
#include "Data.h"

class CEditor
{
public:
	CEditor();
	CEditor(CData* data, CConfig* config, CFile* file);
	virtual ~CEditor();

	bool	main();			// メインループ

	CConfig* m_config;		// コンフィグ
	CData*	m_data;			// データ
	CFile*	m_file;			// ファイルハンドラ

protected:

private:

};
#endif // CEDITOR_H
