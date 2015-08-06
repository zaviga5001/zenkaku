#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <locale.h>
#include <ncurses.h>
#include "CString.h"

#include "main.h"
#include "common.h"




int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	// パス取得
	get_zenkaku_home();
	get_user_home();

	// 画面初期化
	if(initscr() == NULL)
	{
		fprintf(stderr, "ERROR:main001:initscr failure\n");
		return 0;
	}
	if(has_colors() == false)
	{
		fprintf(stderr, "ERROR:main002:has_colors failure\n");
		endwin();
		return 0;
	}
	if(start_color() == ERR)
	{
		fprintf(stderr, "ERROR:main003:start_color failure\n");
		endwin();
		return 0;
	}
	if (init_cpairs() == false)
	{
		fprintf(stderr, "ERROR:main004:init_cpairs failure\n");
		endwin();
		return 0;
	}

	// コンフィグ情報格納エリア作成
	CConfig*	config;
	config	= new CConfig();
	if (config == NULL)
	{
		fprintf(stderr, "ERROR:main005:Out of Memory error(config)\n");
		endwin();
		return 0;
	}

	// 設定ファイル読み込み
	CString	fname = ZENKAKURC;
	CFile*	zenkakurc;
	zenkakurc	= new CFile;
	if (zenkakurc == NULL)
	{
		fprintf(stderr, "ERROR:main006:Out of Memory error(zenkakurc)\n");
		endwin();
		return 0;
	}
	zenkakurc->read_cfg(fname, config);
	// ポインタ解放
	delete zenkakurc;

	// タイトル画面
	CTitle*	title;
	title = new CTitle;
	if (title == NULL)
	{
		fprintf(stderr, "ERROR:main007:Out of Memory error(title)\n");
		endwin();
		return 0;
	}
	// タイトル画面表示
	if (title->disp_title(config) == false)
	{
		fprintf(stderr, "ERROR:main008:disp_title failure\n");
		endwin();
		return 0;
	}
	// シナリオ選択
	if (title->select_game(config) == false)
	{
		fprintf(stderr, "ERROR:main009:select_game failure\n");
		endwin();
		return 0;
	}
	// タイトル画面ポインタ解放
	delete title;

	// ゲーム作成
	CGame*	game;
	game = new CGame(config);
	if (game == NULL)
	{
		fprintf(stderr, "ERROR:main010:Out of Memory error(game)\n");
		endwin();
		return 0;
	}
	// ゲームスタート
	game->main();
	// 終了
	delete game;

	// 端末復帰
	endwin();
	return 0;
}

bool init_cpairs()
{
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
	fprintf(stderr, "DEBUG:zenkaku_home=" + zenkaku_home + "\n");
#endif
}

void get_user_home()
{
	user_home = getenv("HOME");

#ifdef	DEBUG
	fprintf(stderr, "DEBUG:user_home=" + user_home + "\n");
#endif
}

