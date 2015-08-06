#ifndef CWINEDITVALUE_EVENT_H
#define CWINEDITVALUE_EVENT_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <ncurses.h>
#include "Windows.h"
#include "CString.h"

class CWinEditValue_Event : public CWinEditValue
{
public:
	CWinEditValue_Event();
	virtual ~CWinEditValue_Event();

	bool	onkeypress_down();	// ���L�[����
	bool	onkeypress_up();	// ��L�[����
	bool	onkeypress_right();	// �E�L�[����
	bool	onkeypress_left();	// ���L�[����
	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

protected:

private:
};

#endif // CWINEDITVALUE_EVENT_H
