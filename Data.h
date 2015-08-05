#ifndef CDATA_H
#define CDATA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include "include/curses.h"
#include "common.h"

#define	FLG_NUM_BY_INT	512


class CData
{
public:
	CData();
	virtual ~CData();

	int		get_flg(int num);
	void		set_flg(int num, bool flg);

	int		m_flg[FLG_NUM_BY_INT];		// �ե饰
	
	ScnData		m_scn;				// ���ʥꥪ�ǡ���
	MyChar		m_mychar[MAX_MYCHAR];		// �ޥ�����鹽¤��
	char		m_mycharnum;			// ���ʥꥪ��ͭ���ʥޥ������ο�
	MyParty		m_myparty;			// �ޥ��ѡ��ƥ���¤��

	Enemy		m_enemy[MAX_ENEMYCACHE];	// Ũ����鹽¤��
	char		m_enemynum;			// ���ѡ��ƥ���Ũ�����ο�
	EnemyParty	m_enemyparty;			// Ũ�ѡ��ƥ���¤��
	ShopData	m_shop;				// ����å׹�¤��

	std::vector<EnemyPG>	m_enemypg;		// Ũ�ѡ��ƥ�����¤��
	std::vector<EventData>	m_event;		// ���٥�ȹ�¤��
	std::vector<ItemData>	m_item;			// �����ƥ๽¤��
	std::vector<MessData>	m_mess;			// ��å�������¤��

	int			m_enemypgnum;		// Ũ�ѡ��ƥ���¤�Το�
	int			m_eventnum;		// ���٥�ȹ�¤�Το�
	int			m_itemnum;		// �����ƥ๽¤�Το�
	int			m_messnum;		// ��å�������¤�Το�

protected:

private:

};
#endif // CDATA_H
