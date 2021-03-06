#ifndef CWINSELECT1LINE_H
#define CWINSELECT1LINE_H
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

class CWinSelect1Line : public CWindows
{
public:
	CWinSelect1Line();
	virtual ~CWinSelect1Line();

	virtual int	drawwin();
	void		push(const std::string str, const int id);
	void		push(const std::string str, const int id, const int cpair);

	Pos	m_wpos;			// ウィンドウ上の表示位置

	bool	onkeypress_left();	// 左キー押下
	bool	onkeypress_down();	// 下キー押下
	bool	onkeypress_up();	// 上キー押下
	bool	onkeypress_right();	// 右キー押下
	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

	int	m_disable_cansel;	// キャンセルボタンが効くかどうか

protected:
	std::vector<std::string>	m_list;		// 要素
	std::vector<int>	m_cp;		// 色
	std::vector<int>	m_index;	// 値
	int	m_maxwidth;		// リスト文字列の最大幅
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）

private:
};

#endif // CWINSELECT1LINE_H
