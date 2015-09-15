#ifndef MAIN_H
#define MAIN_H
#include "Config.h"
#include "File.h"
#include "Title.h"
#include "Game.h"
#include "Editor.h"


int		main(int argc, char *argv[]);
bool		init_cpairs();
void		get_zenkaku_home();
void		get_user_home();
void		main_debug();

std::string	zenkaku_home;	// プログラムのホームディレクトリ
std::string	user_home;	// ユーザのホームディレクトリ

#endif	// MAIN_H
