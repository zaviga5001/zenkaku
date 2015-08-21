#ifndef	MY_MSG_H
#define	MY_MSG_H


enum msg_id {
	MY_MSG_WIN_TATE,
	MY_MSG_WIN_YOKO,
	MY_MSG_WIN_7,
	MY_MSG_WIN_9,
	MY_MSG_WIN_1,
	MY_MSG_WIN_3,
	MY_MSG_WIN_8,
	MY_MSG_WIN_4,
	MY_MSG_WIN_6,
	MY_MSG_WIN_2,
	MY_MSG_WIN_5,
	MY_MSG_SYS_YES,
	MY_MSG_SYS_NO,
	MY_MSG_SYS_OK,
	MY_MSG_SYS_CANSEL,
	MY_MSG_SYS_SEL_SCENARIO,
	MY_MSG_SYS_INP_PATH,
	MY_MSG_SYS_INP_MAPNO,
	MY_MSG_SYS_INP_SPOS,
	MY_MSG_SYS_SAVE_YN,
	MY_MSG_SYS_NO_MAP,
	MY_MSG_SYS_ADD_TILE,

	MY_MSG_DUMMY
};

typedef	struct {
	char*	tile;
	char*	msg;
} MsgData;

static MsgData	msg[MY_MSG_DUMMY + 1] = {
	#include	"msg.utf8"
};


#endif  // MY_MSG_H
