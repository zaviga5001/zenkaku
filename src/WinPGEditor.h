#ifndef CWINPGEDITOR_H
#define CWINPGEDITOR_H
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



class CWinPGEditor : public CWindows
{
public:
	CWinPGEditor(CConfig* config);
	virtual ~CWinPGEditor();

	virtual int	drawwin();
	void		push(const CString str, const int id);
	void		push(const CString str, const int id, const int cpair);
	void		change(const CString str, const int id, const int index);
	bool		read_pg(int index);	// �p�[�e�B�Q�ǂݍ���
	void		write_pg(int index);	// �p�[�e�B�Q��������

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
	int	m_maxwidth;		// ���X�g������̍ő啝
	Pos	m_cur;			// �J�[�\���̈ʒu
	Pos	m_dpos;			// ���X�g�̕\���J�n�ʒu�i�����Ή��j

private:
};

#endif // CWINPGEDITOR_H