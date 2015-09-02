#include "Editor.h"

CEditor::CEditor(CConfig* config)
{
	// コンフィグ格納
	m_config = config;
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
	switch(m_config->m_scenario)
	{
		case 1:
			CWinMapEditor*	window1;
			window1 = new CWinMapEditor(m_config);
			window1->startwin(true);
			delete(window1);
			refresh();
			break;
		case 2:
			CWinEventEditor*	window2;
			window2 = new CWinEventEditor(m_config);
			window2->startwin(true);
			delete(window2);
			refresh();
			break;
		case 3:
			CWinMycharEditor*	window3;
			window3 = new CWinMycharEditor(m_config);
			window3->startwin(true);
			delete(window3);
			refresh();
			break;
		case 4:
			CWinEnemyEditor*	window4;
			window4 = new CWinEnemyEditor(m_config);
			window4->startwin(true);
			delete(window4);
			refresh();
			break;
		case 5:
			CWinPartyEditor*	window5;
			window5 = new CWinPartyEditor(m_config);
			window5->startwin(true);
			delete(window5);
			refresh();
			break;
		case 6:
			CWinPGEditor*	window6;
			window6 = new CWinPGEditor(m_config);
			window6->startwin(true);
			delete(window6);
			refresh();
			break;
		case 7:
			CWinItemEditor*	window7;
			window7 = new CWinItemEditor(m_config);
			window7->startwin(true);
			delete(window7);
			refresh();
			break;
		case 8:
			CWinMessageEditor*	window8;
			window8 = new CWinMessageEditor(m_config);
			window8->startwin(true);
			delete(window8);
			refresh();
			break;
		case 9:
			CWinScenarioEditor*	window9;
			window9 = new CWinScenarioEditor(m_config);
			window9->startwin(true);
			delete(window9);
			refresh();
			break;
		default:
			break;
	}

	return true;
}





