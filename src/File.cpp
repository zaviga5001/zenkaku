#include "File.h"

CFile::CFile()
{
}

CFile::~CFile()
{
}

void CFile::read_cfg(const std::string fname, CConfig* config)
{
	std::map<std::string, std::string> data;
	std::fstream in(fname.c_str(), std::ios::in);
	if( in.fail() ){
		fprintf(stderr, "WARN:file001:Read failure(zenkakurc)\n");
		return;
	}

	char buf[512];
	while (in.getline(buf, 512)){
		std::istringstream iss(buf);
		std::string key, value;
		iss >> key >> value;
		if(key.length() != 0 && value.length() != 0)
		data[key] = value;
	}

	// 設定値の取り出し
	std::string &value = data["title"];
	std::istringstream iss(value);
	iss >> config->m_title;
}

ScnList CFile::read_scenario_list(const std::string fname)
{
	ScnList	tmp_scn;
	tmp_scn.id = 1;

	std::map<std::string, std::string> data;
	std::fstream in(fname.c_str(), std::ios::in);
	if( in.fail() ){
		fprintf(stderr, "WARN:file002:Read failure(scenario)\n");
		tmp_scn.id = 0;
		return(tmp_scn);
	}

	char buf[10000];
	while (in.getline(buf, 10000)){
		std::istringstream iss(buf);
		std::string key, value;
		iss >> key >> value;
		if(key.length() != 0 && value.length() != 0)
		data[key] = value;
	}

	// 設定値の取り出し
	tmp_scn.name = data["scenario"].c_str();
	tmp_scn.doc = data["doc"].c_str();

	return(tmp_scn);
}


int CFile::read_mychar(CData* data)
{
	FILE*	fp;
	char	tmp_buf[1024];

	fp = fopen(data->m_scn.mychar[0].c_str(), "r");
	if (fp == NULL)	return 0;

	fread(&data->m_mychar[0].id,	sizeof(int),		1, fp);
	fread(&data->m_mychar[0].race,	sizeof(enum e_race),	1, fp);
	fread(&data->m_mychar[0].job,	sizeof(enum e_job),	1, fp);
	fread(&data->m_mychar[0].gender,sizeof(enum e_gender),	1, fp);
	fread( data->m_mychar[0].tile,	sizeof(char),		2, fp);
	fread(&data->m_mychar[0].ch,	sizeof(char),		1, fp);
	fread(&data->m_mychar[0].bg,	sizeof(char),		1, fp);
	fread(&data->m_mychar[0].type,	sizeof(BYTE),		1, fp);
	fread(&data->m_mychar[0].status,sizeof(enum e_status),	1, fp);
	fread(&data->m_mychar[0].level,	sizeof(char),		1, fp);
	fread(&data->m_mychar[0].exp,	sizeof(int),		1, fp);
	fread(&data->m_mychar[0].hp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].sp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].ap,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].gp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].mp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].ep,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].fp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].dp,	sizeof(MyCharValue),	1, fp);
	fread(&data->m_mychar[0].rweapon,sizeof(short),		1, fp);
	fread(&data->m_mychar[0].lweapon,sizeof(short),		1, fp);
	fread(&data->m_mychar[0].helm,	sizeof(short),		1, fp);
	fread(&data->m_mychar[0].armor,	sizeof(short),		1, fp);
	fread(&data->m_mychar[0].mant,	sizeof(short),		1, fp);
	fread(&data->m_mychar[0].boots,	sizeof(short),		1, fp);
	fread( data->m_mychar[0].equip,	sizeof(short),		MAX_EQUIP, fp);
	fread(&data->m_mychar[0].food,	sizeof(BYTE),		1, fp);
	fread(&data->m_mychar[0].magic,	sizeof(BYTE),		MAX_TYPE * MAX_MAGIC, fp);
	fread(&data->m_mychar[0].magicexp,sizeof(BYTE),		MAX_TYPE * MAX_MAGIC, fp);
	fread(&data->m_mychar[0].fight,	sizeof(BYTE),		MAX_TYPE * MAX_FIGHT, fp);
	fread(&data->m_mychar[0].fightexp,sizeof(BYTE),		MAX_TYPE * MAX_FIGHT, fp);
	fread(&data->m_mychar[0].skill,	sizeof(BYTE),		MAX_TYPE * MAX_SKILL, fp);
	fread(&data->m_mychar[0].skillexp,sizeof(BYTE),		MAX_TYPE * MAX_SKILL, fp);
	fread(&data->m_mychar[0].curse,	sizeof(BYTE),		MAX_TYPE, fp);

	for (int j = 0; j < 1024; j++)
	{
		if (feof(fp))	break;
		fread(&tmp_buf[j], sizeof(char), 1, fp);
		if (tmp_buf[j] == ':')
		{
			tmp_buf[j] = 0;
			data->m_mychar[0].name = tmp_buf;
			break;
		}
	}
	for (int j = 0; j < 1024; j++)
	{
		if (feof(fp))	break;
		fread(&tmp_buf[j], sizeof(char), 1, fp);
		if (tmp_buf[j] == ':')
		{
			tmp_buf[j] = 0;
			data->m_mychar[0].prof = tmp_buf;
			break;
		}
	}

	fclose(fp);

	return(1);
}

bool CFile::write_mychar(CData* data)
{
	FILE*	fp;
	fp = fopen(data->m_scn.mychar[0].c_str(), "w");
	if (fp == NULL)	return 0;

	fwrite(&data->m_mychar[0].id,	sizeof(int),		1, fp);
	fwrite(&data->m_mychar[0].race,	sizeof(enum e_race),	1, fp);
	fwrite(&data->m_mychar[0].job,	sizeof(enum e_job),	1, fp);
	fwrite(&data->m_mychar[0].gender,sizeof(enum e_gender),	1, fp);
	fwrite( data->m_mychar[0].tile,	sizeof(char),		2, fp);
	fwrite(&data->m_mychar[0].ch,	sizeof(char),		1, fp);
	fwrite(&data->m_mychar[0].bg,	sizeof(char),		1, fp);
	fwrite(&data->m_mychar[0].type,	sizeof(BYTE),		1, fp);
	fwrite(&data->m_mychar[0].status,sizeof(enum e_status),	1, fp);
	fwrite(&data->m_mychar[0].level,sizeof(char),		1, fp);
	fwrite(&data->m_mychar[0].exp,	sizeof(int),		1, fp);
	fwrite(&data->m_mychar[0].hp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].sp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].ap,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].gp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].mp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].ep,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].fp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].dp,	sizeof(MyCharValue),	1, fp);
	fwrite(&data->m_mychar[0].rweapon,sizeof(short),	1, fp);
	fwrite(&data->m_mychar[0].lweapon,sizeof(short),	1, fp);
	fwrite(&data->m_mychar[0].helm,	sizeof(short),		1, fp);
	fwrite(&data->m_mychar[0].armor,sizeof(short),		1, fp);
	fwrite(&data->m_mychar[0].mant,	sizeof(short),		1, fp);
	fwrite(&data->m_mychar[0].boots,sizeof(short),		1, fp);
	fwrite( data->m_mychar[0].equip,sizeof(short),		MAX_EQUIP, fp);
	fwrite(&data->m_mychar[0].food,	sizeof(BYTE),		1, fp);
	fwrite(&data->m_mychar[0].magic,sizeof(BYTE),		MAX_TYPE * MAX_MAGIC, fp);
	fwrite(&data->m_mychar[0].magicexp,sizeof(BYTE),	MAX_TYPE * MAX_MAGIC, fp);
	fwrite(&data->m_mychar[0].fight,sizeof(BYTE),		MAX_TYPE * MAX_FIGHT, fp);
	fwrite(&data->m_mychar[0].fightexp,sizeof(BYTE),	MAX_TYPE * MAX_FIGHT, fp);
	fwrite(&data->m_mychar[0].skill,sizeof(BYTE),		MAX_TYPE * MAX_SKILL, fp);
	fwrite(&data->m_mychar[0].skillexp,sizeof(BYTE),	MAX_TYPE * MAX_SKILL, fp);
	fwrite(&data->m_mychar[0].curse,sizeof(BYTE),		MAX_TYPE, fp);

	fwrite(data->m_mychar[0].name.c_str(),	sizeof(char),	data->m_mychar[0].name.capacity(), fp);
	fwrite( ":", sizeof(char), 1, fp);
	fwrite(data->m_mychar[0].prof.c_str(),	sizeof(char),	data->m_mychar[0].prof.capacity(), fp);
	fwrite( ":", sizeof(char), 1, fp);

	fclose(fp);

	return(true);
}

int CFile::read_enemy(CData* data, const int index)
{
	FILE*	fp;
	char	tmp_buf[1024];

	fp = fopen("system/enemy.dat", "r");
	if (fp == NULL)	return 0;

	if (fseek(fp, 440 * index, SEEK_SET) == 0)
	{
		fread(tmp_buf, sizeof(char), MAX_ENEMYNAME, fp);
		if (feof(fp))
		{
			fclose(fp);
			return 0;
		}
		data->m_enemy[index].name = tmp_buf;
		fread(&data->m_enemy[index].type,	sizeof(BYTE),		1, fp);
		fread(&data->m_enemy[index].status,	sizeof(enum e_status),	1, fp);
		fread(&data->m_enemy[index].hp,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].ap,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].gp,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].mp,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].ep,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].fp,		sizeof(EnemyValue),	1, fp);
		fread(&data->m_enemy[index].exp,	sizeof(int),		1, fp);
		fread(&data->m_enemy[index].gold,	sizeof(int),		1, fp);
		fread(&data->m_enemy[index].item,	sizeof(ItemNum),	ENEMY_ITEM, fp);
		fread(&data->m_enemy[index].item_r,	sizeof(char),		ENEMY_ITEM, fp);
		fread(&data->m_enemy[index].fight,	sizeof(short),		ENEMY_FIGHT, fp);
		fread(&data->m_enemy[index].fight_r,	sizeof(char),		ENEMY_FIGHT, fp);
		fread(&data->m_enemy[index].flg,	sizeof(int),		1, fp);
		fread(&data->m_enemy[index].next_enemy,	sizeof(int),		1, fp);
		fread(&data->m_enemy[index].call_enemy,	sizeof(int),		ENEMY_CALL, fp);
		fread(tmp_buf, sizeof(char), MAX_ENEMYPROF, fp);
		data->m_enemy[index].prof = tmp_buf;
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}

bool CFile::write_enemy(CData* data, const int index)
{
	char	nullbuf = 0;
	FILE*	fp;
	fp = fopen("system/enemy.dat", "r+");
	if (fp == NULL)	return 0;

	fseek(fp, 440 * index, 0);

	fwrite(data->m_enemy[index].name.c_str(),	sizeof(char),		data->m_enemy[index].name.capacity(), fp);
	fwrite(&nullbuf,				sizeof(char),		MAX_ENEMYNAME - data->m_enemy[index].name.capacity(), fp);
	fwrite(&data->m_enemy[index].type,		sizeof(BYTE),		1, fp);
	fwrite(&data->m_enemy[index].status,		sizeof(enum e_status),	1, fp);
	fwrite(&data->m_enemy[index].hp,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].ap,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].gp,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].mp,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].ep,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].fp,		sizeof(EnemyValue),	1, fp);
	fwrite(&data->m_enemy[index].exp,		sizeof(int),		1, fp);
	fwrite(&data->m_enemy[index].gold,		sizeof(int),		1, fp);
	fwrite(&data->m_enemy[index].item,		sizeof(ItemNum),	ENEMY_ITEM, fp);
	fwrite(&data->m_enemy[index].item_r,		sizeof(char),		ENEMY_ITEM, fp);
	fwrite(&data->m_enemy[index].fight,		sizeof(short),		ENEMY_FIGHT, fp);
	fwrite(&data->m_enemy[index].fight_r,		sizeof(char),		ENEMY_FIGHT, fp);
	fwrite(&data->m_enemy[index].flg,		sizeof(int),		1, fp);
	fwrite(&data->m_enemy[index].next_enemy,	sizeof(int),		1, fp);
	fwrite(&data->m_enemy[index].call_enemy,	sizeof(int),		ENEMY_CALL, fp);
	fwrite(data->m_enemy[index].prof.c_str(),	sizeof(char),		data->m_enemy[index].prof.capacity(), fp);
	fwrite(&nullbuf,				sizeof(char),		MAX_ENEMYPROF - data->m_enemy[index].prof.capacity(), fp);

	fclose(fp);

	return(true);
}

int CFile::read_party(CData* data, const int index)
{
	FILE*	fp;
	std::string tmppath = "data/" + data->m_scn.path + "/party.dat";
	fp = fopen(tmppath.c_str(), "r");
	if (fp == NULL)	return 0;

	if (fseek(fp, sizeof(EnemyParty) * index, SEEK_SET) == 0)
	{
		fread( data->m_enemyparty.enemy,	sizeof(int),		MAX_ENEMY, fp);
		if (feof(fp))
		{
			fclose(fp);
			return 0;
		}
		fread( data->m_enemyparty.item,		sizeof(ItemNum),	ENEMY_ITEM, fp);
		fread( data->m_enemyparty.item_r,	sizeof(char),		ENEMY_ITEM, fp);
		fread(&data->m_enemyparty.flg,		sizeof(int),		1, fp);
		fclose(fp);
		return 1;
	}
	fclose(fp);
	return 0;
}

bool CFile::write_party(CData* data, const int index)
{
	FILE*	fp;
	std::string tmppath = "data/" + data->m_scn.path + "/party.dat";
	fp = fopen(tmppath.c_str(), "r+");
	if (fp == NULL)	return 0;

	fseek(fp, sizeof(EnemyParty) * index, 0);

	fwrite( data->m_enemyparty.enemy,	sizeof(int),		MAX_ENEMY, fp);
	fwrite( data->m_enemyparty.item,	sizeof(ItemNum),	ENEMY_ITEM, fp);
	fwrite( data->m_enemyparty.item_r,	sizeof(char),		ENEMY_ITEM, fp);
	fwrite(&data->m_enemyparty.flg,		sizeof(int),		1, fp);

	fclose(fp);

	return(true);
}

int CFile::read_pg(CData* data, const int index)
{
	FILE*		fp;
	EnemyPG		tmp_pg;
	EnemyPGValue	tmp_pgv;
	char		tmp_buf[10];
	std::string	tmp_cs;

	sprintf(tmp_buf, "/p%03d.dat", index);
	tmp_cs = tmp_buf;
	tmp_cs = "data/" + data->m_scn.path + tmp_cs;

	fp = fopen(tmp_cs.c_str(), "r");
	if (fp == NULL)	return 0;

	while(!feof(fp))
	{
		fread(&tmp_pgv,	sizeof(EnemyPGValue),	1, fp);
		if (feof(fp))	break;
		tmp_pg.elm.push_back(tmp_pgv);
	}
	if (index >= data->m_enemypg.size())
	{
		data->m_enemypg.push_back(tmp_pg);
	}
	else
	{
		data->m_enemypg[index] = tmp_pg;
	}

	fclose(fp);
	return(true);
}

bool CFile::write_pg(CData* data, const int index)
{
	FILE*		fp;
	char		tmp_buf[12];
	std::string		tmp_cs;

	sprintf(tmp_buf, "/p%03d.dat", index);
	tmp_cs = tmp_buf;
	tmp_cs = "data/" + data->m_scn.path + tmp_cs;

	fp = fopen(tmp_cs.c_str(), "w");
	if (fp == NULL)	return 0;

	for (int i = 0; i < data->m_enemypg[index].elm.size(); i++)
	{
		fwrite(&data->m_enemypg[index].elm[i],	sizeof(EnemyPGValue),	1, fp);
	}

	fclose(fp);

	return(true);
}

bool CFile::read_event(CData* data)
{
	FILE*	fp;
	EventData	tmp_ev;

	std::string tmppath = "data/" + data->m_scn.path + "/event.dat";
	fp = fopen(tmppath.c_str(), "r");
	if (fp == NULL)	return 0;

	while(!feof(fp))
	{
		fread(&tmp_ev.action,	sizeof(enum e_event),	1, fp);
		if (feof(fp))	break;
		fread( tmp_ev.elm,	sizeof(int),		EVENT_ELM, fp);
		fread(&tmp_ev.flg,	sizeof(int),		1, fp);
		fread(&tmp_ev.falseid,	sizeof(int),		1, fp);
		fread(&tmp_ev.trueid,	sizeof(int),		1, fp);
		data->m_event.push_back(tmp_ev);
		data->m_eventnum++;
	}
	fclose(fp);
	return 1;
}

bool CFile::write_event(CData* data, const int index)
{
	FILE*	fp;
	std::string tmppath = "data/" + data->m_scn.path + "/event.dat";
	fp = fopen(tmppath.c_str(), "r+");
	if (fp == NULL)	return 0;

	fseek(fp, sizeof(EventData) * index, 0);

	fwrite(&data->m_event[index].action,	sizeof(enum e_event),	1, fp);
	fwrite( data->m_event[index].elm,	sizeof(int),		EVENT_ELM, fp);
	fwrite(&data->m_event[index].flg,	sizeof(int),		1, fp);
	fwrite(&data->m_event[index].falseid,	sizeof(int),		1, fp);
	fwrite(&data->m_event[index].trueid,	sizeof(int),		1, fp);

	fclose(fp);
	return(true);
}

bool CFile::read_item(CData* data)
{
	FILE*		fp;
	ItemData	tmp_it;
	char		tmp_buf[1024];
	int		i;

	fp = fopen("system/item.dat", "r");
	if (fp == NULL)	return 0;

	while(!feof(fp))
	{
		for (i = 0; ; i++)
		{
			fread(&tmp_buf[i], sizeof(char), 1, fp);
			if (feof(fp))
			{
				fclose(fp);
				return 0;
			}
			if (tmp_buf[i] == ':')
			{
				tmp_buf[i] = 0;
				break;
			}
		}
		tmp_it.name = tmp_buf;
		fread(&tmp_it.type,	sizeof(enum e_item),	1, fp);
		fread(&tmp_it.price,	sizeof(int),		1, fp);
		fread( tmp_it.elm,	sizeof(int),		ITEM_ELM, fp);
		if (feof(fp))	break;
		data->m_item.push_back(tmp_it);
		data->m_itemnum++;
	}
	fclose(fp);
	return(true);
}

bool CFile::write_item(CData* data)
{
	FILE*		fp;
	fp = fopen("system/item.dat", "w");
	if (fp == NULL)	return 0;

	for (int i = 0; i < data->m_itemnum; i++)
	{
		fwrite(data->m_item[i].name.c_str(),sizeof(char),	data->m_item[i].name.capacity(), fp);
		fwrite(":",			sizeof(char),		1, fp);
		fwrite(&data->m_item[i].type,	sizeof(enum e_item),	1, fp);
		fwrite(&data->m_item[i].price,	sizeof(int),		1, fp);
		fwrite( data->m_item[i].elm,	sizeof(int),		ITEM_ELM, fp);
	}

	fclose(fp);
	return(true);
}

bool CFile::read_shop(CData* data, const int index)
{
	FILE*		fp;
	ShopData	tmp_sh;
	ShopValue	tmp_shv;
	char		tmp_buf[1024];
	std::string	tmp_cs;

	sprintf(tmp_buf, "/s%03d.dat", index);
	tmp_cs = tmp_buf;
	tmp_cs = "data/" + data->m_scn.path + tmp_cs;

	fp = fopen(tmp_cs.c_str(), "r");
	if (fp == NULL)	return 0;

	for (int i = 0; ; i++)
	{
		fread(&tmp_buf[i], sizeof(char), 1, fp);
		if (tmp_buf[i] == ':')
		{
			tmp_buf[i] = 0;
			break;
		}
	}
	tmp_sh.name = tmp_buf;
	fread(&tmp_sh.type,	sizeof(enum e_shop),	1, fp);

	while(!feof(fp))
	{
		fread(&tmp_shv,	sizeof(ShopValue),	1, fp);
		if (feof(fp))	break;
		tmp_sh.elm.push_back(tmp_shv);
	}
	data->m_shop = tmp_sh;

	fclose(fp);
	return(true);

}

bool CFile::write_shop(CData* data, const int index)
{
	FILE*		fp;
	char		tmp_buf[12];
	std::string	tmp_cs;

	sprintf(tmp_buf, "/s%03d.dat", index);
	tmp_cs = tmp_buf;
	tmp_cs = "data/" + data->m_scn.path + tmp_cs;

	fp = fopen(tmp_cs.c_str(), "w");
	if (fp == NULL)	return 0;

	fwrite(data->m_shop.name.c_str(),	sizeof(char),		data->m_shop.name.capacity(), fp);
	fwrite(":",				sizeof(char),		1, fp);
	fwrite(&data->m_shop.type,		sizeof(enum e_shop),	1, fp);

	for (int i = 0; i < data->m_shop.elm.size(); i++)
	{
		fwrite(&data->m_shop.elm[i],	sizeof(ShopValue),	1, fp);
	}

	fclose(fp);
	return(true);
}

bool CFile::read_mess(CData* data)
{
	FILE*		fp;
	MessData	tmp_ms;
	char		tmp_buf[1024];
	int		i;

	std::string tmppath = "data/" + data->m_scn.path + "/mess.dat";
	fp = fopen(tmppath.c_str(), "r");
	if (fp == NULL)	return 0;

	while(!feof(fp))
	{
		for (i = 0; ; i++)
		{
			fread(&tmp_buf[i], sizeof(char), 1, fp);
			if (feof(fp))
			{
				fclose(fp);
				return 0;
			}
			if (tmp_buf[i] == ':')
			{
				tmp_buf[i] = 0;
				break;
			}
		}
		tmp_ms.msg = tmp_buf;
		if (feof(fp))	break;
		data->m_mess.push_back(tmp_ms);
		data->m_messnum++;
	}
	fclose(fp);
	return(true);
}

bool CFile::write_mess(CData* data)
{
	FILE*		fp;
	std::string tmppath = "data/" + data->m_scn.path + "/mess.dat";
	fp = fopen(tmppath.c_str(), "w");
	if (fp == NULL)	return 0;

	for (int i = 0; i < data->m_messnum; i++)
	{
		fwrite(data->m_mess[i].msg.c_str(),	sizeof(char),	data->m_mess[i].msg.capacity(), fp);
		fwrite(":",				sizeof(char),	1, fp);
	}

	fclose(fp);
	return(true);
}

MapData CFile::get_map_size(const std::string fname)
{
	MapData	size;
	size.height = 0;
	size.width  = 0;
	std::string fname_t = fname + ".txt";
	std::ifstream ifs(fname_t.c_str());
	std::string str;
	if (ifs.fail())
	{
		std::cerr << "失敗" << std::endl;
		return(size);
	}
	while (getline(ifs, str))
	{
		size.height++;
		if (str.length() > size.width)		size.width = str.length();
	}
	return(size);
}

int CFile::read_map(const std::string fname, MapData* mapdata, PosData* posdata, PosData* spposdata, TileData* tiledata, PosEvent* pevent, PosEvent* sevent, std::string* fieldname)
{
/*	FILE*	fp;
	std::string fname_t = fname + ".txt";
	std::string fname_b = fname + ".bin";
	std::string tmp_cs;
	//tmp_cs.setDefaultCharset(std::string::EUC_JP);
	int	i, j, k, num = 0, flg;

	fp = fopen(fname_b.c_str(), "r");
	if (fp == NULL)
	{ // タイルファイルなし マップから新規作成
		fp = fopen(fname_t.c_str(), "r");
		if (fp == NULL)	return 0;	// タイルもマップもなし
		for (k = 0; ; k++)
        	{ // 行単位ループ
			if(tmp_cs.ReadLine(fp) == EOF)        break;
			for(i = 0; i < tmp_cs.length(); i = i + 2)
			{ // 文字単位ループ
				flg = false;
				for(j = 0; j < num; j++)
				{ // 既に読んだ文字と比較
					if (tmp_cs[i]     == tiledata[j].tile[0] &&
					    tmp_cs[i + 1] == tiledata[j].tile[1]   )
					{ // 既に登録があった
						posdata[k * mapdata->width + (i / 2)].falseid = (char)j;
						flg = true;
						break;
					}
				}
				if (!flg)
				{	// 登録がなかった
					tiledata[num].tile[0]	= tmp_cs[i];
					tiledata[num].tile[1]	= tmp_cs[i + 1];
					tiledata[num].ch	= 7;
					tiledata[num].bg	= 0;
					tiledata[num].attr	= 0;
					tiledata[num].height	= 50;
					tiledata[num].move	= 0;

					// ポジションデータ保存
					posdata[k * mapdata->width + (i / 2)].falseid = (char)num;
					num++;
				}
				posdata[k * mapdata->width + (i / 2)].flg     = 0;
				posdata[k * mapdata->width + (i / 2)].trueid  = 0;
				posdata[k * mapdata->width + (i / 2)].name    = 0;
				posdata[k * mapdata->width + (i / 2)].enemy   = 0;
				posdata[k * mapdata->width + (i / 2)].encount = 10;

				// PADに描画
				//wattrset(map, COLOR_PAIR(0));
				//mvwaddstr(map, k, i, (LPCSTR)tmp_cs.Sub(i, i + 2));
			}
		}
		// NextMap初期化
		mapdata->nextmap_u = 0;
		mapdata->nextmap_d = 0;
		mapdata->nextmap_l = 0;
		mapdata->nextmap_r = 0;

		for (k = 0; k < MAX_SPPOS; k++)
        	{ // スペシャルポジション初期化
			spposdata[k].flg     = 0;
			spposdata[k].trueid  = 0;
			spposdata[k].falseid = 0;
			spposdata[k].name    = 0;
			spposdata[k].enemy   = 0;
			spposdata[k].encount = 10;
		}
	}
	else
	{ // タイルファイルあり 読み込み
		fread(mapdata,   sizeof(MapData), 1, fp);
		fread(posdata,   sizeof(struct typePosData), mapdata->height * mapdata->width, fp);
		fread(spposdata, sizeof(PosData), MAX_SPPOS, fp);
		fread(&num,      sizeof(int    ), 1, fp);
		for (int i = 0; i < num; i++)
		{
			fread(&tiledata[i],  sizeof(TileData), 1, fp);
		}
		fread(pevent,    sizeof(PosEvent), MAX_MAPEVENT, fp);
		fread(sevent,    sizeof(PosEvent), MAX_MAPEVENT, fp);

		char tmp_buf[1024];
		for (int i = 0; i < MAX_FNAME; i++)
		{
			if (feof(fp))	break;
			for (int j = 0; j < 1024; j++)
			{
				if (feof(fp))	break;
				fread(&tmp_buf[j], sizeof(char), 1, fp);
				if (tmp_buf[j] == ':')
				{
					tmp_buf[j] = 0;
					fieldname[i] = tmp_buf;
					break;
				}
			}
		}
	}
	fclose(fp);

	return(num);	// タイルの数を返す
*/
	return(0);	// タイルの数を返す
}

bool CFile::write_map(const std::string fname, MapData* mapdata, PosData* posdata, PosData* spposdata, TileData* tiledata, PosEvent* pevent, PosEvent* sevent, std::string* fieldname, int tilenum)
{
/*	FILE*	fp;
	std::string fname_b = fname + ".bin";
	bool	ret;

	fp = fopen(fname_b.c_str(), "w");
	if (fp != NULL)
	{
		// 書き出し
		fwrite(mapdata,   sizeof(MapData), 1, fp);
		fwrite(posdata,   sizeof(struct typePosData), mapdata->height * mapdata->width, fp);
		fwrite(spposdata, sizeof(PosData), MAX_SPPOS, fp);
		fwrite(&tilenum,  sizeof(int    ), 1, fp);
		for (int i = 0; i < tilenum; i++)
		{
			fwrite(&tiledata[i],  sizeof(TileData), 1, fp);
		}
		fwrite(pevent,    sizeof(PosEvent), MAX_MAPEVENT, fp);
		fwrite(sevent,    sizeof(PosEvent), MAX_MAPEVENT, fp);
		for (int i = 0; i < MAX_FNAME; i++)
		{
			if (fieldname[i] == "　")	break;
			fwrite(fieldname[i].c_str(), sizeof(char), fieldname[i].capacity(), fp);
			fwrite( ":", sizeof(char), 1, fp);
		}

		fclose(fp);
		ret = true;
	}
	else
	{ // ファイル作成できず
		ret = false;
	}

	return(ret);
*/
	return(0);
}


std::string CFile::input_path_dialog()
{
	std::string retstr;

	CWinGetPath*	win;
	win = new CWinGetPath;
	win->settitle(std::string(msg[MY_MSG_SYS_INP_PATH].msg));
	retstr = win->startdialog(true);
	delete(win);
	return (retstr);
}

void CFile::mychop(std::string& cs)
{
/*	// スペース、タブ、'#'以降を取り除く
	int i;
	i = cs.Find("#");
	if (i > NOT_FOUND)	cs = cs.Left(i);
	if (cs.length() > 0)	cs = cs.Replace(" ", "", SSF_ALL);
	if (cs.length() > 0)	cs = cs.Replace("\t", "", SSF_ALL);
*/
}

/*
void CFile::readcsv(const std::string cs, CList<int>* cl)
{
	std::string tmp_cs = cs;
	int	tmp_num;
	bool	flg = false;

	while (1)
	{
		tmp_num = tmp_cs.Find(",");			// 探す
		if (tmp_num == NOT_FOUND)
		{
			tmp_num = tmp_cs.length();			// なかったら、文字列全部を対象にする
			flg = true;				// なかったら、処理後終了する
		}

		if (tmp_num == 0)		cl->Append(0);
		else if (tmp_num > 0)		cl->Append(atoi(tmp_cs.Left(tmp_num)));
		else	break;

		if (flg)	break;

		tmp_cs = tmp_cs.Sub(tmp_num + 1);		// カンマの次の文字に進む
	}
}
*/


