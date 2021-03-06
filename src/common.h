#ifndef MY_COMMON_H
#define MY_COMMON_H

#include	"MyStr.h"

/****************************************/
/* デバッグフラグ			*/
/****************************************/
#define	DEBUG

#include	<vector>
#include	<string>
#include	<bitset>

/****************************************/
/* 定数					*/
/****************************************/
typedef		unsigned char	BYTE;
#define		FLG_BITS	128	// *32 bits個のフラグを扱える

#define		MAX_MYCHAR	8	// ゲーム内のマイキャラ数
#define		MAX_PARTY	4	// 同時にパーティに加わるマイキャラ数
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
#define		MAX_ENEMYNAME	82	// 敵キャラの名前の長さ
#define		MAX_ENEMYPROF	512	// 敵キャラのプロフィールの長さ

#define		MAX_WEAPON	10	// 武器の所持上限（一人）
#define		MAX_WEAPONCACHE	1024	// 一度に読み込める最大武器数
#define		MAX_WEAPONNAME	40	// 武器の名前の長さ
#define		MAX_WEAPONPROF	128	// 武器の説明文の長さ

#define		MAX_ARMOR	10	// 防具の所持上限（一人）
#define		MAX_ARMORCACHE	1024	// 一度に読み込める最大防具数
#define		MAX_ARMORNAME	40	// 防具の名前の長さ
#define		MAX_ARMORPROF	128	// 防具の説明文の長さ

#define		MAX_ITEM	128	// アイテムの所持上限（一人）
#define		MAX_ITEMCACHE	1024	// 一度に読み込める最大アイテム数
#define		MAX_ITEMNAME	40	// アイテムの名前の長さ
#define		MAX_ITEMPROF	128	// アイテムの説明文の長さ
#define		MAX_SITEM	16	// スペシャルアイテムの所持上限
#define		MAX_STOCK	99	// １つのアイテムの所持上限
#define		ITEM_ELM	5	// アイテム内容

#define		EVENT_ELM	5	// イベント内容

#define		MAX_SPPOS	256	// スペシャルポジションの最大数
#define		MAX_TILE	256	// 読み込めるタイルの最大数
#define		MAX_MAPEVENT	128	// マップイベントの最大数
#define		MAX_FNAME	64	// 地名の最大数

#define		MAX_INTNUM	30	// INT入力時の桁数：10桁（1文字3byteで計算）

#define		STR(var)	#var	//引数にした変数を変数名を示す文字列リテラルとして返すマクロ関数

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
		T_LIGHT	= 0x10,	// 光
		T_DARK	= 0x20,	// 闇
		T_TIME	= 0x40,	// 時
		T_SPACE	= 0x80	// 空
};
struct Str_e_type : public std::string {
	Str_e_type(e_type e) {
		switch(e) {
			break; case T_FIRE : { assign("火"); }
			break; case T_WATER: { assign("水"); }
			break; case T_WIND : { assign("風"); }
			break; case T_EARTH: { assign("地"); }
			break; case T_LIGHT: { assign("光"); }
			break; case T_DARK : { assign("闇"); }
			break; case T_TIME : { assign("時"); }
			break; case T_SPACE: { assign("空"); }
			break; default:      { assign("無"); }
		}
	}
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

enum e_rare {
		R_NORMAL,	// ノーマル
		R_RARE,		// レア
		R_SRARE,	// Sレア
		R_SSRARE,	// SSレア
		R_URARE,	// Uレア
		R_LEGEND	// SSレア
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

enum e_armor {
		A_UPPER,	// 上半身
		A_BOTTOM,	// 下半身
		A_ONEPIECE,	// ワンピース
		A_MANT,		// マント
		A_HERMET,	// 兜
		A_GAUNTLET,	// 篭手
		A_SHIELD,	// 盾
		A_BOOTS,	// ブーツ
		A_RING,		// 指輪
		A_INNER		// 下着
};

enum e_m_fire {
		EM_FIRE0	= 0x0001,	// ファイア
		EM_FIRE1	= 0x0002,	// ファイア
		EM_FIRE2	= 0x0004,	// ファイア
		EM_FIRE3	= 0x0008,	// ファイア
		EM_FIRE4	= 0x0010,	// ファイア
		EM_FIRE5	= 0x0020,	// ファイア
		EM_FIRE6	= 0x0040,	// ファイア
		EM_FIRE7	= 0x0080,	// ファイア
		EM_FIRE8	= 0x0100,	// ファイア
		EM_FIRE9	= 0x0200,	// ファイア
		EM_FIREA	= 0x0400,	// ファイア
		EM_FIREB	= 0x0800,	// ファイア
		EM_FIREC	= 0x1000,	// ファイア
		EM_FIRED	= 0x2000,	// ファイア
		EM_FIREE	= 0x4000,	// ファイア
		EM_FIREF	= 0x8000	// ファイア
};
struct Str_e_m_fire : public std::string {
	Str_e_m_fire(e_m_fire e) {
		switch(e) {
			break; case EM_FIRE0 : { assign("ファイア"); }
			break; case EM_FIRE1 : { assign("照明弾"); }
			break; case EM_FIRE2 : { assign("フレイム"); }
			break; case EM_FIRE3 : { assign("ファイアウォール"); }
			break; case EM_FIRE4 : { assign("命の炎"); }
			break; case EM_FIRE5 : { assign("メガファイア"); }
			break; case EM_FIRE6 : { assign(""); }
			break; case EM_FIRE7 : { assign(""); }
			break; case EM_FIRE8 : { assign("メガフレイム"); }
			break; case EM_FIRE9 : { assign("熱消毒"); }
			break; case EM_FIREA : { assign(""); }
			break; case EM_FIREB : { assign("ギガファイア"); }
			break; case EM_FIREC : { assign(""); }
			break; case EM_FIRED : { assign("ギガフレイム"); }
			break; case EM_FIREE : { assign(""); }
			break; case EM_FIREF : { assign("ファイナルエクスプロージョン"); }
			break; default:      { assign("無"); }
		}
	}
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
		SK_ROGUE	= 0x00,	// 盗賊
		SK_HEARL	= 0x01,	// 調合
		SK_THRROW	= 0x02,	// 投げる
		SK_SWIM		= 0x04,	// 泳ぐ
		SK_COOK		= 0x08,	// 料理
		SK_DANCE	= 0x10,	// ダンス
		SK_LUCK		= 0x20,	// 運
		SK_DUMMY	= 0x40	// 予備
};

enum e_enemyfight {
		EF_ATTACK,	// 物理攻撃
		EF_MAGIC,	// 魔法
		EF_ITEM,	// アイテム攻撃
		EF_GUARD,	// ガード
		EF_ESCAPE,	// 逃げる
		EF_ROGUE,	// 盗む
		EF_CALL,	// 仲間を呼ぶ
		EF_TRANSE,	// 変身する
		EF_CHANGE,	// 属性を変える
		EF_SUCIDE	// 自爆
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
	int		an;			// 攻撃回数
	int		ag;			// 防御力
	int		mp;			// 魔法力
	int		mn;			// 魔法回数
	int		mg;			// 魔法防御力
	int		hr;			// 命中率
	int		er;			// 回避率
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
} Enemy;	// 合計814bytes
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

typedef struct typeWeapon{	// 武器データ
	char		name[MAX_WEAPONNAME];	// 名前
	int		type;			// 属性
	int		kind;			// 種類
	int		rare;			// レアリティ
	int		ap;			// 攻撃力
	int		an;			// 攻撃回数
	int		ag;			// 防御力
	int		mp;			// 魔法力
	int		mn;			// 魔法回数
	int		mg;			// 魔法防御力
	int		hr;			// 命中率
	int		er;			// 回避率
	int		fp;			// 素早さ
	int		option;			// 追加効果
	int		price;			// 価格
	char		prof[MAX_WEAPONPROF];	// 説明文
} Weapon; // 224bytes
#define	WEAPONFILE_BLOCK	300	// 武器ファイルに書き込むブロックサイズ

typedef struct typeArmor{	// 防具データ
	char		name[MAX_ARMORNAME];	// 名前
	int		type;			// 属性
	int		kind;			// 種類
	int		rare;			// レアリティ
	int		ag;			// 防御力
	int		mg;			// 魔法防御力
	int		er;			// 回避率
	int		fp;			// 素早さ
	int		option;			// 追加効果
	int		price;			// 価格
	char		prof[MAX_ARMORPROF];	// 説明文
} Armor; // 204bytes
#define	ARMORFILE_BLOCK	250	// 武器ファイルに書き込むブロックサイズ

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

