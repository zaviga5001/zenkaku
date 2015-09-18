#ifndef CWINDOWS_H
#define CWINDOWS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <ncurses.h>
#include <string>
#include "common.h"
#include "msg.h"
#include "Data.h"

#define	MYKEY_LEFT	68
#define	MYKEY_DOWN	66
#define	MYKEY_UP	65
#define	MYKEY_RIGHT	67
#define	MYKEY_OK	'x'
#define	MYKEY_CANCEL	'z'

#define	COLOR_NUM	8
#define	ATTR_NUM	11
#define	SYSTEM_COLOR_NUM	63

//	色
//		COLOR_BLACK
//		COLOR_RED
//		COLOR_GREEN
//		COLOR_YELLOW
//		COLOR_BLUE
//		COLOR_MAGENTA
//		COLOR_CYAN
//		COLOR_WHITE

//	属性
//		A_NORMAL
//		A_STANDOUT
//		A_UNDERLINE
//		A_REVERSE
//		A_BLINK
//		A_DIM
//		A_BOLD
//		A_PROTECT
//		A_INVIS
//		A_ALTCHARSET
//		A_CHARTEXT

enum	my_tt {
	TT_SPC,
	TT_CHR,
	TT_STR,
//	TT_BYT,
//	TT_CST,
	TT_INT,
//	TT_UINT,
//	TT_SHT,
//	TT_LNG,
	TT_VCT
};

class CWindows
{
public:
	CWindows();
	virtual ~CWindows();

	int	startwin(bool frame);			// 表示開始（フレーム付）
	std::string	startdialog(bool frame);		// 表示開始（文字列確定型）

	void	settitle(const std::string title);		// ウィンドゥタイトルを表示する
	void	setsize(int w, int h);			// 画面サイズを決める
	void	movewin(int x, int y);			// 表示位置を移動する
	int	getcpair(int ch, int bg);		// カラーペア番号を取得する
	int	getchcolor(int cpair);			// カラーペア番号を分解する
	int	getbgcolor(int cpair);			// カラーペア番号を分解する
	void	setdefcpair(int cpair);			// デフォルトカラーをセットする
	void	setdefcpair(int ch, int bg);

	void	drawframe();				// フレームを表示する
	virtual int	drawwin() = 0;			// 中身を表示する仮想関数（派生先で使う）

	void	splitwin(int y);			// ウィンドゥを上下に分割する
	void	setmessage(int x, int y, std::string str);	// メッセージを表示する
	void	setmessage(int x, int y, std::string str, int cpair);
	void	setmessage(int x, int y, std::string str, int ch, int bg);
	int	setmessage_n(int x, int y, std::string str);// メッセージを表示する（自動改行）
	int	setmessage_n(int x, int y, std::string str, int cpair);
	int	setmessage_n(int x, int y, std::string str, int ch, int bg);
	void	seticon(Pos pos, Pos* cur, Pos* dpos, std::vector<std::string> list, std::vector<int> cpair, int col);
							// マトリクスを表示する
	void	setselect(int x, int y, int* posx, int* dposx, std::vector<std::string> list, std::vector<int> cpair);
							// セレクトタブを表示する
	void	setlist(int x, int y, int* dposx, int* posy, int* dposy, std::vector<std::string> list, std::vector<int> cpair);
							// リストを表示する
	void	setedit(int x, int y, int* posy, int* dposy, std::vector<std::string> name, std::vector<std::string> value, std::vector<int> cpair, std::vector<int> max_num);
							// リストを表示する
	void	wclrtorborder();			// 1行クリア
	void	clearwin();				// ウィンドゥ内部を全クリア（罫線は残す）
	bool	mvwaddstrtoeol(int x, int y, const std::string str);
							// 行末まで表示

	void	chg_attr(int x, int y, long attr);				// 属性だけ変更
	void	chg_color(int x, int y, int cpair);				// 色だけ変更
	void	chg_color(int x, int y, int ch, int bg);			// 色だけ変更
	void	chg_attr_color(int x, int y, long attr, int cpair);		// 色と属性を変更
	void	chg_attr_color(int x, int y, long attr, int ch, int bg);	// 色と属性を変更

	virtual void	keyloop();			// キー入力ループ
	virtual bool	onkeypress_left();		// 左キー押下（仮想関数）
	virtual bool	onkeypress_down();		// 下キー押下（仮想関数）
	virtual bool	onkeypress_up();		// 上キー押下（仮想関数）
	virtual bool	onkeypress_right();		// 右キー押下（仮想関数）
	virtual bool	onkeypress_ok();		// ＯＫキー押下（仮想関数）
	virtual bool	onkeypress_cancel();		// キャンセルキー押下（仮想関数）


	int	m_winx;			// 表示位置左
	int	m_winy;			// 表示位置上
	int	m_winw;			// 幅
	int	m_winh;			// 高さ

	int	m_return;		// startwinの返り値
	std::string	m_returnstr;		// startdialogの返り値

	int	m_colors[COLOR_NUM];	// カラーテーブル
	int	m_cpair;		// デフォルトカラーペア
	long	m_attrs[ATTR_NUM];	// 属性テーブル

	WINDOW*	m_this;			// 自分自身のウィンドゥハンドラ


	void signal_handler(int sig);
	void	warn(enum msg_id tmp_msg);	// 警告ウィンドゥ表示
	void	warn(std::string tmp_msg);	// 警告ウィンドゥ表示

protected:
	int	adjx(int x);		// 全角X座標を実際の座標に変換する
	int	xyton(int x, int y);	// 二次元の座標を一次元の配列要素に変換する

	std::string	m_title;		// ウィンドゥタイトル

private:

};
#endif // CWINDOWS_H
