#ifndef CWINEDITVALUE_H
#define CWINEDITVALUE_H
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

class CWinEditValue : public CWindows
{
public:
	CWinEditValue();
	virtual ~CWinEditValue();

	virtual int	drawwin();
	void		push(const CString str, void * ptr, const int chr, const int num);
	void		push(const CString str, void * ptr, const int chr, const int num, const int cpair);

	Pos	m_wpos;			// �E�B���h�E��̕\���ʒu

	virtual bool	onkeypress_down();	// ���L�[����
	virtual bool	onkeypress_up();	// ��L�[����
	virtual bool	onkeypress_right();	// �E�L�[����
	virtual bool	onkeypress_left();	// ���L�[����
	virtual bool	onkeypress_ok();	// �n�j�L�[����
	virtual bool	onkeypress_cancel();	// �L�����Z���L�[����

	int	m_disable_cansel;	// �L�����Z���{�^�����������ǂ���

protected:
	CString	encode(void* ptr, const int chr, const int num);
	void	decode(CString* str, void* ptr, const int chr);

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

#endif // CWINEDITVALUE_H
