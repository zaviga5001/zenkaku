#ifndef CWINSCENARIOEDITOR_H
#define CWINSCENARIOEDITOR_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <string>
#include <ncurses.h>
#include "Windows.h"
#include "Config.h"
#include "Data.h"
#include "File.h"



class CWinScenarioEditor : public CWindows
{
public:
	CWinScenarioEditor(CData* data, CConfig* config, CFile* file);
	virtual ~CWinScenarioEditor();

	virtual int	drawwin();

	void		keyloop();		// キー入力ループ
	bool		onkeypress_left();	// 左キー押下
	bool		onkeypress_down();	// 下キー押下
	bool		onkeypress_up();	// 上キー押下
	bool		onkeypress_right();	// 右キー押下

	int		read_mychar();		// マイキャラ読み込み

	std::string	m_path;			// データ格納パス
	int		m_mcnum;		// マイキャラデータの数

	CConfig*	m_config;		// コンフィグ
	CData*		m_data;			// データ
	CFile*		m_file;			// ファイルハンドラ

protected:
	void		warn(enum msg_id tmp_msg);	// 警告ウィンドゥ表示

private:
};

#endif // CWINSCENARIOEDITOR_H
