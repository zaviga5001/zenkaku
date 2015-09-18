#ifndef MY_COMMON_H
#define MY_COMMON_H

#include	"MyStr.h"

/****************************************/
/* デバッグフラグ			*/
/****************************************/
#define	DEBUG

#include	<vector>
#include	<string>

/****************************************/
/* 定数					*/
/****************************************/
typedef		unsigned char	BYTE;
#define		FLG_BITS	128	// *32 bits個のフラグを扱える

#define		MAX_MYCHAR	8	// ゲーム内のマイキャラ数
#define		MAX_PARTY	4	// 同時にパーティに加わるマイキャラ数
#define		MAX_ITEM	128	// アイテムの所持上限（一人）
#define		MAX_ITEMCACHE	1024	// 一度に読み込める最大アイテム数
#define		MAX_ITEMNAME	41	// アイテムの名前の長さ
#define		MAX_ITEMPROF	128	// アイテムの説明文の長さ
#define		MAX_SITEM	16	// スペシャルアイテムの所持上限
#define		MAX_STOCK	99	// １つのアイテムの所持上限
#define		MAX_TYPE	8	// 属性の種類
#define		MAX_FIGHT	16	// 属性奥義の種類
#define		MAX_MAGIC	16	// 魔法の種類
#define		MAX_SKILL	16	// スキルの種類
#define		MAX_EQUIP	3	// 装備できる装飾品の数
#define		ENEMY_ITEM	5	// 敵キャラが所持しているアイテムの種類
#define		ENEMY_FIGHT	10	// 敵キャラの攻撃手段
#define		ENEMY_CALL	5	// 敵キャラが呼ぶ仲間の種類
#define		MAX_ENEMY	16	// １つのパーティ内の最大敵キャラ数
#define		MAX_ENEMYCACHE	1024	// 一度に読み込める最大敵キャラ数
#define		MAX_ENEMYNAME	81	// 敵キャラの名前の長さ
#define		MAX_ENEMYPROF	512	// 敵キャラのプロフィールの長さ
#define		EVENT_ELM	5	// イベント内容
#define		ITEM_ELM	5	// アイテム内容
#define		MAX_SPPOS	256	// スペシャルポジションの最大数
#define		MAX_TILE	256	// 読み込めるタイルの最大数
#define		MAX_MAPEVENT	128	// マップイベントの最大数
#define		MAX_FNAME	64	// 地名の最大数
#define		MAX_INTNUM	36	// INT入力時の桁数：12桁（1文字3byteで計算）


#define	ZENKAKURC	"/.zenkaku/zenkakurc"

extern std::string	zenkaku_home;
extern std::string	user_home;

/****************************************/
/* 色々な型宣言など			*/
/****************************************/

enum e_race {
		R_HUMAN,	// 人間
		R_ELF,		// エルフ
		R_HALFELF,	// ハーフエルフ
		R_DWARF,	// ドワーフ
		R_HOBIT,	// ホビット
		R_OAK,		// オーク
		R_TOROL,	// トロル
		R_NORM,		// ノーム
		R_DRAGON,	// ドラゴン
		R_ROBOT,	// 機械
		R_FAIRY,	// 妖精
		R_RACEETC	// その他
};

enum e_job {
		J_FIGHTER,	// 戦士
		J_KNIGHT,	// 騎士 
		J_SAMURAI,	// 侍
		J_ARCHER,	// アーチャー
		J_MAIGCKNIGHT,	// 魔法戦士
		J_MAGE,		// 魔導士
		J_SORSARAR,	// 呪術師
		J_WIZARD,	// 魔法使い
		J_PRIEST,	// 僧侶
		J_SUMMONER,	// 召喚士
		J_HERAR,	// ヒーラー
		J_MONK,		// モンク
		J_NINJA,	// 忍者
		J_THIEF,	// 盗賊
		J_DANCER,	// 踊り子
		J_COOK		// 調理師
};

enum e_type {
		T_FIRE	= 0x01,	// 火
		T_WATER	= 0x02,	// 水
		T_WIND	= 0x04,	// 風
		T_EARTH	= 0x08,	// 土
		T_RAY	= 0x10,	// 光
		T_DARK	= 0x20,	// 闇
		T_TIME	= 0x40,	// 時
		T_SPACE	= 0x80	// 空
};

enum e_gender {
		G_MAIL,		// 男
		G_FEMAIL,	// 女
		G_UNK		// 不明
};

enum e_command {
		C_FIGHT,	// 闘う
		C_USEMAGIC,	// 魔法
		C_USEITEM,	// アイテム
		C_DEFFENCE,	// 守る
		C_EQUIP,	// 装備
		C_ESCAPE,	// 逃げる
		C_SAME		// 前回と同じ
};

enum e_weapon {
		W_SWORD,	// 剣（火）
		W_SPIER,	// 槍（水）
		W_DAGGER,	// 短剣（風）
		W_HAMMER,	// 棍棒（土）
		W_ARROW,	// 弓矢（光）
		W_AXE,		// 斧（闇）
		W_ROD,		// 杖（時）
		W_WIP		// 鞭（空）
};

enum e_status {
		ST_NORMAL	= 0x0000,	// 普通
		ST_POISON	= 0x0001,	// 毒   土属性はかからない
		ST_FREEZE	= 0x0002,	// 凍結 水属性はかからない
		ST_SLEEP	= 0x0004,	// 眠り
		ST_BLIND	= 0x0008,	// 盲目 闇属性はかからない
		ST_SLOW		= 0x0010,	// 遅い 時属性はかからない
		ST_FORGET	= 0x0020,	// 忘却
		ST_CONFUSE	= 0x0040,	// 混乱
		ST_STONE	= 0x0080,	// 石化 土属性はかからない
		ST_STUN		= 0x0100,	// 気絶
		ST_DEAD		= 0x0200	// 死
};

enum e_skill {
		T_ROGUE		= 0x00,	// 盗賊
		T_HEARL		= 0x01,	// 調合
		T_THRROW	= 0x02,	// 投げる
		T_SWIM		= 0x04,	// 泳ぐ
		T_COOK		= 0x08,	// 料理
		T_DANCE		= 0x10,	// ダンス
		T_LUCK		= 0x20,	// 運
		T_DUMMY		= 0x40	// 予備
};

enum e_event {
	EV_FLG,			// フラグを操作する
	EV_COUNTER,		// カウンターを操作する
	EV_MESS,		// メッセージ表示
	EV_BATTLE,		// 戦闘開始
	EV_CURPOS,		// 現在地を記憶／戻す
	EV_LOADPOS,		// マップ読み込み
	EV_MOVE,		// 移動する
	EV_KEY,			// キー入力をシミュレート
	EV_WINDOW,		// ウィンドゥを開く／閉じる
	EV_MEMBER,		// メンバーを追加／離脱する
	EV_DRAWMEMBER,		// メンバーのシンボルを表示する
	EV_DRAWCHAR,		// その他の文字シンボルを表示する
	EV_ITEM,		// アイテムを増減する
	EV_STATUS,		// ステータスを操作する
	EV_MAGIC,		// 魔法を発動する
	EV_DISPLAY,		// 画面効果
	EV_NONE,		// 何もしない
	EV_GAMEOVER,		// 強引にゲームオーバーを引き起こす
	EV_ENDING		// エンディング開始
};

enum e_item {
	IT_FOOD,		// 食料
	IT_DRUG,		// 薬
	IT_WEAPON,		// 武器
	IT_SHIELD,		// 盾
	IT_HELM,		// 兜
	IT_ARMOR,		// 防具
	IT_MANT,		// マント
	IT_BOOTS,		// 靴
	IT_EQUIP,		// 装飾品
	IT_RIDE,		// 乗り物
	IT_BOOK,		// 本
	IT_THROW,		// 投げる物
	IT_ETC			// その他
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
typedef struct typePos{		// キャラクタの位置
	int	x;		// マップ上のX座標
	int	y;		// マップ上のY座標
} Pos;

typedef struct typePos3{	// キャラクタの位置(三次元)
	int	x;		// マップ上のX座標
	int	y;		// マップ上のY座標
	int	h;		// マップ上の高さ
} Pos3;

typedef struct typeScnData{	// シナリオに付随するデータ
	int	id;			// シナリオID（インストールする順番によって変わる）
	std::string path;		// シナリオディレクトリ名（インストール時乱数で決まる）
	std::string mychar[MAX_MYCHAR];	// マイキャラファイル名
} ScnData;

typedef struct typeScnList{	// シナリオリスト用データ
	int	id;			// シナリオID（インストールする順番によって変わる）
	std::string name;		// シナリオ名
	std::string doc;		// シナリオ概要
} ScnList;

typedef struct typeMyCharValue{	// マイキャラの値型
	int	p;		// 現在の値
	int	t;		// 一時的に上昇した最大値
	int	m;		// 最大値
} MyCharValue;

typedef struct typeMyChar{	// マイキャラに付随するデータ
	int		id;			// 現在プレイ中のシナリオID
	enum e_race	race;			// 種族
	enum e_job	job;			// 職業
	enum e_gender	gender;			// 性別
	std::string	name;			// 名前
	std::string	tile;			// 文字
	int		ch;			// 文字色
	int		bg;			// 背景色

	int		type;			// 属性
	enum e_status	status;			// ステータス
	int		level;			// レベル
	int		exp;			// 経験値

	MyCharValue	hp;			// 体力
	MyCharValue	sp;			// スキルポイント
	MyCharValue	ap;			// 攻撃力
	MyCharValue	gp;			// 防御力
	MyCharValue	mp;			// 魔法力
	MyCharValue	ep;			// 回避力
	MyCharValue	fp;			// 素早さ
	MyCharValue	dp;			// 器用さ
	int		rweapon;		// 右手武器
	int		lweapon;		// 左手武器
	int		helm;			// 頭防具
	int		armor;			// 体防具
	int		mant;			// 体防具
	int		boots;			// 足防具
	int		equip[MAX_EQUIP];	// 装飾品
	int		food;			// 満腹度

	int		magic[MAX_TYPE][MAX_MAGIC];	// 魔法レベル
	int		magicexp[MAX_TYPE][MAX_MAGIC];	// 魔法経験値
	int		fight[MAX_TYPE][MAX_FIGHT];	// 属性奥義レベル
	int		fightexp[MAX_TYPE][MAX_FIGHT];	// 属性奥義経験値
	int		skill[MAX_TYPE][MAX_SKILL];	// スキルレベル
	int		skillexp[MAX_TYPE][MAX_SKILL];	// スキル経験値
	int		curse[MAX_TYPE];		// 呪い（属性毎）

	std::string	prof;			// プロフィール
} MyChar;

typedef struct typeItemNum{	// 所持アイテム型
	int		id;		// アイテムID
	int		num;		// 所持数
} ItemNum;

typedef struct typeMyParty{	// パーティに付随するデータ
	int		mychar[MAX_PARTY];	// パーティメンバー
	int		map;			// マップ番号
	Pos3		pos;			// 現在地
	ItemNum		item[MAX_ITEM];		// 所持アイテム
	ItemNum		spitem[MAX_SITEM];	// 所持スペシャルアイテム
	int		gold;			// 所持金
	int		status;			// ステータス（乗り物に乗っているなど）
} MyParty;

typedef struct typeMapData{	// マップに付随するデータ
	int	width;		// 横幅
	int	height;		// 縦幅
	int	nextmap_u;	// 次マップ（上）
	int	nextmap_d;	// 次マップ（下）
	int	nextmap_l;	// 次マップ（左）
	int	nextmap_r;	// 次マップ（右）

} MapData;

typedef struct typePosData{	// ポジションに付随するデータ
	int	flg;		// フラグ
	int	falseid;	// タイルID、もしくは参照スペシャルポジション
	int	trueid;		// タイルID、もしくは参照スペシャルポジション
	int	enemy;		// 出現敵
	int	encount;	// エンカウント率(0-100%)
	int	name;		// 地名ID
} PosData;
// [x][y]      マップワークエリア
// [MAX_SPPOS] スペシャルポジション

typedef struct typeTileData{	// タイルに付随するデータ
	std::string	tile;	// 文字
	int	ch;		// 文字色
	int	bg;		// 背景色
	int	attr;		// 属性
	int	height;		// 高さ
	int	move;		// 移動属性
} TileData;
// [MAX_TILE] ワークエリア

typedef struct typePosEvent{	// ポジションイベントデータ
	int	flg;		// 発生確認フラグ番号
	bool	torf;		// 発生確認フラグBit
	int	x;		// 発生場所X
	int	y;		// 発生場所Y
	int	h;		// 発生高さ
	int	event;		// 発生イベント番号
} PosEvent;
// [MAX_MAPEVENT] ワークエリア

typedef struct typeEnemyValue{	// 敵キャラの値型
	int	p;		// 現在の値
	int	m;		// 最大値
} EnemyValue;

typedef struct typeEnemyWork{	// 敵キャラデータを読み込むワーク
	std::string	name;			// 名前
	int		type;			// 属性
	enum e_status	status;			// ステータス

	EnemyValue	hp;			// 体力
	EnemyValue	ap;			// 攻撃力
	EnemyValue	ag;			// 防御力
	EnemyValue	mp;			// 魔法力
	EnemyValue	mg;			// 魔法防御力
	EnemyValue	ep;			// 回避力
	EnemyValue	fp;			// 素早さ

	int		exp;			// 所持経験値
	int		gold;			// 所持金
	ItemNum		item;			// 所持アイテム
	int		fight[ENEMY_FIGHT];	// 攻撃方法
	int		fight_r[ENEMY_FIGHT];	// 攻撃確率

	int		flg;			// 倒された時立てるフラグ番号
	int		next_enemy;		// 倒された時、次に読み込む敵ID
	int		call_enemy[ENEMY_CALL];	// 呼ぶ敵ID

	std::string	prof;			// プロフィール
} EnemyWork;

typedef struct typeEnemy{	// 敵キャラデータ（ファイル書き込み用）
	char		name[MAX_ENEMYNAME];	// 名前（40bytes）
	int		type;			// 属性

	int		hp;			// 体力
	int		ap;			// 攻撃力
	int		ag;			// 防御力
	int		mp;			// 魔法力
	int		mg;			// 魔法防御力
	int		ep;			// 回避力
	int		fp;			// 素早さ

	int		exp;			// 所持経験値
	int		gold;			// 所持金
	ItemNum		item[ENEMY_ITEM];	// 所持アイテム
	int		item_r[ENEMY_ITEM];	// 所持確率
	int		fight[ENEMY_FIGHT];	// 攻撃方法
	int		fight_r[ENEMY_FIGHT];	// 攻撃確率

	int		flg;			// 倒された時立てるフラグ番号
	int		next_enemy;		// 倒された時、次に読み込む敵ID
	int		call_enemy[ENEMY_CALL];	// 呼ぶ敵ID

	char		prof[MAX_ENEMYPROF];	// プロフィール（512bytes）
} Enemy;	// 合計801bytes
#define	ENEMYFILE_BLOCK	1000	// 敵キャラファイルに書き込むブロックサイズ


typedef struct typeEnemyParty{	// 敵パーティに付随するデータ
	int		enemy[MAX_ENEMY];	// パーティメンバー
	ItemNum		item[ENEMY_ITEM];	// 所持アイテム（パーティ固有）
	int		item_r[ENEMY_ITEM];	// 所持確率（パーティ固有）
	int		flg;			// 倒された時立てるフラグ番号
} EnemyParty;

typedef struct typeEnemyPGValue{	// 敵パーティ群の値型
	int		party;		// パーティ
	int		party_r;	// 出現確率
} EnemyPGValue;

typedef struct typeEnemyPG{	// 敵パーティ群に付随するデータ
	std::vector<EnemyPGValue>	elm;	// パーティ
} EnemyPG;

typedef struct typeEventData{	// イベントデータ
	e_event		action;			// 動作
	int		elm[EVENT_ELM];		// 内容（動作によって格納する値の意味は違う）
	int		flg;			// 動作後に判定するフラグ番号
	int		falseid;		// Falseの時遷移するイベント
	int		trueid;			// Trueの時遷移するイベント
} EventData;

typedef struct typeItem{	// アイテムデータ
	char		name[MAX_ITEMNAME];	// 名前
	e_item		type;			// 種類
	int		price;			// 価格
	int		elm[ITEM_ELM];		// 内容（種類によって格納する値の意味は違う）
	char		prof[MAX_ITEMPROF];	// 説明文
} Item; // 309bytes
#define	ITEMFILE_BLOCK	400	// アイテムファイルに書き込むブロックサイズ


typedef struct typeShopValue{	// ショップの値型
	int		item;			// 商品（アイテムID）
	int		stock;			// 在庫数
	int		spprice;		// スペシャルプライス
} ShopValue;

typedef struct typeShopData{	// ショップデータ
	std::string	name;			// 名前
	e_shop		type;			// 種類
	std::vector<ShopValue>	elm;		// 商品
} ShopData;

typedef struct typeMessData{	// メッセージデータ
	std::string	msg;			// メッセージ
} MessData;







#endif	// MY_COMMON_H

