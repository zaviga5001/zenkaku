#ifndef CWINMSG_H
#define CWINMSG_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <ncurses.h>
#include <string>
#include "Windows.h"

class CWinMsg : public CWindows
{
public:
	CWinMsg();
	virtual ~CWinMsg();

	virtual int	drawwin();

	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

	std::string	m_msg;			// メッセージ本文

protected:
	int	m_dpos;			// 表示開始文字の位置

private:
};

#endif // CWINMSG_H
