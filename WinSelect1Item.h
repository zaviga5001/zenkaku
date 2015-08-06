#ifndef CWINSELECT1ITEM_H
#define CWINSELECT1ITEM_H
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

class CWinSelect1Item : public CWindows
{
public:
	CWinSelect1Item();
	virtual ~CWinSelect1Item();

	virtual int	drawwin();
	void		push(const CString str, const int id);
	void		push(const CString str, const int id, const int cpair);

	Pos	m_wpos;			// �E�B���h�E��̕\���ʒu

	bool	onkeypress_left();	// ���L�[����
	bool	onkeypress_down();	// ���L�[����
	bool	onkeypress_up();	// ��L�[����
	bool	onkeypress_right();	// �E�L�[����
	bool	onkeypress_ok();	// �n�j�L�[����
	bool	onkeypress_cancel();	// �L�����Z���L�[����

	int	m_disable_cansel;	// �L�����Z���{�^�����������ǂ���

	CString	m_msg;			// ���b�Z�[�W
	int	m_split;		// �X�v���b�^�̈ʒu

protected:
	std::vector<CString>	m_list;		// �v�f
	std::vector<int>	m_cp;		// �F
	std::vector<int>	m_index;	// �l
	int	m_maxwidth;		// ���X�g������̍ő啝
	Pos	m_cur;			// �J�[�\���̈ʒu
	Pos	m_dpos;			// ���X�g�̕\���J�n�ʒu�i�����Ή��j

private:
};

#endif // CWINSELECT1ITEM_H
