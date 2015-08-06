#ifndef CWINMYCHAREDITOR_H
#define CWINMYCHAREDITOR_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <ncurses.h>
#include "Windows.h"
#include "CString.h"
#include "Config.h"
#include "Data.h"
#include "File.h"



class CWinMycharEditor : public CWindows
{
public:
	CWinMycharEditor(CConfig* config);
	virtual ~CWinMycharEditor();

	virtual int	drawwin();
	void		push(const CString str, void * ptr, const int chr, const int num);
	void		push(const CString str, void * ptr, const int chr, const int num, const int cpair);
	void		read_mychar();		// マイキャラ読み込み
	void		write_mychar();		// マイキャラ書き込み


	void		keyloop();		// キー入力ループ
	virtual bool	onkeypress_down();	// 下キー押下
	virtual bool	onkeypress_up();	// 上キー押下
	virtual bool	onkeypress_right();	// 右キー押下
	virtual bool	onkeypress_left();	// 左キー押下
	virtual bool	onkeypress_ok();	// ＯＫキー押下
	virtual bool	onkeypress_cancel();	// キャンセルキー押下

	CData*	m_data;				// ゲーム内のあらゆる情報
	Pos	m_wpos;				// ウィンドウ上の表示位置

protected:
	CString	encode(void* ptr, const int chr, const int num);
	void	decode(CString* str, void* ptr, const int chr);
	void		warn(enum msg_id tmp_msg);	// 警告ウィンドゥ表示

	std::vector<CString>	m_name;	// 要素名
	std::vector<CString>	m_value;// 値（文字列変換）
	std::vector<void*>	m_ptr;	// ポインタ
	std::vector<int>	m_my_tt;// 変数の型
	std::vector<int>	m_size;	// 配列の個数
	std::vector<int>	m_cp;	// 色
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）

private:
};

#endif // CWINMYCHAREDITOR_H
