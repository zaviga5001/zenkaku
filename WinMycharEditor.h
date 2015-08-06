#ifndef CWINMYCHAREDITOR_H
#define CWINMYCHAREDITOR_H
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



class CWinMycharEditor : public CWindows
{
public:
	CWinMycharEditor(CConfig* config);
	virtual ~CWinMycharEditor();

	virtual int	drawwin();
	void		push(const CString str, void * ptr, const int chr, const int num);
	void		push(const CString str, void * ptr, const int chr, const int num, const int cpair);
	void		read_mychar();		// �}�C�L�����ǂݍ���
	void		write_mychar();		// �}�C�L������������


	void		keyloop();		// �L�[���̓��[�v
	virtual bool	onkeypress_down();	// ���L�[����
	virtual bool	onkeypress_up();	// ��L�[����
	virtual bool	onkeypress_right();	// �E�L�[����
	virtual bool	onkeypress_left();	// ���L�[����
	virtual bool	onkeypress_ok();	// �n�j�L�[����
	virtual bool	onkeypress_cancel();	// �L�����Z���L�[����

	CData*	m_data;				// �Q�[�����̂�������
	Pos	m_wpos;				// �E�B���h�E��̕\���ʒu

protected:
	CString	encode(void* ptr, const int chr, const int num);
	void	decode(CString* str, void* ptr, const int chr);
	void		warn(enum msg_id tmp_msg);	// �x���E�B���h�D�\��

	std::vector<CString>	m_name;	// �v�f��
	std::vector<CString>	m_value;// �l�i������ϊ��j
	std::vector<void*>	m_ptr;	// �|�C���^
	std::vector<int>	m_my_tt;// �ϐ��̌^
	std::vector<int>	m_size;	// �z��̌�
	std::vector<int>	m_cp;	// �F
	Pos	m_cur;			// �J�[�\���̈ʒu
	Pos	m_dpos;			// ���X�g�̕\���J�n�ʒu�i�����Ή��j

private:
};

#endif // CWINMYCHAREDITOR_H
