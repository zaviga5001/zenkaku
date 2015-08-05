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

	int		m_flg[FLG_NUM_BY_INT];		// フラグ
	
	ScnData		m_scn;				// シナリオデータ
	MyChar		m_mychar[MAX_MYCHAR];		// マイキャラ構造体
	char		m_mycharnum;			// シナリオで有効なマイキャラの数
	MyParty		m_myparty;			// マイパーティ構造体

	Enemy		m_enemy[MAX_ENEMYCACHE];	// 敵キャラ構造体
	char		m_enemynum;			// １パーティの敵キャラの数
	EnemyParty	m_enemyparty;			// 敵パーティ構造体
	ShopData	m_shop;				// ショップ構造体

	std::vector<EnemyPG>	m_enemypg;		// 敵パーティ群構造体
	std::vector<EventData>	m_event;		// イベント構造体
	std::vector<ItemData>	m_item;			// アイテム構造体
	std::vector<MessData>	m_mess;			// メッセージ構造体

	int			m_enemypgnum;		// 敵パーティ構造体の数
	int			m_eventnum;		// イベント構造体の数
	int			m_itemnum;		// アイテム構造体の数
	int			m_messnum;		// メッセージ構造体の数

protected:

private:

};
#endif // CDATA_H
