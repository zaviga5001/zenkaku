#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ncurses.h>
#include "CString.h"

#include "main.h"
#include "common.h"




int main(int argc, char *argv[])
{
	// �ѥ�����
	get_zenkaku_home();
	get_user_home();

	// ���̽����
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

	// ����ե��������Ǽ���ꥢ����
	CConfig*	config;
	config	= new CConfig();
	if (config == NULL)
	{
		fprintf(stderr, "ERROR:main005:Out of Memory error(config)\n");
		endwin();
		return 0;
	}

	// ����ե������ɤ߹���
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
	// �ݥ��󥿲���
	delete zenkakurc;

	// �����ȥ����
	CTitle*	title;
	title = new CTitle;
	if (title == NULL)
	{
		fprintf(stderr, "ERROR:main007:Out of Memory error(title)\n");
		endwin();
		return 0;
	}
	// �����ȥ����ɽ��
	if (title->disp_title(config) == false)
	{
		fprintf(stderr, "ERROR:main008:disp_title failure\n");
		endwin();
		return 0;
	}
	// ���ʥꥪ����
	if (title->select_game(config) == false)
	{
		fprintf(stderr, "ERROR:main009:select_game failure\n");
		endwin();
		return 0;
	}
	// �����ȥ���̥ݥ��󥿲���
	delete title;

	// ���������
	CGame*	game;
	game = new CGame(config);
	if (game == NULL)
	{
		fprintf(stderr, "ERROR:main010:Out of Memory error(game)\n");
		endwin();
		return 0;
	}
	// �����ॹ������
	game->main();
	// ��λ
	delete game;

	// ü������
	endwin();
	return 0;
}

bool init_cpairs()
{
	int i, j, num = 0;

	// ���顼�ơ��֥�
	int colors[COLOR_NUM];
	for(i = 0; i < COLOR_NUM; i++)
	{
		colors[i] = COLOR_BLACK + i;
	}

	// ���顼�ڥ��ơ��֥�
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

