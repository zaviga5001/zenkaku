#ifndef CWINSHOWMESSAGE_H
#define CWINSHOWMESSAGE_H
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

#define		TYPE_AUTO	0
#define		TYPE_SCROLL	1

class CWinShowMessage : public CWindows
{
public:
	CWinShowMessage();
	virtual ~CWinShowMessage();

	virtual int	drawwin();
	int		drawmsg();
	int		drawitem();
	void		push(const CString str, const int id);
	void		push(const CString str, const int id, const int cpair);

	Pos	m_wpos;			// ウィンドウ上の表示位置

	bool	onkeypress_left();	// 左キー押下
	bool	onkeypress_down();	// 下キー押下
	bool	onkeypress_up();	// 上キー押下
	bool	onkeypress_right();	// 右キー押下
	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

	int	m_disable_cansel;	// キャンセルボタンが効くかどうか
	int	m_type;			// 表示タイプ
					// 0:自動表示タイプ
					// 1:スクロールタイプ

	CString	m_msg;			// メッセージ
	int	m_split;		// スプリッタの位置

protected:
	std::vector<CString>	m_list;		// 要素
	std::vector<CString>	m_pause;	// メッセージ一時停止用
	std::vector<int>	m_cp;		// 色
	std::vector<int>	m_index;	// 値
	std::vector<CString>	m_msgvct;	// メッセージ
	int	m_maxwidth;		// リスト文字列の最大幅
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）
	Pos	m_drawarea;		// 描画エリアの広さ

private:
};

#endif // CWINSHOWMESSAGE_H
