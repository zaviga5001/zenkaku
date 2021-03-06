#ifndef CWINENEMYEDITOR_H
#define CWINENEMYEDITOR_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <vector>
#include <string>
#include <ncurses.h>
#include "Windows.h"
#include "Config.h"
#include "Data.h"
#include "File.h"



class CWinEnemyEditor : public CWindows
{
public:
	CWinEnemyEditor(CData* data, CConfig* config, CFile* file);
	virtual ~CWinEnemyEditor();

	virtual int	drawwin();
	void		push(const std::string str, const int id);
	void		push(const std::string str, const int id, const int cpair);
	void		change(const std::string str, const int id, const int index);
	void		read_item_list();	// アイテム一括読み込み
	void		read_enemy_list();	// 敵キャラ一括読み込み
	void		read_enemy(int index);	// 敵キャラ読み込み
	void		write_enemy(int index);	// 敵キャラ書き込み
	void		read_type_list();	// 属性リスト作成
	void		read_fight_list();	// 攻撃方法リスト作成

	Pos		m_wpos;			// ウィンドウ上の表示位置

	void		keyloop();		// キー入力ループ
	bool		onkeypress_left();	// 左キー押下
	bool		onkeypress_down();	// 下キー押下
	bool		onkeypress_up();	// 上キー押下
	bool		onkeypress_right();	// 右キー押下
	virtual bool	onkeypress_ok();	// ＯＫキー押下
	virtual bool	onkeypress_cancel();	// キャンセルキー押下

	CConfig*	m_config;		// コンフィグ
	CData*		m_data;			// データ
	CFile*		m_file;			// ファイルハンドラ

	int		m_enemynum;		// 読み込んだ敵キャラ数
	int		m_itemnum;		// 読み込んだアイテム数
	int		m_typenum;		// 属性数
	int		m_fightnum;		// 攻撃方法数

protected:
	std::vector<std::string>	m_list;		// 要素
	std::vector<int>		m_cp;		// 色
	std::vector<int>		m_index;	// 値
	int	m_maxwidth;		// リスト文字列の最大幅
	Pos	m_cur;			// カーソルの位置
	Pos	m_dpos;			// リストの表示開始位置（横長対応）
	std::vector<std::string>	m_enemylist;	// 敵キャラ名リスト
	std::vector<std::string>	m_itemlist;	// アイテム名リスト
	std::vector<std::string>	m_typelist;	// 属性リスト
	std::vector<std::string>	m_fightlist;	// 攻撃方法リスト

private:
};

#endif // CWINENEMYEDITOR_H
