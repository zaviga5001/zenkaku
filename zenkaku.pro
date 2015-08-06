TEMPLATE	= app
CONFIG		= qt warn_on release
HEADERS		= CDate.h \
		  CHashTable.h \
		  CString.h \
		  Config.h \
		  Data.h \
		  File.h \
		  Game.h \
		  Hash.h \
		  Title.h \
		  WinEditValue.h \
		  WinEditValue_Cmask.h \
		  WinEditValue_Event.h \
		  WinEditValue_Flg.h \
		  WinEditValue_Pos.h \
		  WinEditValue_Tile.h \
		  WinEnemyEditor.h \
		  WinEventEditor.h \
		  WinGetPath.h \
		  WinItemEditor.h \
		  WinMapEditor.h \
		  WinMessageEditor.h \
		  WinMsg.h \
		  WinMycharEditor.h \
		  WinPGEditor.h \
		  WinPartyEditor.h \
		  WinScenarioEditor.h \
		  WinSelect1Icon.h \
		  WinSelect1Item.h \
		  WinSelect1Line.h \
		  WinShopEditor.h \
		  WinTitle.h \
		  Windows.h \
		  common.h \
		  main.h \
		  msg.h \
		  win.h
SOURCES		= CDate.cpp \
		  CString.cpp \
		  CString_st.cpp \
		  CString_stin.cpp \
		  Config.cpp \
		  Data.cpp \
		  File.cpp \
		  Game.cpp \
		  Hash.cpp \
		  Title.cpp \
		  WinEditValue.cpp \
		  WinEditValue_Cmask.cpp \
		  WinEditValue_Event.cpp \
		  WinEditValue_Flg.cpp \
		  WinEditValue_Pos.cpp \
		  WinEditValue_Tile.cpp \
		  WinEnemyEditor.cpp \
		  WinEventEditor.cpp \
		  WinGetPath.cpp \
		  WinItemEditor.cpp \
		  WinMapEditor.cpp \
		  WinMessageEditor.cpp \
		  WinMsg.cpp \
		  WinMycharEditor.cpp \
		  WinPGEditor.cpp \
		  WinPartyEditor.cpp \
		  WinScenarioEditor.cpp \
		  WinSelect1Icon.cpp \
		  WinSelect1Item.cpp \
		  WinSelect1Line.cpp \
		  WinShopEditor.cpp \
		  WinTitle.cpp \
		  Windows.cpp \
		  main.cpp
INTERFACES	= 
DESTDIR = ./
INCLUDEPATH += /usr/local/zgcc34/include include
DEPENDPATH += /usr/local/zgcc34/lib
TARGET = zenkaku
LIBS += -Llib -lncursesj
