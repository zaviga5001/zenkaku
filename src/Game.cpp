#include "Game.h"

CGame::CGame(CData* data, CConfig* config, CFile* file)
{
	// コンフィグ格納
	m_config = config;
	// データ格納
	m_data = data;
	// ファイルハンドラ格納
	m_file = file;

	// 乱数の種
	srand(time(NULL));

}

CGame::~CGame()
{
}


// ゲームをループさせる
// コマンド入力を待つ場合と、イベントで自動で進む場合と
// 二種類を想定
//
// 返り値
// true:ループ続行
// false:ゲーム終了
//
bool CGame::main()
{
	return true;
}





