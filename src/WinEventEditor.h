#ifndef CWINEVENTEDITOR_H
#define CWINEVENTEDITOR_H
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



class CWinEventEditor : public CWindows
{
public:
	CWinEventEditor(CConfig* config);
	virtual ~CWinEventEditor();

	virtual int	drawwin();
	void		push(const CString str, const int id);
	void		push(const CString str, const int id, const int cpair);
	void		change(const CString str, const int id, const int index);
	void		read_event();		// �C�x���g�ǂݍ���
	void		write_event(int index);	// �C�x���g��������

	Pos		m_wpos;			// �E�B���h�E��̕\���ʒu

	void		keyloop();		// �L�[���̓��[�v
	bool		onkeypress_left();	// ���L�[����
	bool		onkeypress_down();	// ���L�[����
	bool		onkeypress_up();	// ��L�[����
	bool		onkeypress_right();	// �E�L�[����
	virtual bool	onkeypress_ok();	// �n�j�L�[����
	virtual bool	onkeypress_cancel();	// �L�����Z���L�[����

	CData*		m_data;			// �Q�[�����̂�������

protected:
	void	warn(enum msg_id tmp_msg);	// �x���E�B���h�D�\��

	std::vector<CString>	m_list;		// �v�f
	std::vector<int>	m_cp;		// �F
	std::vector<int>	m_index;	// �l
	int	m_maxwidth;			// ���X�g������̍ő啝
	Pos	m_cur;				// �J�[�\���̈ʒu
	Pos	m_dpos;				// ���X�g�̕\���J�n�ʒu�i�����Ή��j

private:
};

#endif // CWINEVENTEDITOR_H