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

	bool	onkeypress_down();	// ���L�[����
	bool	onkeypress_up();	// ��L�[����
	bool	onkeypress_right();	// �E�L�[����
	bool	onkeypress_left();	// ���L�[����
	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

protected:

private:
};

#endif // CWINEDITVALUE_CMASK_H
