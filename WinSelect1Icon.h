#ifndef CWINSELECT1ICON_H
#define CWINSELECT1ICON_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include "include/curses.h"
#include "Windows.h"
#include "CString.h"

class CWinSelect1Icon : public CWindows
{
public:
	CWinSelect1Icon();
	virtual ~CWinSelect1Icon();

	virtual int	drawwin();
	void		push(const CString str, const int id);
	void		push(const CString str, const int cpair, const int id);

	Pos	m_wpos;			// ウィンドウ上の表示位置
	int	m_cols;			// アイコン表示の縦横カラム数

	bool	onkeypress_left();	// 左キー押下
	bool	onkeypress_down();	// 下キー押下
	bool	onkeypress_up();	// 上キー押下
	bool	onkeypress_right();	// 右キー押下
	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

	int	m_disable_cansel;	// キャンセルボタンが効くかどうか

protected:
	std::vector<CString>	m_list;		// 要素
	std::vector<int>	m_cp;		// 色
	std::vector<int>	m_index;	// 値
	int	m_maxwidth;		// リスト文字列の最大幅
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）

private:
};

#endif // CWINSELECT1ICON_H
