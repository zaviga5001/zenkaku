#ifndef CWINMAPEDITOR_H
#define CWINMAPEDITOR_H
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


class CWinMapEditor : public CWindows
{
public:
	CWinMapEditor(CData* data, CConfig* config, CFile* file);
	virtual ~CWinMapEditor();

	virtual int	drawwin();
	void		refreshwin();
	void		refreshpos(int x, int y);
	int		gettile(int x, int y);

	void		keyloop();		// キー入力ループ
	bool		onkeypress_left();	// 左キー押下
	bool		onkeypress_down();	// 下キー押下
	bool		onkeypress_up();	// 上キー押下
	bool		onkeypress_right();	// 右キー押下

	// マップデータ
	Pos		m_dpos;			// パッド上の表示領域左上
	Pos		m_cur;			// カーソル位置
	std::string	m_path;			// ファイル名
	MapData		m_mapdata;		// マップに付随するデータ
	PosData*	m_posdata;		// ポジションに付随するデータ
	PosData		m_spposdata[MAX_SPPOS];	// スペシャルポジションに付随するデータ
	TileData	m_tiledata[MAX_TILE];	// タイルに付随するデータ
	int		m_tilenum;		// タイルの種類
	PosEvent	m_pevent[MAX_MAPEVENT];	// ポイントイベントデータベース
	PosEvent	m_sevent[MAX_MAPEVENT];	// ストップイベントデータベース
	std::string	m_fieldname[MAX_FNAME];	// 地名

	PosData		m_posbuf;		// ポジションデータコピー用バッファ
	PosData		m_posundobuf;		// ポジションデータUNDO用バッファ
	PosData		m_posmsk;		// ポジションデータコピー用マスク

	CConfig*	m_config;		// コンフィグ
	CData*		m_data;			// データ
	CFile*		m_file;			// ファイルハンドラ

protected:
	void		warn_no_map();		// マップが読み込まれていない警告

	int	xyton(int x, int y);	// 二次元の座標を一次元の配列要素に変換する

private:
};

#endif // CWINMAPEDITOR_H
