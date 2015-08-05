#include "Data.h"

CData::CData()
{
	// ����μ�
	srand(time(NULL));

	// �ե饰�ν����
	memset(m_flg, 0, 4 * FLG_NUM_BY_INT);
	
	// ������������������ϥ��饹�γ��������������
	m_scn.id   = 1;
	m_scn.path = "qwert123";
	m_scn.mychar[0] = "data/qwert123/asdfg123.dat";

	// Ũ�ѡ��ƥ��ɤ߹���
	m_enemypgnum = 0;

	// ���٥���ɤ߹���
	m_eventnum = 0;

	// �����ƥ��ɤ߹���
	m_itemnum = 0;

	// ����å��ɤ߹���

	// ��å������ɤ߹���
	m_messnum = 0;
}

CData::~CData()
{
}

int CData::get_flg(int num)
{
	if (num > 32 * FLG_NUM_BY_INT)	return 99;
	if (num < 1 )			return 99;

	num--;	// 1������ֹ��0������Ѵ�

	int sho   = num / 32;
	int amari = num % 32;

	int bit = 1 << amari;

	if (m_flg[sho] & bit)	return 1;
	else			return 0;
}

void CData::set_flg(int num, bool flg)
{
	if (num > 32 * FLG_NUM_BY_INT)	return;
	if (num < 1)			return;

	if (flg ^ get_flg(num))
	{
		num--;	// 1������ֹ��0������Ѵ�

		int sho   = num / 32;
		int amari = num % 32;

		int bit = 1 << amari;

		if (flg)	m_flg[sho] += bit;
		else		m_flg[sho] -= bit;
	}
}



