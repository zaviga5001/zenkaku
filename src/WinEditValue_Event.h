#ifndef CWINEDITVALUE_EVENT_H
#define CWINEDITVALUE_EVENT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <string>
#include <ncurses.h>
#include "Windows.h"

class CWinEditValue_Event : public CWinEditValue
{
public:
	CWinEditValue_Event();
	virtual ~CWinEditValue_Event();

	bool	onkeypress_down();	// 下キー押下
	bool	onkeypress_up();	// 上キー押下
	bool	onkeypress_right();	// 右キー押下
	bool	onkeypress_left();	// 左キー押下
	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

protected:

private:
};

#endif // CWINEDITVALUE_EVENT_H
