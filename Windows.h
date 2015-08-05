#ifndef CWINDOWS_H
#define CWINDOWS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include "include/curses.h"
#include "common.h"
#include "msg.h"
#include "CString.h"
#include "Data.h"

#define	MYKEY_LEFT	68
#define	MYKEY_DOWN	66
#define	MYKEY_UP	65
#define	MYKEY_RIGHT	67
#define	MYKEY_OK	'x'
#define	MYKEY_CANCEL	'z'

#define	COLOR_NUM	8
#define	ATTR_NUM	11
#define	SYSTEM_COLOR_NUM	63

//	��
//		COLOR_BLACK
//		COLOR_RED
//		COLOR_GREEN
//		COLOR_YELLOW
//		COLOR_BLUE
//		COLOR_MAGENTA
//		COLOR_CYAN
//		COLOR_WHITE

//	°��
//		A_NORMAL
//		A_STANDOUT
//		A_UNDERLINE
//		A_REVERSE
//		A_BLINK
//		A_DIM
//		A_BOLD
//		A_PROTECT
//		A_INVIS
//		A_ALTCHARSET
//		A_CHARTEXT

enum	my_tt {
	TT_SPC,
	TT_CHR,
	TT_STR,
	TT_BYT,
	TT_CST,
	TT_INT,
	TT_UINT,
	TT_SHT,
	TT_LNG,
	TT_VCT
};

class CWindows
{
public:
	CWindows();
	virtual ~CWindows();

	int	startwin(bool frame);			// ɽ�����ϡʥե졼���ա�
	CString	startdialog(bool frame);		// ɽ�����ϡ�ʸ������귿��

	void	settitle(const CString title);		// ������ɥ������ȥ��ɽ������
	void	setsize(int w, int h);			// ���̥����������
	void	movewin(int x, int y);			// ɽ�����֤��ư����
	int	getcpair(int ch, int bg);		// ���顼�ڥ��ֹ���������
	int	getchcolor(int cpair);			// ���顼�ڥ��ֹ��ʬ�򤹤�
	int	getbgcolor(int cpair);			// ���顼�ڥ��ֹ��ʬ�򤹤�
	void	setdefcpair(int cpair);			// �ǥե���ȥ��顼�򥻥åȤ���
	void	setdefcpair(int ch, int bg);

	void	drawframe();				// �ե졼���ɽ������
	virtual int	drawwin() = 0;			// ��Ȥ�ɽ�����벾�۴ؿ���������ǻȤ���

	void	splitwin(int y);			// ������ɥ���岼��ʬ�䤹��
	void	setmessage(int x, int y, CString str);	// ��å�������ɽ������
	void	setmessage(int x, int y, CString str, int cpair);
	void	setmessage(int x, int y, CString str, int ch, int bg);
	int	setmessage_n(int x, int y, CString str);// ��å�������ɽ������ʼ�ư���ԡ�
	int	setmessage_n(int x, int y, CString str, int cpair);
	int	setmessage_n(int x, int y, CString str, int ch, int bg);
	void	seticon(Pos pos, Pos* cur, Pos* dpos, std::vector<CString> list, std::vector<int> cpair, int col);
							// �ޥȥꥯ����ɽ������
	void	setselect(int x, int y, int* posx, int* dposx, std::vector<CString> list, std::vector<int> cpair);
							// ���쥯�ȥ��֤�ɽ������
	void	setlist(int x, int y, int* dposx, int* posy, int* dposy, std::vector<CString> list, std::vector<int> cpair);
							// �ꥹ�Ȥ�ɽ������
	void	setedit(int x, int y, int* posy, int* dposy, std::vector<CString> name, std::vector<CString> value, std::vector<int> cpair);
							// �ꥹ�Ȥ�ɽ������
	void	wclrtorborder();			// 1�ԥ��ꥢ
	void	clearwin();				// ������ɥ������������ꥢ�ʷ����ϻĤ���
	bool	mvwaddstrtoeol(int x, int y, const CString str);
							// �����ޤ�ɽ��

	void	chg_attr(int x, int y, long attr);				// °�������ѹ�
	void	chg_color(int x, int y, int cpair);				// �������ѹ�
	void	chg_color(int x, int y, int ch, int bg);			// �������ѹ�
	void	chg_attr_color(int x, int y, long attr, int cpair);		// ����°�����ѹ�
	void	chg_attr_color(int x, int y, long attr, int ch, int bg);	// ����°�����ѹ�

	virtual void	keyloop();			// �������ϥ롼��
	virtual bool	onkeypress_left();		// �����������ʲ��۴ؿ���
	virtual bool	onkeypress_down();		// �����������ʲ��۴ؿ���
	virtual bool	onkeypress_up();		// �奭�������ʲ��۴ؿ���
	virtual bool	onkeypress_right();		// �����������ʲ��۴ؿ���
	virtual bool	onkeypress_ok();		// �ϣ˥��������ʲ��۴ؿ���
	virtual bool	onkeypress_cancel();		// ����󥻥륭�������ʲ��۴ؿ���


	int	m_winx;			// ɽ�����ֺ�
	int	m_winy;			// ɽ�����־�
	int	m_winw;			// ��
	int	m_winh;			// �⤵

	int	m_return;		// startwin���֤���
	CString	m_returnstr;		// startdialog���֤���

	int	m_colors[COLOR_NUM];	// ���顼�ơ��֥�
	int	m_cpair;		// �ǥե���ȥ��顼�ڥ�
	long	m_attrs[ATTR_NUM];	// °���ơ��֥�

	WINDOW*	m_this;			// ��ʬ���ȤΥ�����ɥ��ϥ�ɥ�


	void signal_handler(int sig);

protected:
	int	adjx(int x);		// ����X��ɸ��ºݤκ�ɸ���Ѵ�����
	int	xyton(int x, int y);	// �󼡸��κ�ɸ��켡�����������Ǥ��Ѵ�����

	CString	m_title;		// ������ɥ������ȥ�

private:

};
#endif // CWINDOWS_H
