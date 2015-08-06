#ifndef CWINSCENARIOEDITOR_H
#define CWINSCENARIOEDITOR_H
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
#include "Config.h"
#include "Data.h"
#include "File.h"



class CWinScenarioEditor : public CWindows
{
public:
	CWinScenarioEditor(CConfig* config);
	virtual ~CWinScenarioEditor();

	virtual int	drawwin();

	void		keyloop();		// �L�[���̓��[�v
	bool		onkeypress_left();	// ���L�[����
	bool		onkeypress_down();	// ���L�[����
	bool		onkeypress_up();	// ��L�[����
	bool		onkeypress_right();	// �E�L�[����

	int		read_mychar();		// �}�C�L�����ǂݍ���

	CString		m_path;			// �f�[�^�i�[�p�X
	int		m_mcnum;		// �}�C�L�����f�[�^�̐�

	CData*		m_data;			// �Q�[�����̂�������

protected:
	void		warn(enum msg_id tmp_msg);	// �x���E�B���h�D�\��

private:
};

#endif // CWINSCENARIOEDITOR_H
