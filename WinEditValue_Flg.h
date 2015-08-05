#ifndef CWINEDITVALUE_FLG_H
#define CWINEDITVALUE_FLG_H
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

class CWinEditValue_Flg : public CWinEditValue
{
public:
	CWinEditValue_Flg(CData* data);
	virtual ~CWinEditValue_Flg();

	bool	onkeypress_down();	// ���L�[����
	bool	onkeypress_up();	// ��L�[����
	bool	onkeypress_right();	// �E�L�[����
	bool	onkeypress_left();	// ���L�[����
	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

	CData *		m_data;
protected:

private:
};

#endif // CWINEDITVALUE_FLG_H
