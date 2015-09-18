#include "File.h"

CFile::CFile()
{
}

CFile::~CFile()
{
}

void CFile::read_cfg(CConfig* config)
{
	std::string fname = user_home + ZENKAKURC;
	config->m_mode  = 0;

	std::map<std::string, std::string> data;
	std::ifstream ifs(fname.c_str());
	if( ifs.fail() ){
		std::cerr << "WARN:file001:Read failure(zenkakurc)" << std::endl;
		return;
	}

	std::string buf, key, value;
	while (std::getline(ifs, buf)){
		std::istringstream iss(buf);
		iss >> key >> value;
		if(key[0] == '#')	continue;
		if(key.length() != 0 && value.length() != 0)
			data[key] = value;
	}

	// 設定値の取り出し
	config->m_mode  = atoi(data["mode"].c_str());
	config->m_title = atoi(data["title"].c_str());
}

ScnList CFile::read_scenario_list(const std::string fname)
{
	ScnList	tmp_scn;
	tmp_scn.id = 1;

	std::map<std::string, std::string> data;
	std::ifstream ifs(fname.c_str());
	if( ifs.fail() ){
		std::cerr << "WARN:file002:Read failure(scenario)" << std::endl;
		tmp_scn.id = 0;
		return(tmp_scn);
	}

	std::string buf, key, value;
	while (std::getline(ifs, buf)){
		std::istringstream iss(buf);
		iss >> key >> value;
		if(key[0] == '#')	continue;
		if(key.length() != 0 && value.length() != 0)
		data[key] = value;
	}

	// 設定値の取り出し
	tmp_scn.name = data["scenario"];
	tmp_scn.doc = data["doc"];

	return(tmp_scn);
}


bool CFile::read_mychar(CData* data, int id)
{
	std::ifstream ifs(data->m_scn.mychar[id].c_str());
	if( ifs.fail() ){
		std::cerr << "WARN:file003:Read failure(mychar)" << std::endl;
		return(0);
	}

	std::string buf[1000];
	int count = 0;
	for (int i = 0; std::getline(ifs, buf[i]); i++){};

	data->m_mychar[id].id		= atoi(buf[count++].c_str());
	data->m_mychar[id].race		= (e_race)atoi(buf[count++].c_str());
	data->m_mychar[id].job		= (e_job)atoi(buf[count++].c_str());
	data->m_mychar[id].gender	= (e_gender)atoi(buf[count++].c_str());
	data->m_mychar[id].name		= buf[count++];
	data->m_mychar[id].tile		= buf[count++];
	data->m_mychar[id].ch		= atoi(buf[count++].c_str());
	data->m_mychar[id].bg		= atoi(buf[count++].c_str());
	data->m_mychar[id].type		= atoi(buf[count++].c_str());
	data->m_mychar[id].status	= (e_status)atoi(buf[count++].c_str());
	data->m_mychar[id].level	= atoi(buf[count++].c_str());
	data->m_mychar[id].exp		= atoi(buf[count++].c_str());
	data->m_mychar[id].hp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].hp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].hp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].sp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].sp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].sp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].ap.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].ap.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].ap.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].gp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].gp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].gp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].mp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].mp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].mp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].ep.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].ep.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].ep.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].fp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].fp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].fp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].dp.p		= atoi(buf[count++].c_str());
	data->m_mychar[id].dp.t		= atoi(buf[count++].c_str());
	data->m_mychar[id].dp.m		= atoi(buf[count++].c_str());
	data->m_mychar[id].rweapon	= atoi(buf[count++].c_str());
	data->m_mychar[id].lweapon	= atoi(buf[count++].c_str());
	data->m_mychar[id].helm		= atoi(buf[count++].c_str());
	data->m_mychar[id].armor	= atoi(buf[count++].c_str());
	data->m_mychar[id].mant		= atoi(buf[count++].c_str());
	data->m_mychar[id].boots	= atoi(buf[count++].c_str());
	for (int i = 0; i < MAX_EQUIP; i++){
		data->m_mychar[id].equip[i]	= atoi(buf[count++].c_str());
	}
	data->m_mychar[id].food		= atoi(buf[count++].c_str());

	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_MAGIC; j++){
			data->m_mychar[id].magic[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_MAGIC; j++){
			data->m_mychar[id].magicexp[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			data->m_mychar[id].fight[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			data->m_mychar[id].fightexp[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_SKILL; j++){
			data->m_mychar[id].skill[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_SKILL; j++){
			data->m_mychar[id].skillexp[i][j]	= atoi(buf[count++].c_str());
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		data->m_mychar[id].curse[i]	= atoi(buf[count++].c_str());
	}
	data->m_mychar[id].prof		= buf[count++];

	return(1);
}

bool CFile::write_mychar(CData* data, int id)
{
	std::ofstream ofs(data->m_scn.mychar[id].c_str());
	if( ofs.fail() ){
		std::cerr << "WARN:file004:Write failure(mychar)" << std::endl;
		return(0);
	}

	ofs << data->m_mychar[id].id << std::endl;
	ofs << data->m_mychar[id].race << std::endl;
	ofs << data->m_mychar[id].job << std::endl;
	ofs << data->m_mychar[id].gender << std::endl;
	ofs << data->m_mychar[id].name << std::endl;
	ofs << data->m_mychar[id].tile << std::endl;
	ofs << data->m_mychar[id].ch << std::endl;
	ofs << data->m_mychar[id].bg << std::endl;
	ofs << data->m_mychar[id].type << std::endl;
	ofs << data->m_mychar[id].status << std::endl;
	ofs << data->m_mychar[id].level << std::endl;
	ofs << data->m_mychar[id].exp << std::endl;
	ofs << data->m_mychar[id].hp.p << std::endl;
	ofs << data->m_mychar[id].hp.t << std::endl;
	ofs << data->m_mychar[id].hp.m << std::endl;
	ofs << data->m_mychar[id].sp.p << std::endl;
	ofs << data->m_mychar[id].sp.t << std::endl;
	ofs << data->m_mychar[id].sp.m << std::endl;
	ofs << data->m_mychar[id].ap.p << std::endl;
	ofs << data->m_mychar[id].ap.t << std::endl;
	ofs << data->m_mychar[id].ap.m << std::endl;
	ofs << data->m_mychar[id].gp.p << std::endl;
	ofs << data->m_mychar[id].gp.t << std::endl;
	ofs << data->m_mychar[id].gp.m << std::endl;
	ofs << data->m_mychar[id].mp.p << std::endl;
	ofs << data->m_mychar[id].mp.t << std::endl;
	ofs << data->m_mychar[id].mp.m << std::endl;
	ofs << data->m_mychar[id].ep.p << std::endl;
	ofs << data->m_mychar[id].ep.t << std::endl;
	ofs << data->m_mychar[id].ep.m << std::endl;
	ofs << data->m_mychar[id].fp.p << std::endl;
	ofs << data->m_mychar[id].fp.t << std::endl;
	ofs << data->m_mychar[id].fp.m << std::endl;
	ofs << data->m_mychar[id].dp.p << std::endl;
	ofs << data->m_mychar[id].dp.t << std::endl;
	ofs << data->m_mychar[id].dp.m << std::endl;
	ofs << data->m_mychar[id].rweapon << std::endl;
	ofs << data->m_mychar[id].lweapon << std::endl;
	ofs << data->m_mychar[id].helm << std::endl;
	ofs << data->m_mychar[id].armor << std::endl;
	ofs << data->m_mychar[id].mant << std::endl;
	ofs << data->m_mychar[id].boots << std::endl;
	ofs << data->m_mychar[id].equip << std::endl;
	ofs << data->m_mychar[id].food << std::endl;
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].magic[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].magicexp[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].fight[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].fightexp[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].skill[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		for (int j = 0; j < MAX_FIGHT; j++){
			ofs << data->m_mychar[id].skillexp[i][j] << std::endl;
		}
	}
	for (int i = 0; i < MAX_TYPE; i++){
		ofs << data->m_mychar[id].curse[i] << std::endl;
	}
	ofs << data->m_mychar[id].prof << std::endl;

	return(true);
}

int CFile::read_enemy(CData* data)
{
	return read_enemy(data, 0, 99999999);
}

int CFile::read_enemy(CData* data, const int index)
{
	return read_enemy(data, index, index);
}

int CFile::read_enemy(CData* data, const int from, const int to)
{
	std::string fname = zenkaku_home + "/system/enemy.dat";	// 敵キャラファイル
	Enemy tmp_enemy;

	std::fstream ifs(fname.c_str(), std::ios::in | std::ios::binary);	// バイナリファイル
	if( ifs.fail() )	return(FALSE);

	int count;
	for (int i = from, count = 0; i <= to; i++, count++)
	{
		ifs.seekg(i * ENEMYFILE_BLOCK, std::ios::beg);	// 頭出し
		ifs.read((char*) &tmp_enemy, sizeof(Enemy));		// 1ブロック読み出し
		if (ifs.eof())	return count;				// ファイルの最後まで到達

		data->m_enemy.push_back(tmp_enemy);			// data に格納
	}
	ifs.close();
	return count;		// 成功
}

// 敵キャラ情報書き出し（敵キャラエディタからしか呼ばれない前提）
// data->m_enemyのindexと、ファイル上のindexがずれているとファイルが壊れるので要注意
bool CFile::write_enemy(CData* data, const int index)
{
	std::string fname = zenkaku_home + "/system/enemy.dat";	// 敵キャラファイル
	std::fstream ofs(fname.c_str(), std::ios::out | std::ios::in | std::ios::binary);	// バイナリファイル
	if( ofs.fail() )	return(FALSE);

	if(ofs.seekp(index * ENEMYFILE_BLOCK, std::ios::beg))	// 頭出し
	{
		ofs.write(reinterpret_cast<char *>(&data->m_enemy[index]), sizeof(Enemy));

		// 予備用領域書き込み
		char tmp_char[ENEMYFILE_BLOCK - sizeof(Enemy)];
		ofs.write(reinterpret_cast<char *>(tmp_char), ENEMYFILE_BLOCK - sizeof(Enemy));
		ofs.close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
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
		fread( data->m_enemyparty.item_r,	sizeof(int),		ENEMY_ITEM, fp);
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
	fwrite( data->m_enemyparty.item_r,	sizeof(int),		ENEMY_ITEM, fp);
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

int CFile::read_item(CData* data)
{
	return read_item(data, 0, 99999999);
}

int CFile::read_item(CData* data, const int index)
{
	return read_item(data, index, index);
}

int CFile::read_item(CData* data, const int from, const int to)
{
	std::string fname = zenkaku_home + "/system/item.dat";	// アイテムファイル
	Item tmp_item;

	std::fstream ifs(fname.c_str(), std::ios::in | std::ios::binary);	// バイナリファイル
	if( ifs.fail() )	return(FALSE);

	int count;
	for (int i = from, count = 0; i <= to; i++, count++)
	{
		ifs.seekg(i * ITEMFILE_BLOCK, std::ios::beg);	// 頭出し
		ifs.read((char*) &tmp_item, sizeof(Item));	// 1ブロック読み出し
		if (ifs.eof())	return count;			// ファイルの最後まで到達

		data->m_item.push_back(tmp_item);		// data に格納
	}
	ifs.close();
	return count;		// 成功
}

bool CFile::write_item(CData* data, const int index)
{
	std::string fname = zenkaku_home + "/system/item.dat";	// アイテムファイル
	std::fstream ofs(fname.c_str(), std::ios::out | std::ios::in | std::ios::binary);	// バイナリファイル
	if( ofs.fail() )	return(FALSE);

	if(ofs.seekp(index * ITEMFILE_BLOCK, std::ios::beg))	// 頭出し
	{
		ofs.write(reinterpret_cast<char *>(&data->m_item[index]), sizeof(Item));

		// 予備用領域書き込み
		char tmp_char[ITEMFILE_BLOCK - sizeof(Item)];
		ofs.write(reinterpret_cast<char *>(tmp_char), ITEMFILE_BLOCK - sizeof(Item));
		ofs.close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
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
		std::cerr << "WARN:file003 get_map_size failure" << std::endl;
		return(size);
	}
	while (getline(ifs, str))
	{
		size.height++;
		if (CMyStr::length(str) > size.width)		size.width = CMyStr::length(str);
	}
	return(size);
}

int CFile::read_map(const std::string fname, MapData* mapdata, PosData* posdata, PosData* spposdata, TileData* tiledata, PosEvent* pevent, PosEvent* sevent, std::string* fieldname)
{
	FILE*	fp;
	std::string fname_t = fname + ".txt";	// マップファイル
	std::string fname_b = fname + ".bin";	// タイルファイル
	std::string tmp_cs;
	int	i, j, k, num = 0, flg;

	std::ifstream ifs(fname_b.c_str(), std::ios::binary);
	if( ifs.fail() )
	{ // タイルファイルなし マップから新規作成
		std::ifstream ifs(fname_t.c_str());
		if( ifs.fail() )	return 0;	// タイルもマップもなし

		k = 0;
		while (std::getline(ifs, tmp_cs))
		{ // 行単位ループ
			std::vector< std::string > tmp_csvect;
			tmp_csvect = CMyStr::separate(tmp_cs);
			for(i = 0; i < tmp_csvect.size(); i++)
			{ // 文字単位ループ
				flg = false;
				for(j = 0; j < num; j++)
				{ // 既に読んだ文字と比較
					if (tmp_csvect[i] == tiledata[j].tile)
					{ // 既に登録があった
						posdata[k * mapdata->width + i].falseid = j;
						flg = true;
						break;
					}
				}
				if (!flg)
				{	// 登録がなかった
					tiledata[num].tile	= tmp_csvect[i];
					tiledata[num].ch	= 7;
					tiledata[num].bg	= 0;
					tiledata[num].attr	= 0;
					tiledata[num].height	= 50;
					tiledata[num].move	= 0;

					// ポジションデータ保存
					posdata[k * mapdata->width + i].falseid = num;
					num++;
				}
				posdata[k * mapdata->width + i].flg     = 0;
				posdata[k * mapdata->width + i].trueid  = 0;
				posdata[k * mapdata->width + i].name    = 0;
				posdata[k * mapdata->width + i].enemy   = 0;
				posdata[k * mapdata->width + i].encount = 10;

				// PADに描画
				//wattrset(map, COLOR_PAIR(0));
				//mvwaddstr(map, k, i, CMyStr::substr(tmp_csvect[i], i, 1));
				
				k++;
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
		ifs.read( (char*)&mapdata, sizeof( MapData ) );
		ifs.read( (char*)posdata, sizeof( PosData ) * mapdata->height * mapdata->width );
		ifs.read( (char*)spposdata, sizeof( PosData ) * MAX_SPPOS );
		ifs.read( (char*)&num,    sizeof( int ) );
		
		for (int i = 0; i < num; i++)
		{
			ifs.read( (char*)&tiledata[i],  sizeof(TileData));
		}
		ifs.read( (char*)pevent,    sizeof( PosEvent ) * MAX_MAPEVENT );
		ifs.read( (char*)sevent,    sizeof( PosEvent ) * MAX_MAPEVENT );

		char tmp_buf[1024];
		ifs.read( (char*)tmp_buf, sizeof( char ) * MAX_FNAME );
		for (int i = 0; i < MAX_FNAME; i++)
		{
			for (int j = 0; j < 1024; j++)
			{
				if (tmp_buf[j] == ':')
				{
					tmp_buf[j] = 0;
					fieldname[i] = std::string(tmp_buf);
					break;
				}
			}
		}
	}

	return(num);	// タイルの数を返す

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


