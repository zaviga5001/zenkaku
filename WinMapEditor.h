#ifndef CWINMAPEDITOR_H
#define CWINMAPEDITOR_H
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
#include "Config.h"
#include "Data.h"

#define	MAX_SPPOS	256
#define	MAX_TILE	256
#define	MAX_MAPEVENT	128
#define	MAX_FNAME	64

#include "File.h"



class CWinMapEditor : public CWindows
{
public:
	CWinMapEditor(CConfig* config);
	virtual ~CWinMapEditor();

	virtual int	drawwin();
	void		refreshwin();
	void		refreshpos(int x, int y);
	int		gettile(int x, int y);

	void		keyloop();		// �L�[���̓��[�v
	bool		onkeypress_left();	// ���L�[����
	bool		onkeypress_down();	// ���L�[����
	bool		onkeypress_up();	// ��L�[����
	bool		onkeypress_right();	// �E�L�[����

	// �}�b�v�f�[�^
	Pos		m_dpos;			// �p�b�h��̕\���̈捶��
	Pos		m_cur;			// �J�[�\���ʒu
	CString		m_path;			// �t�@�C����
	MapData		m_mapdata;		// �}�b�v�ɕt������f�[�^
	PosData*	m_posdata;		// �|�W�V�����ɕt������f�[�^
	PosData		m_spposdata[MAX_SPPOS];	// �X�y�V�����|�W�V�����ɕt������f�[�^
	TileData	m_tiledata[MAX_TILE];	// �^�C���ɕt������f�[�^
	int		m_tilenum;		// �^�C���̎��
	PosEvent	m_pevent[MAX_MAPEVENT];	// �|�C���g�C�x���g�f�[�^�x�[�X
	PosEvent	m_sevent[MAX_MAPEVENT];	// �X�g�b�v�C�x���g�f�[�^�x�[�X
	CString		m_fieldname[MAX_FNAME];	// �n��

	PosData		m_posbuf;		// �|�W�V�����f�[�^�R�s�[�p�o�b�t�@
	PosData		m_posundobuf;		// �|�W�V�����f�[�^UNDO�p�o�b�t�@
	PosData		m_posmsk;		// �|�W�V�����f�[�^�R�s�[�p�}�X�N

	CData*		m_data;			// �Q�[�����̂�������

protected:
	void		warn_no_map();		// �}�b�v���ǂݍ��܂�Ă��Ȃ��x��

	int	xyton(int x, int y);	// �񎟌��̍��W���ꎟ���̔z��v�f�ɕϊ�����

private:
};

#endif // CWINMAPEDITOR_H
