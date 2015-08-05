#include "win.h"

CWinScenarioEditor::CWinScenarioEditor(CConfig* config)
{
	// �ʲ��ϥǥե�����ͤǤ���
	// ���֥������Ⱥ������Ĵ�����Ƥ���������
	m_winx   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winy   = 0;		// ���ɽ�����ϰ��֡ʾ��0��
	m_winw   = COLS / 2;	// ����������Ѥǥ�����ȡ�
	m_winh   = LINES;	// ��ι⤵

	m_data = new CData;
}

CWinScenarioEditor::~CWinScenarioEditor()
{
	if (m_data != NULL)	delete(m_data);
}

int CWinScenarioEditor::drawwin()
{
	// ���̺�����
	wrefresh(m_this);
	return true;
}


void CWinScenarioEditor::keyloop()
{
	timeout(-1);    // �������Ϥ��Ԥ�

	CWinMsg*		nw_msg;
	CWinGetPath*		nw_getpath;
	CFile*			mycharfp;

	for( ; ; )
	{
		int ch = wgetch(m_this);
		switch(ch)
		{
			case MYKEY_LEFT:
				if (!onkeypress_left())		return;
				break;
			case MYKEY_DOWN:
				if (!onkeypress_down())		return;
				break;
			case MYKEY_UP:
				if (!onkeypress_up())		return;
				break;
			case MYKEY_RIGHT:
				if (!onkeypress_right())	return;
				break;
			case 'z':
				return;
				break;
			default:
				continue;
				break;
		}
	}
}

// �ޥ������ե����뤫���ɤ߹���
int CWinScenarioEditor::read_mychar()
{
	CFile*	mycharfp;
	mycharfp = new CFile;

//	for (int i = 1; ; i++)
//	{
//		char	tmp_str[10];
//		sprintf(tmp_str, "%d", i);
//		m_path = "mychar/" + tmp_str + ".bin";
//	}

	delete(mycharfp);

	return 0;
}

void CWinScenarioEditor::warn(enum msg_id tmp_msg)
{
	CWinMsg*	nw_msg;
	nw_msg = new CWinMsg;
	nw_msg->m_msg = msg[tmp_msg].msg;
	nw_msg->setdefcpair(1, 0);
	nw_msg->startwin(true);
	delete(nw_msg);
	drawwin();
}

bool CWinScenarioEditor::onkeypress_left()
{
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinScenarioEditor::onkeypress_down()
{
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinScenarioEditor::onkeypress_up()
{
	drawwin();
	return true;	// �����롼�׷�³
}
bool CWinScenarioEditor::onkeypress_right()
{
	drawwin();
	return true;	// �����롼�׷�³
}



