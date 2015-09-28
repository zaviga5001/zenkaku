#include "Data.h"

CData::CData()
{
	// 乱数の種
	srand(time(NULL));

	// フラグの初期化
	memset(m_flg, 0, 4 * FLG_NUM_BY_INT);
	
	// 今だけ初期化（本当はクラスの外から初期化する）
	m_scn.id   = 1;
	m_scn.path = "qwert123";
	m_scn.mychar[0] = "data/qwert123/asdfg123.dat";

	// 敵パーティ読み込み
	m_enemypgnum = 0;

	// イベント読み込み
	m_eventnum = 0;

	// アイテム読み込み
	m_itemnum = 0;

	// 武器読み込み
	m_weaponnum = 0;

	// 防具読み込み
	m_armornum = 0;

	// ショップ読み込み

	// メッセージ読み込み
	m_messnum = 0;
}

CData::~CData()
{
}

int CData::get_flg(int num)
{
	if (num > 32 * FLG_NUM_BY_INT)	return 99;
	if (num < 1 )			return 99;

	num--;	// 1からの番号を0からに変換

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
		num--;	// 1からの番号を0からに変換

		int sho   = num / 32;
		int amari = num % 32;

		int bit = 1 << amari;

		if (flg)	m_flg[sho] += bit;
		else		m_flg[sho] -= bit;
	}
}



