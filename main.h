#ifndef MAIN_H
#define MAIN_H
#include "Config.h"
#include "File.h"
#include "Title.h"
#include "Game.h"
#include "CString.h"


#define	ZENKAKURC	"/home/randy/.zenkaku/zenkakurc"


int		main(int argc, char *argv[]);
bool		init_cpairs();
void		get_zenkaku_home();
void		get_user_home();

CString		zenkaku_home;	// �v���O�����̃z�[���f�B���N�g��
CString		user_home;	// ���[�U�̃z�[���f�B���N�g��

#endif	// MAIN_H
