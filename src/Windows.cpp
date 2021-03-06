#include "Windows.h"

CWindows::CWindows()
{
	cbreak();
	noecho();
	curs_set(0); 

	// デフォルトカラー初期化
	setdefcpair(0);

	// 属性テーブル
	for(long j = 0; j < ATTR_NUM; j++)
	{
		m_attrs[j] = A_NORMAL + j;
	};

	m_return = 0;
	m_returnstr = "";
}

CWindows::~CWindows()
{
	delwin(m_this);
}

// 表示開始
//
int CWindows::startwin(bool frame)
{
	m_this = newwin(m_winh, adjx(m_winw), m_winy, adjx(m_winx));
	refresh();

	if (frame)	drawframe();
	drawwin();
	keyloop();

	return (m_return);
}

// 表示開始
//
std::string CWindows::startdialog(bool frame)
{
	m_this = newwin(m_winh, adjx(m_winw), m_winy, adjx(m_winx));
	refresh();

	if (frame)	drawframe();
	drawwin();
	keyloop();

	return (m_returnstr);
}

// ウィンドゥタイトルをセットする
//
void CWindows::settitle(const std::string title)
{
	m_title = title;
}

// ウィンドゥのサイズを決める
//
void CWindows::setsize(int max_w, int max_h)
{
	if (adjx(max_w) > COLS || max_w == 0)	m_winw = (COLS) / 2;
	else					m_winw = max_w;
	if (max_h      > LINES || max_h == 0)	m_winh = LINES;
	else					m_winh = max_h;
}

// ウィンドゥの表示位置を調整する
//
void CWindows::movewin(int pos, int from)
{
	switch(pos)
	{
		case 1:		// 左下
			m_winx = 0 + from;
			m_winy = LINES - m_winh - from;
			break;
		case 2:		// 下
			m_winx = ((COLS / 2) - m_winw) / 2;
			m_winy = LINES - m_winh - from;
			break;
		case 3:		// 右下
			m_winx = (COLS / 2) - m_winw - from;
			m_winy = LINES - m_winh - from;
			break;
		case 4:		// 左
			m_winx = 0 + from;
			m_winy = (LINES - m_winh) / 2;
			break;
		case 5:		// 中央（fromは無視）
			m_winx = ((COLS / 2) - m_winw) / 2;
			m_winy = (LINES - m_winh) / 2;
			break;
		case 6:		// 右
			m_winx = (COLS / 2) - m_winw - from;
			m_winy = (LINES - m_winh) / 2;
			break;
		case 7:		// 左上
			m_winx = 0 + from;
			m_winy = 0 + from;
			break;
		case 8:		// 上
			m_winx = ((COLS / 2) - m_winw) / 2;
			m_winy = 0 + from;
			break;
		case 9:		// 右上
			m_winx = (COLS / 2) - m_winw - from;
			m_winy = 0 + from;
			break;
		default:
			break;
	};
	if (m_winx < 0)	m_winx = 0;
	if (m_winy < 0)	m_winy = 0;
}

// カラーペア番号を取得する
//
int CWindows::getcpair(int ch, int bg)
{
	return ((COLOR_NUM - ch - 1) + (bg * COLOR_NUM));
}

// デフォルトカラーをセットする
//
void CWindows::setdefcpair(int ch, int bg)
{
	setdefcpair(getcpair(ch, bg));
}
// デフォルトカラーをセットする
//
void CWindows::setdefcpair(int cpair)
{
	m_cpair = cpair;
}

// カラーペア番号を分解する
//
int CWindows::getchcolor(int cpair)
{
	return (COLOR_NUM - (cpair % COLOR_NUM) - 1);
}

// カラーペア番号を分解する
//
int CWindows::getbgcolor(int cpair)
{
	return (cpair / COLOR_NUM);
}

// フレーム描画
//
void CWindows::drawframe()
{
	// デフォルトカラーで描画
	wattrset(m_this, COLOR_PAIR(m_cpair));

	for (int i = 2; i < adjx(m_winw - 1); i = i + 2)
	{
		mvwprintw(m_this, 0,        i, "%s", msg[MY_MSG_WIN_YOKO].msg);
		mvwprintw(m_this, m_winh-1, i, "%s", msg[MY_MSG_WIN_YOKO].msg);
	}
	mvwprintw(m_this, 0,   0,                "%s", msg[MY_MSG_WIN_7].msg);
	mvwprintw(m_this, 0,   adjx(m_winw - 1), "%s", msg[MY_MSG_WIN_9].msg);
	for (int i = 1; i < m_winh - 1; i++)
	{
		mvwprintw(m_this, i, 0,                "%s", msg[MY_MSG_WIN_TATE].msg);
		mvwprintw(m_this, i, adjx(m_winw - 1), "%s", msg[MY_MSG_WIN_TATE].msg);
	}
	mvwprintw(m_this, m_winh-1, 0,                "%s", msg[MY_MSG_WIN_1].msg);
	mvwprintw(m_this, m_winh-1, adjx(m_winw - 1), "%s", msg[MY_MSG_WIN_3].msg);

	if (m_title != "")
	{	// ウィンドウタイトル表示
		std::string tmp_str = CMyStr::substr(m_title, 0, m_winw - 2);
		mvwprintw(m_this, 0, 2,   "%s", tmp_str.c_str());
	}

	wrefresh(m_this);
}

// ウィンドゥを罫線により分割する
//
void CWindows::splitwin(int pos)
{
	// システムカラーで描画
	wattrset(m_this, COLOR_PAIR(m_cpair));

	mvwprintw(m_this, pos, 0,   "%s", msg[MY_MSG_WIN_4].msg);
	for (int i = 2; i < adjx(m_winw - 1); i = i + 2)
	{
		mvwprintw(m_this, pos, i, "%s", msg[MY_MSG_WIN_YOKO].msg);
	}
	mvwprintw(m_this, pos, adjx(m_winw - 1), "%s", msg[MY_MSG_WIN_6].msg);
	wrefresh(m_this);
}

// メッセージ表示
// 改行対応なし（色指定なし）
//
void CWindows::setmessage(int x, int y, std::string message)
{
	setmessage(x, y, message, m_cpair);
}
// メッセージ表示
// 改行対応なし（色指定あり）
//
void CWindows::setmessage(int x, int y, std::string message, int ch, int bg)
{
	setmessage(x, y, message, getcpair(ch, bg));
}
// メッセージ表示
// 改行対応なし
//
void CWindows::setmessage(int x, int y, std::string message, int cpair)
{
	wattrset(m_this, COLOR_PAIR(cpair));

	mvwaddstrtoeol(x, y, message);
	wrefresh(m_this);
}

// メッセージ表示
// 改行対応（色指定なし）
//
int CWindows::setmessage_n(int x, int y, std::string message)
{
	return (setmessage_n(x, y, message, m_cpair));
}
// メッセージ表示
// 改行対応
//
int CWindows::setmessage_n(int x, int y, std::string message, int ch, int bg)
{
	return (setmessage_n(x, y, message, getcpair(ch, bg)));
}
// メッセージ表示
// 改行対応（色指定あり）
//
int CWindows::setmessage_n(int x, int y, std::string message, int cpair)
{
	int	waittime = 0, i = 0, dposx = 0;
	std::vector<std::string> messvect = CMyStr::separate(message);

	wattrset(m_this, COLOR_PAIR(cpair));

	for (i = 0; i < messvect.size(); i++)
	{
		if (messvect[i].compare("k") == 0)
		{	// キー入力待ち記号

			keyloop();
			continue;
		}
		else if (messvect[i].compare("p") == 0)
		{	// 改ページ記号
			keyloop();
			i++;
			break;
		}
		else if (messvect[i].compare("n") == 0)
		{	// 改行記号
			// 改行
			i++;
			dposx = 0;
			y++;
		}
		else if (messvect[i].compare("t") == 0)
		{	// ウェイトタイム記号
			std::string tmpwait;
			tmpwait = messvect[i+1] + messvect[i+2] + messvect[i+3];
			waittime = atoi(tmpwait.c_str());
			i += 3;
			continue;
		}
		else if (messvect[i].compare("c") == 0)
		{	// 色指定記号
			int tmp_ch, tmp_bg;
			if (messvect[i + 1].compare("c") == 0)
			{	// 色戻す
				tmp_ch = getchcolor(m_cpair);
			}
			else
			{	// 色付ける
				tmp_ch = atoi(messvect[i + 1].c_str());
			}
			if (messvect[i + 2].compare("c") == 0)
			{	// 色戻す
				tmp_bg = getbgcolor(m_cpair);
			}
			else
			{	// 色付ける
				tmp_bg = atoi(messvect[i + 2].c_str());
			}
			wattrset(m_this, COLOR_PAIR(getcpair(tmp_ch, tmp_bg)));
			i += 2;
			continue;
		}

		if (adjx(x) + dposx >= adjx(m_winw - 1))
		{	// ウィンドゥの右端まで到達
			// 改行
			dposx = 0;
			y++;
		}
		if (y >= m_winh - 1)
		{
			keyloop();
			break;	// ウィンドゥの終わりに到達
		}

		mvwprintw(m_this, y, adjx(x) + dposx, "%s", messvect[i].c_str());
		dposx += 2;

		if (waittime > 0)
		{
			wrefresh(m_this);
			usleep(waittime * 1000);	// 1000 = 1ミリ秒
		}
	}
	wattrset(m_this, COLOR_PAIR(m_cpair));
	wrefresh(m_this);
	return(i);
}

// 上下左右に移動できるメニューを表示
// 
void CWindows::seticon(Pos pos, Pos* cur, Pos* dpos, std::vector<std::string> list, std::vector<int> cpair, int col)
{
	int	num = list.size();		// アイテムの個数
	int	x, y;

	if (cur->x < dpos->x)	dpos->x = cur->x;
	if (cur->y < dpos->y)	dpos->y = cur->y;
	if (cur->x - dpos->x + pos.x >= m_winw - 2)	dpos->x = cur->x - m_winw + pos.x + 2;
	if (cur->y - dpos->y + pos.y >= m_winh - 2)	dpos->y = cur->y - m_winh + pos.y + 2;

	for (int i = 0; i < num; i++)
	{
		x = i % col;
		y = i / col;

		if (x < dpos->x)	continue;
		if (y < dpos->y)	continue;
		if (x - dpos->x + pos.x >= m_winw - 1)	continue;
		if (y - dpos->y + pos.y >= m_winh - 1)	continue;
		// 表示する
		if (x == cur->x && y == cur->y)	wattrset(m_this, WA_REVERSE | COLOR_PAIR(cpair[i]));
		else				wattrset(m_this, WA_NORMAL  | COLOR_PAIR(cpair[i]));
		mvwprintw(m_this, y - dpos->y + pos.y, adjx(x - dpos->x + pos.x), "%s", list[i].c_str());
	}

	wrefresh(m_this);
}

// 左右にカーソル移動できるメニューを表示
// 色塗り未対応
// 
void CWindows::setselect(int x, int y, int* posx, int* dposx, std::vector<std::string> list, std::vector<int> cpair)
{
	std::string	str;		// アイテムを全て連結した文字列
	int	num = list.size();	// アイテムの個数
	int 	pos_l = 0, pos_r = 0;	// カーソルが合っているメニュー文字列の左右端座標
	int	width;			// 表示領域の幅
	width = m_winw - x - 1;

	for (int i = 0; i < num; i++)
	{
		if (i != 0)	str += "　";
		if (i == *posx)	pos_l = CMyStr::length(str);	// 左端座標取得
		str += list[i];
		if (i == *posx)	pos_r = CMyStr::length(str);	// 右端座標取得
	}

	if (pos_l < *dposx)		*dposx = pos_l;		// 左にシフト
	if (pos_r > *dposx + width)	*dposx = pos_r - width;	// 右にシフト

	// 表示する
	mvwaddstrtoeol(x, y, str.substr(adjx(*dposx)));

	// 選択中アイテム反転
	mvwchgat(m_this, y, adjx(pos_l - *dposx + x), adjx(CMyStr::length(list[*posx])), WA_REVERSE, 0, NULL);

	wrefresh(m_this);
}

// 上下に選択できるリストを表示
// 
void CWindows::setlist(int x, int y, int* dposx, int* posy, int* dposy, std::vector<std::string> list, std::vector<int> cpair)
{
	int num = list.size();
	if (*posy < *dposy)				*dposy = *posy;
	if (*posy - *dposy > (m_winh - y - 2) &&
	    *posy < num                         )	*dposy = *dposy + 1;
	if (*posy > num)				*posy  = *posy  - 1;

	for (int i = 0; i < num; i++)
	{
		if (i + y >= m_winh - 1)	break;

		if (*posy == *dposy + i)	wattron(m_this,  A_REVERSE | COLOR_PAIR(cpair[i]));
		else				wattrset(m_this, A_NORMAL | COLOR_PAIR(cpair[i]));

		if (list[*dposy + i].substr(adjx(*dposx)) == "")
			mvwaddstrtoeol(x, y + i, std::string(""));
		else
			mvwaddstrtoeol(x, y + i, list[*dposy + i].substr(adjx(*dposx)));
	}
	wrefresh(m_this);
}

// 上下に選択できるエディットフィールドを表示
// 
void CWindows::setedit(int x, int y, int* posy, int* dposy, std::vector<std::string> name, std::vector<std::string> value, std::vector<int> cpair, std::vector<int> max_num)
{
	std::string	tmp_str;
	int	num = name.size();
	int	max_size = 0;
	int	i, j;

	if (*posy < *dposy)				*dposy = *posy;
	for ( ; ; )
	{
		if (*posy - *dposy > (m_winh - y - 2) &&
		    *posy < num                         )	*dposy = *dposy + 1;
		else
			break;
	}
	if (*posy > num)				*posy  = *posy  - 1;

	for (i = 0; i < num; i++)
	{
		if (max_size < CMyStr::length(name[i]) && name[i] != "--------------")
		{
			max_size = CMyStr::length(name[i]);
		}
	}
	max_size += 2;

	for (i = 0; i < num; i++)
	{
		if (i + y >= m_winh - 1)	break;

		tmp_str = name[i + *dposy];
		for (j = 0; j < (max_size - CMyStr::length(name[i + *dposy])); j++)
		{
			tmp_str = tmp_str + "　";
		}
		mvwaddstrtoeol(x, y + i, tmp_str);

		if (*posy == *dposy + i)	wattron(m_this,  A_REVERSE | COLOR_PAIR(cpair[i]));
		else				wattrset(m_this, A_NORMAL | COLOR_PAIR(cpair[i]));

		mvwaddstrtoeol(max_size + 1, y + i, value[i + *dposy]);
	}
	wrefresh(m_this);
}

// カーソル以降行末まで削除した後、右端に全角罫線を表示する
// 
void CWindows::wclrtorborder()
{
	int x, y;
	getyx(m_this, y, x);

	wattrset(m_this, COLOR_PAIR(m_cpair));
	wclrtoeol(m_this);
	mvwprintw(m_this, y, adjx(m_winw - 1), "%s", msg[MY_MSG_WIN_TATE].msg);
}

// ウィンドゥ内部をクリアする（罫線は残す）
// 
void CWindows::clearwin()
{
	werase(m_this);
	drawframe();
}

// 行末まで文字列を表示（罫線は残す）
// 
bool CWindows::mvwaddstrtoeol(int cur_x, int cur_y, const std::string str)
{
	std::string tmp_str = CMyStr::substr(str, 0, m_winw - cur_x - 1);
	mvwprintw(m_this, cur_y, adjx(cur_x), "%s", tmp_str.c_str());
	wclrtorborder();
	if (m_winw - cur_x - 1 > CMyStr::length(str))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// 色は変えずに属性を変える
//
void CWindows::chg_attr(int x, int y, long attr)
{
	chtype ch1 = mvwinch(m_this, y, adjx(x))	& A_CHARTEXT;
	chtype ch2 = mvwinch(m_this, y, adjx(x) + 1)	& A_CHARTEXT;
	chtype ch1c = mvwinch(m_this, y, adjx(x))	& A_COLOR;

	wattrset(m_this, attr | ch1c);

	mvwaddch(m_this, y, adjx(x),     ch1);
	mvwaddch(m_this, y, adjx(x) + 1, ch2);
}

// 属性は変えずに色を変える
//
void CWindows::chg_color(int x, int y, int ch, int bg)
{
	chg_color(x, y, getcpair(ch, bg));
}
// 属性は変えずに色を変える
//
void CWindows::chg_color(int x, int y, int cpair)
{
	chtype ch1 = mvwinch(m_this, y, adjx(x))	| !A_COLOR;
	chtype ch2 = mvwinch(m_this, y, adjx(x) + 1)	| !A_COLOR;

	ch1 += COLOR_PAIR(cpair);
	ch2 += COLOR_PAIR(cpair);

	mvwaddch(m_this, y, adjx(x),     ch1);
	mvwaddch(m_this, y, adjx(x) + 1, ch2);
}

// 属性と色を変える
//
void CWindows::chg_attr_color(int x, int y, long attr, int ch, int bg)
{
	chg_attr_color(x, y, attr, getcpair(ch, bg));
}
// 属性と色を変える
//
void CWindows::chg_attr_color(int x, int y, long attr, int cpair)
{
	chtype ch1 = mvwinch(m_this, y, adjx(x))	& A_CHARTEXT;
	chtype ch2 = mvwinch(m_this, y, adjx(x) + 1)	& A_CHARTEXT;

	wattrset(m_this, attr | COLOR_PAIR(cpair));

	mvwaddch(m_this, y, adjx(x),     ch1);
	mvwaddch(m_this, y, adjx(x) + 1, ch2);
}

// キー入力ループ
// 
void CWindows::keyloop()
{
	flushinp();
	timeout(-1);	// キー入力で待つ

	for( ; ; )
	{
		int ch = wgetch(m_this);
		switch(ch)
		{
			case MYKEY_LEFT:
				if (!onkeypress_left())		return;
				break;
			case MYKEY_DOWN:
				if (!onkeypress_down())		return;
				break;
			case MYKEY_UP:
				if (!onkeypress_up())		return;
				break;
			case MYKEY_RIGHT:
				if (!onkeypress_right())	return;
				break;
			case MYKEY_OK:
				if (!onkeypress_ok())		return;
				break;
			case MYKEY_CANCEL:
				if (!onkeypress_cancel())	return;
				break;
			default:
				continue;
		}
	}
}

bool CWindows::onkeypress_left()	{ return true; }	// キーループ継続
bool CWindows::onkeypress_down()	{ return true; }	// キーループ継続
bool CWindows::onkeypress_up()		{ return true; }	// キーループ継続
bool CWindows::onkeypress_right()	{ return true; }	// キーループ継続
bool CWindows::onkeypress_ok()		{ return true; }	// キーループ継続
bool CWindows::onkeypress_cancel()	{ return false; }	// キーループ終了

// 全角X座標を実際のX座標に変換する
int CWindows::adjx(int x){
	return x * 2;
}

// 二次元の座標を一次元の配列要素に変換する
int CWindows::xyton(int x, int y){
	return (y * m_winw + x);
}

// 強制終了シグナル
void CWindows::signal_handler(int sig){
	endwin();
	//exit(EXIT_FAILURE);
}

void CWindows::warn(enum msg_id tmp_msg)
{
	WINDOW* warn_win;
	warn_win = newwin(20, 40, 10, 10);
	refresh();

	wattrset(warn_win, COLOR_PAIR(getcpair(1, 7)));

	mvwprintw(warn_win, 1, 1, "%s", msg[tmp_msg].msg);
	wrefresh(warn_win);

	getchar();
	delwin(warn_win);
}

void CWindows::warn(std::string tmp_msg)
{
	WINDOW* warn_win;
	warn_win = newwin(20, 40, 10, 10);
	refresh();

	wattrset(warn_win, COLOR_PAIR(getcpair(1, 7)));

	mvwprintw(warn_win, 1, 1, "%s", tmp_msg.c_str());
	wrefresh(warn_win);

	getchar();
	delwin(warn_win);
}

