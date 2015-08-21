#ifndef CWINPGEDITOR_H
#define CWINPGEDITOR_H
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



class CWinPGEditor : public CWindows
{
public:
	CWinPGEditor(CConfig* config);
	virtual ~CWinPGEditor();

	virtual int	drawwin();
	void		push(const std::string str, const int id);
	void		push(const std::string str, const int id, const int cpair);
	void		change(const std::string str, const int id, const int index);
	bool		read_pg(int index);	// パーティ群読み込み
	void		write_pg(int index);	// パーティ群書き込み

	Pos		m_wpos;			// ウィンドウ上の表示位置

	void		keyloop();		// キー入力ループ
	bool		onkeypress_left();	// 左キー押下
	bool		onkeypress_down();	// 下キー押下
	bool		onkeypress_up();	// 上キー押下
	bool		onkeypress_right();	// 右キー押下
	virtual bool	onkeypress_ok();	// ＯＫキー押下
	virtual bool	onkeypress_cancel();	// キャンセルキー押下

	CData*		m_data;			// ゲーム内のあらゆる情報

protected:
	void	warn(enum msg_id tmp_msg);	// 警告ウィンドゥ表示

	std::vector<std::string>	m_list;		// 要素
	std::vector<int>	m_cp;		// 色
	std::vector<int>	m_index;	// 値
	int	m_maxwidth;		// リスト文字列の最大幅
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）

private:
};

#endif // CWINPGEDITOR_H
