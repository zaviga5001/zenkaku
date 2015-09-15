#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <locale.h>
#include <ncurses.h>
#include <sstream>
#include <string>

#include "common.h"
#include "main.h"




int main(int argc, char *argv[])
{
	using namespace std;
	setlocale(LC_ALL, "");

//	main_debug();

	// パス取得
	get_zenkaku_home();
	get_user_home();

	// 画面初期化
	if(initscr() == NULL)
	{
		cerr << "ERROR:main001:initscr failure" << endl;
		return 0;
	}
	if(has_colors() == false)
	{
		cerr << "ERROR:main002:has_colors failure" << endl;
		endwin();
		return 0;
	}
	if(start_color() == ERR)
	{
		cerr << "ERROR:main003:start_color failure" << endl;
		endwin();
		return 0;
	}
	if (init_cpairs() == false)
	{
		cerr << "ERROR:main004:init_cpairs failure" << endl;
		endwin();
		return 0;
	}

	// ゲームデータ格納エリア作成
	CData*	data;
	data	= new CData();
	if (data == NULL)
	{
		cerr << "ERROR:main005:Out of Memory error(data)" << endl;
		endwin();
		return 0;
	}

	// コンフィグ情報格納エリア作成
	CConfig*	config;
	config	= new CConfig();
	if (config == NULL)
	{
		cerr << "ERROR:main006:Out of Memory error(config)" << endl;
		endwin();
		return 0;
	}

	// ファイルハンドラクラス作成
	CFile*	file;
	file	= new CFile();
	if (file == NULL)
	{
		cerr << "ERROR:main007:Out of Memory error(file)" << endl;
		endwin();
		return 0;
	}

	// 設定ファイル読み込み
	file->read_cfg(config);

	// タイトル画面
	CTitle*	title;
	title = new CTitle;
	if (title == NULL)
	{
		cerr << "ERROR:main008:Out of Memory error(title)" << endl;
		endwin();
		return 0;
	}
	// タイトル画面表示
	if (title->disp_title(config) == false)
	{
		cerr << "ERROR:main009:disp_title failure" << endl;
		endwin();
		return 0;
	}
	// シナリオ選択
	if (title->select_game(data, config, file) == false)
	{
		cerr << "ERROR:main009:select_game failure" << endl;
		endwin();
		return 0;
	}
	// タイトル画面ポインタ解放
	delete title;

	if (config->m_mode == 0)
	{	// Game
		// ゲーム作成
		CGame*	game;
		game = new CGame(data, config, file);
		if (game == NULL)
		{
			cerr << "ERROR:main010:Out of Memory error(game)" << endl;
			endwin();
			return 0;
		}
		// ゲームスタート
		game->main();
		// 終了
		delete game;
	}
	else
	{	// Editor
		// エディタ作成
		CEditor*	editor;
		editor = new CEditor(data, config, file);
		if (editor == NULL)
		{
			cerr << "ERROR:main011:Out of Memory error(editor)" << endl;
			endwin();
			return 0;
		}
		// エディタスタート
		editor->main();
		// 終了
		delete editor;
	}
	
	// 端末復帰
	endwin();
	return 0;
}

bool init_cpairs()
{
	using namespace std;

	int i, j, num = 0;

	// カラーテーブル
	int colors[COLOR_NUM];
	for(i = 0; i < COLOR_NUM; i++)
	{
		colors[i] = COLOR_BLACK + i;
	}

	// カラーペアテーブル
	for(i = 0; i < COLOR_NUM; i++)
	{
		for(j = 0; j < COLOR_NUM; j++)
		{
			if (num > 0)
			{
				init_pair(num, colors[COLOR_NUM - j - 1], colors[i]);
			}
			num++;
		}
	}
	return true;
}

void get_zenkaku_home()
{
	using namespace std;

	int i;
	char buf[1024];
	memset(buf, 0, 1024);
	readlink("/proc/self/exe", buf, sizeof(buf));
	for (i = 1023; i > 0; i--)
	{
		if (buf[i] == '/')	break;
	}
	buf[i] = 0;
	zenkaku_home = buf;
	
#ifdef	DEBUG
	cerr << "DEBUG:zenkaku_home=" << zenkaku_home << endl;
#endif
}

void get_user_home()
{
	using namespace std;

	user_home = getenv("HOME");

#ifdef	DEBUG
	cerr << "DEBUG:user_home=" << user_home << endl;
#endif
}


void main_debug()
{
	using namespace std;

	string str1 = "あいうえお";
	string str2 = "ABCDE";
	string str3 = "ABCDEあいうえお";
	string str4 = "あAいBうCえDおE";
	string str5 = "あいうK1えお";

	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;
	cout << str4 << endl;
	cout << str5 << endl;

	cout << mystd::to_string(str1.length()) << endl;
	cout << mystd::to_string(str2.length()) << endl;
	cout << mystd::to_string(str3.length()) << endl;
	cout << mystd::to_string(str4.length()) << endl;
	cout << mystd::to_string(str5.length()) << endl;

	cout << mystd::to_string(CMyStr::length(str1)) << endl;
	cout << mystd::to_string(CMyStr::length(str2)) << endl;
	cout << mystd::to_string(CMyStr::length(str3)) << endl;
	cout << mystd::to_string(CMyStr::length(str4)) << endl;
	cout << mystd::to_string(CMyStr::length(str5)) << endl;

	cout << CMyStr::substr(str1, 2, 2) << endl;
	cout << CMyStr::substr(str2, 1, 3) << endl;
	cout << CMyStr::substr(str3, 3, 1) << endl;
	cout << CMyStr::substr(str4, 3, 4) << endl;
	cout << CMyStr::substr(str5, 3, 2) << endl;

	getchar();
}
