#ifndef MY_COMMON_H
#define MY_COMMON_H

/****************************************/
/* �ǥХå��ե饰			*/
/****************************************/
#define	DEBUG

#include	<vector>
#include	"CString.h"

/****************************************/
/* ���					*/
/****************************************/
#define		FLG_BITS	128	// *32 bits�ĤΥե饰�򰷤���

#define		MAX_MYCHAR	8	// ��������Υޥ�������
#define		MAX_PARTY	8	// Ʊ���˥ѡ��ƥ��˲ä��ޥ�������
#define		MAX_ITEM	128	// �����ƥ�ν����¡ʰ�͡�
#define		MAX_SITEM	16	// ���ڥ���륢���ƥ�ν�����
#define		MAX_STOCK	99	// ���ĤΥ����ƥ�ν�����
#define		MAX_FIGHT	8	// °�������μ���
#define		MAX_MAGIC	8	// ��ˡ�μ���
#define		MAX_SKILL	8	// ������μ���
#define		MAX_TYPE	8	// °���μ���
#define		MAX_EQUIP	3	// �����Ǥ��������ʤο�
#define		ENEMY_ITEM	5	// Ũ����餬������Ƥ��륢���ƥ�μ���
#define		ENEMY_FIGHT	10	// Ũ�����ι������
#define		ENEMY_CALL	5	// Ũ����餬�Ƥ���֤μ���
#define		MAX_ENEMY	16	// ���ĤΥѡ��ƥ���κ���Ũ������
//#define		MAX_ENEMYCACHE	16	// ���٤��ɤ߹�������Ũ������
#define		MAX_ENEMYCACHE	1024	// ���٤��ɤ߹�������Ũ������
#define		MAX_ENEMYNAME	40	// Ũ������̾����Ĺ��
#define		MAX_ENEMYPROF	256	// Ũ�����Υץ�ե������Ĺ��
#define		EVENT_ELM	5	// ���٥������
#define		ITEM_ELM	5	// �����ƥ�����

extern CString	zenkaku_home;
extern CString	user_home;

/****************************************/
/* �����ʷ�����ʤ�			*/
/****************************************/

enum e_race {
		R_HUMAN,	// �ʹ�
		R_ELF,		// �����
		R_HALFELF,	// �ϡ��ե����
		R_DWARF,	// �ɥ��
		R_HOBIT,	// �ۥӥå�
		R_OAK,		// ������
		R_TOROL,	// �ȥ��
		R_NORM,		// �Ρ���
		R_DRAGON,	// �ɥ饴��
		R_ROBOT,	// ����
		R_FAIRY,	// ����
		R_RACEETC	// ����¾
};

enum e_job {
		J_FIGHTER,	// ���
		J_KNIGHT,	// ���� 
		J_SAMURAI,	// ��
		J_ARCHER,	// �������㡼
		J_MAIGCKNIGHT,	// ��ˡ���
		J_MAGE,		// ��Ƴ��
		J_SORSARAR,	// ���ѻ�
		J_WIZARD,	// ��ˡ�Ȥ�
		J_PRIEST,	// ��η
		J_SUMMONER,	// ������
		J_HERAR,	// �ҡ��顼
		J_MONK,		// ���
		J_NINJA,	// Ǧ��
		J_THIEF,	// ��±
		J_DANCER,	// �٤��
		J_COOK		// Ĵ����
};

enum e_type {
		T_FIRE	= 0x01,	// ��
		T_WATER	= 0x02,	// ��
		T_WIND	= 0x04,	// ��
		T_EARTH	= 0x08,	// ��
		T_RAY	= 0x10,	// ��
		T_DARK	= 0x20,	// ��
		T_TIME	= 0x40,	// ��
		T_SPACE	= 0x80	// ��
};

enum e_gender {
		G_MAIL,		// ��
		G_FEMAIL,	// ��
		G_UNK		// ����
};

enum e_command {
		C_FIGHT,	// Ʈ��
		C_USEMAGIC,	// ��ˡ
		C_USEITEM,	// �����ƥ�
		C_DEFFENCE,	// ���
		C_EQUIP,	// ����
		C_ESCAPE,	// ƨ����
		C_SAME		// �����Ʊ��
};

enum e_weapon {
		W_SWORD,	// ���ʲС�
		W_SPIER,	// ��ʿ��
		W_DAGGER,	// û��������
		W_HAMMER,	// �������ڡ�
		W_ARROW,	// ����ʸ���
		W_AXE,		// ��ʰǡ�
		W_ROD,		// ��ʻ���
		W_WIP		// �ܡʶ���
};

enum e_status {
		ST_NORMAL	= 0x0000,	// ����
		ST_POISON	= 0x0001,	// ��   ��°���Ϥ�����ʤ�
		ST_FREEZE	= 0x0002,	// ��� ��°���Ϥ�����ʤ�
		ST_SLEEP	= 0x0004,	// ̲��
		ST_BLIND	= 0x0008,	// ���� ��°���Ϥ�����ʤ�
		ST_SLOW		= 0x0010,	// �٤� ��°���Ϥ�����ʤ�
		ST_FORGET	= 0x0020,	// ˺��
		ST_CONFUSE	= 0x0040,	// ����
		ST_STONE	= 0x0080,	// �в� ��°���Ϥ�����ʤ�
		ST_STUN		= 0x0100,	// ����
		ST_DEAD		= 0x0200	// ��
};

enum e_skill {
		T_ROGUE		= 0x00,	// ��±
		T_HEARL		= 0x01,	// Ĵ��
		T_THRROW	= 0x02,	// �ꤲ��
		T_SWIM		= 0x04,	// �ˤ�
		T_COOK		= 0x08,	// ����
		T_DANCE		= 0x10,	// ����
		T_LUCK		= 0x20,	// ��
		T_DUMMY		= 0x40	// ͽ��
};

enum e_event {
	EV_FLG,			// �ե饰������
	EV_COUNTER,		// �����󥿡�������
	EV_MESS,		// ��å�����ɽ��
	EV_BATTLE,		// ��Ʈ����
	EV_CURPOS,		// �����Ϥ򵭲����᤹
	EV_LOADPOS,		// �ޥå��ɤ߹���
	EV_MOVE,		// ��ư����
	EV_KEY,			// �������Ϥ򥷥ߥ�졼��
	EV_WINDOW,		// ������ɥ��򳫤����Ĥ���
	EV_MEMBER,		// ���С����ɲá�Υæ����
	EV_DRAWMEMBER,		// ���С��Υ���ܥ��ɽ������
	EV_DRAWCHAR,		// ����¾��ʸ������ܥ��ɽ������
	EV_ITEM,		// �����ƥ����������
	EV_STATUS,		// ���ơ�����������
	EV_MAGIC,		// ��ˡ��ȯư����
	EV_DISPLAY,		// ���̸���
	EV_NONE,		// ���⤷�ʤ�
	EV_GAMEOVER,		// �����˥����४���С������������
	EV_ENDING		// ����ǥ��󥰳���
};

enum e_item {
	IT_FOOD,		// ����
	IT_DRUG,		// ��
	IT_WEAPON,		// ���
	IT_SHIELD,		// ��
	IT_HELM,		// ��
	IT_ARMOR,		// �ɶ�
	IT_MANT,		// �ޥ��
	IT_BOOTS,		// ��
	IT_EQUIP,		// ������
	IT_RIDE,		// ���ʪ
	IT_BOOK,		// ��
	IT_THROW,		// �ꤲ��ʪ
	IT_ETC			// ����¾
};

enum e_shop {
	SH_INN,
	SH_ITEM,
	SH_CHURCH,
	SH_EXPORT
};

enum e_dir {
	WEST,
	SOUTH,
	NORTH,
	EAST
};


/*************************************************************/
typedef struct typePos{		// ����饯���ΰ���
	int	x;		// �ޥå׾��X��ɸ
	int	y;		// �ޥå׾��Y��ɸ
} Pos;

typedef struct typePos3{	// ����饯���ΰ���(������)
	int	x;		// �ޥå׾��X��ɸ
	int	y;		// �ޥå׾��Y��ɸ
	char	h;		// �ޥå׾�ι⤵
} Pos3;

typedef struct typeScnData{	// ���ʥꥪ���տ魯��ǡ���
	int	id;			// ���ʥꥪID�ʥ��󥹥ȡ��뤹����֤ˤ�ä��Ѥ���
	CString path;			// ���ʥꥪ�ǥ��쥯�ȥ�̾�ʥ��󥹥ȡ��������Ƿ�ޤ��
	CString mychar[MAX_MYCHAR];	// �ޥ������ե�����̾
} ScnData;

typedef struct typeScnList{	// ���ʥꥪ�ꥹ���ѥǡ���
	int	id;			// ���ʥꥪID�ʥ��󥹥ȡ��뤹����֤ˤ�ä��Ѥ���
	CString name;			// ���ʥꥪ̾
	CString doc;			// ���ʥꥪ����
} ScnList;

typedef struct typeMyCharValue{	// �ޥ��������ͷ�
	int	p;		// ���ߤ���
	int	t;		// ���Ū�˾徺����������
	int	m;		// ������
} MyCharValue;

typedef struct typeMyChar{	// �ޥ��������տ魯��ǡ���
	int		id;			// ���ߥץ쥤��Υ��ʥꥪID
	enum e_race	race;			// ��²
	enum e_job	job;			// ����
	enum e_gender	gender;			// ����
	CString		name;			// ̾��
	char		tile[2];		// ʸ��
	char		ch;			// ʸ����
	char		bg;			// �طʿ�

	BYTE		type;			// °��
	enum e_status	status;			// ���ơ�����
	unsigned char	level;			// ��٥�
	unsigned int	exp;			// �и���

	MyCharValue	hp;			// ����
	MyCharValue	sp;			// ������ݥ����
	MyCharValue	ap;			// ������
	MyCharValue	gp;			// �ɸ���
	MyCharValue	mp;			// ��ˡ��
	MyCharValue	ep;			// ������
	MyCharValue	fp;			// ���ᤵ
	MyCharValue	dp;			// ���Ѥ�
	unsigned short	rweapon;		// �������
	unsigned short	lweapon;		// �������
	unsigned short	helm;			// Ƭ�ɶ�
	unsigned short	armor;			// ���ɶ�
	unsigned short	mant;			// ���ɶ�
	unsigned short	boots;			// ­�ɶ�
	unsigned short	equip[MAX_EQUIP];	// ������
	BYTE		food;			// ��ʢ��

	BYTE		magic[MAX_TYPE][MAX_MAGIC];	// ��ˡ��٥�
	BYTE		magicexp[MAX_TYPE][MAX_MAGIC];	// ��ˡ�и���
	BYTE		fight[MAX_TYPE][MAX_FIGHT];	// °��������٥�
	BYTE		fightexp[MAX_TYPE][MAX_FIGHT];	// °�������и���
	BYTE		skill[MAX_TYPE][MAX_SKILL];	// �������٥�
	BYTE		skillexp[MAX_TYPE][MAX_SKILL];	// ������и���
	BYTE		curse[MAX_TYPE];		// ������°�����

	CString		prof;			// �ץ�ե�����
} MyChar;

typedef struct typeItemNum{	// ��������ƥ෿
	unsigned short	id;		// �����ƥ�ID
	char		num;		// �����
} ItemNum;

typedef struct typeMyParty{	// �ѡ��ƥ����տ魯��ǡ���
	char		mychar[MAX_PARTY];	// �ѡ��ƥ����С�
	char		map;			// �ޥå��ֹ�
	Pos3		pos;			// ������
	ItemNum		item[MAX_ITEM];		// ��������ƥ�
	ItemNum		spitem[MAX_SITEM];	// ������ڥ���륢���ƥ�
	unsigned int	gold;			// �����
	char		status;			// ���ơ������ʾ��ʪ�˾�äƤ���ʤɡ�
} MyParty;

typedef struct typeMapData{	// �ޥåפ��տ魯��ǡ���
	int	width;		// ����
	int	height;		// ����
	char	nextmap_u;	// ���ޥåסʾ��
	char	nextmap_d;	// ���ޥåסʲ���
	char	nextmap_l;	// ���ޥåסʺ���
	char	nextmap_r;	// ���ޥåסʱ���

} MapData;

typedef struct typePosData{	// �ݥ��������տ魯��ǡ���
	int	flg;		// �ե饰
	int	falseid;	// ������ID���⤷���ϻ��ȥ��ڥ����ݥ������
	int	trueid;		// ������ID���⤷���ϻ��ȥ��ڥ����ݥ������
	int	enemy;		// �и�Ũ
	char	encount;	// ���󥫥����Ψ(0-100%)
	char	name;		// ��̾ID
} PosData;
// [x][y]      �ޥåץ�����ꥢ
// [MAX_SPPOS] ���ڥ����ݥ������

typedef struct typeTileData{	// ��������տ魯��ǡ���
	char	tile[2];	// ʸ��
	char	ch;		// ʸ����
	char	bg;		// �طʿ�
	char	attr;		// °��
	char	height;		// �⤵
	char	move;		// ��ư°��
} TileData;
// [MAX_TILE] ������ꥢ

typedef struct typePosEvent{	// �ݥ�����󥤥٥�ȥǡ���
	int	flg;		// ȯ����ǧ�ե饰�ֹ�
	bool	torf;		// ȯ����ǧ�ե饰Bit
	int	x;		// ȯ�����X
	int	y;		// ȯ�����Y
	char	h;		// ȯ���⤵
	int	event;		// ȯ�����٥���ֹ�
} PosEvent;
// [MAX_MAPEVENT] ������ꥢ

typedef struct typeEnemyValue{	// Ũ�������ͷ�
	int	p;		// ���ߤ���
	int	m;		// ������
} EnemyValue;

typedef struct typeEnemy{	// Ũ�������տ魯��ǡ���
	CString		name;			// ̾��
	BYTE		type;			// °��
	enum e_status	status;			// ���ơ�����

	EnemyValue	hp;			// ����
	EnemyValue	ap;			// ������
	EnemyValue	gp;			// �ɸ���
	EnemyValue	mp;			// ��ˡ��
	EnemyValue	ep;			// ������
	EnemyValue	fp;			// ���ᤵ

	unsigned int	exp;			// ����и���
	unsigned int	gold;			// �����
	ItemNum		item[ENEMY_ITEM];	// ��������ƥ�
	char		item_r[ENEMY_ITEM];	// �����Ψ
	unsigned short	fight[ENEMY_FIGHT];	// ������ˡ
	char		fight_r[ENEMY_FIGHT];	// �����Ψ

	int		flg;			// �ݤ��줿��Ω�Ƥ�ե饰�ֹ�
	int		next_enemy;		// �ݤ��줿���������ɤ߹���ŨID
	int		call_enemy[ENEMY_CALL];	// �Ƥ�ŨID

	CString		prof;			// �ץ�ե�����
} Enemy;

typedef struct typeEnemyParty{	// Ũ�ѡ��ƥ����տ魯��ǡ���
	int		enemy[MAX_ENEMY];	// �ѡ��ƥ����С�
	ItemNum		item[ENEMY_ITEM];	// ��������ƥ�ʥѡ��ƥ���ͭ��
	char		item_r[ENEMY_ITEM];	// �����Ψ�ʥѡ��ƥ���ͭ��
	int		flg;			// �ݤ��줿��Ω�Ƥ�ե饰�ֹ�
} EnemyParty;

typedef struct typeEnemyPGValue{	// Ũ�ѡ��ƥ������ͷ�
	int		party;		// �ѡ��ƥ�
	char		party_r;	// �и���Ψ
} EnemyPGValue;

typedef struct typeEnemyPG{	// Ũ�ѡ��ƥ������տ魯��ǡ���
	std::vector<EnemyPGValue>	elm;	// �ѡ��ƥ�
} EnemyPG;

typedef struct typeEventData{	// ���٥�ȥǡ���
	e_event		action;			// ư��
	int		elm[EVENT_ELM];		// ���ơ�ư��ˤ�äƳ�Ǽ�����ͤΰ�̣�ϰ㤦��
	int		flg;			// ư����Ƚ�ꤹ��ե饰�ֹ�
	int		falseid;		// False�λ����ܤ��륤�٥��
	int		trueid;			// True�λ����ܤ��륤�٥��
} EventData;

typedef struct typeItemData{	// �����ƥ�ǡ���
	CString		name;			// ̾��
	e_item		type;			// ����
	int		price;			// ����
	int		elm[ITEM_ELM];		// ���ơʼ���ˤ�äƳ�Ǽ�����ͤΰ�̣�ϰ㤦��
} ItemData;

typedef struct typeShopValue{	// ����åפ��ͷ�
	int		item;			// ���ʡʥ����ƥ�ID��
	int		stock;			// �߸˿�
	int		spprice;		// ���ڥ����ץ饤��
} ShopValue;

typedef struct typeShopData{	// ����åץǡ���
	CString		name;			// ̾��
	e_shop		type;			// ����
	std::vector<ShopValue>	elm;		// ����
} ShopData;

typedef struct typeMessData{	// ��å������ǡ���
	CString		msg;			// ��å�����
} MessData;







#endif	// MY_COMMON_H

