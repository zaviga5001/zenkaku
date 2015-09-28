#include "Editor.h"

CEditor::CEditor(CData* data, CConfig* config, CFile* file)
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

CEditor::~CEditor()
{
}

// メインループ
//
// 返り値
// true:ループ続行
// false:終了
//
bool CEditor::main()
{
	switch(m_data->m_scn_index)
	{
		case 0:
			CWinMapEditor*	window1;
			window1 = new CWinMapEditor(m_data, m_config, m_file);
			window1->startwin(true);
			delete(window1);
			refresh();
			break;
		case 1:
			CWinEventEditor*	window2;
			window2 = new CWinEventEditor(m_data, m_config, m_file);
			window2->startwin(true);
			delete(window2);
			refresh();
			break;
		case 2:
			CWinMycharEditor*	window3;
			window3 = new CWinMycharEditor(m_data, m_config, m_file);
			window3->startwin(true);
			delete(window3);
			refresh();
			break;
		case 3:
			CWinEnemyEditor*	window4;
			window4 = new CWinEnemyEditor(m_data, m_config, m_file);
			window4->startwin(true);
			delete(window4);
			refresh();
			break;
		case 4:
			CWinPartyEditor*	window5;
			window5 = new CWinPartyEditor(m_data, m_config, m_file);
			window5->startwin(true);
			delete(window5);
			refresh();
			break;
		case 5:
			CWinPGEditor*	window6;
			window6 = new CWinPGEditor(m_data, m_config, m_file);
			window6->startwin(true);
			delete(window6);
			refresh();
			break;
		case 6:
			CWinItemEditor*	window7;
			window7 = new CWinItemEditor(m_data, m_config, m_file);
			window7->startwin(true);
			delete(window7);
			refresh();
			break;
		case 7:
			CWinMessageEditor*	window8;
			window8 = new CWinMessageEditor(m_data, m_config, m_file);
			window8->startwin(true);
			delete(window8);
			refresh();
			break;
		case 8:
			CWinScenarioEditor*	window9;
			window9 = new CWinScenarioEditor(m_data, m_config, m_file);
			window9->startwin(true);
			delete(window9);
			refresh();
			break;
		case 9:
			CWinWeaponEditor*	window10;
			window10 = new CWinWeaponEditor(m_data, m_config, m_file);
			window10->startwin(true);
			delete(window10);
			refresh();
			break;
		case 10:
			CWinArmorEditor*	window11;
			window11 = new CWinArmorEditor(m_data, m_config, m_file);
			window11->startwin(true);
			delete(window11);
			refresh();
			break;
		default:
			break;
	}

	return true;
}





