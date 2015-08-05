#ifndef CWINEDITVALUE_CMASK_H
#define CWINEDITVALUE_CMASK_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include "include/curses.h"
#include "Windows.h"
#include "CString.h"

class CWinEditValue_Cmask : public CWinEditValue
{
public:
	CWinEditValue_Cmask();
	virtual ~CWinEditValue_Cmask();

	bool	onkeypress_down();	// 下キー押下
	bool	onkeypress_up();	// 上キー押下
	bool	onkeypress_right();	// 右キー押下
	bool	onkeypress_left();	// 左キー押下
	bool	onkeypress_ok();	// ＯＫキー押下
	bool	onkeypress_cancel();	// キャンセルキー押下

protected:

private:
};

#endif // CWINEDITVALUE_CMASK_H
