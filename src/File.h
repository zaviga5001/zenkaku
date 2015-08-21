#ifndef CFILE_H
#define CFILE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

#include "Config.h"
#include "win.h"

class CFile
{
public:
	CFile();
	virtual ~CFile();

	void	read_cfg(const std::string fname, CConfig* config);

	int	read_mychar(CData* data);
	bool	write_mychar(CData* data);

	int	read_enemy(CData* data, const int index);
	bool	write_enemy(CData* data, const int index);

	int	read_party(CData* data, const int index);
	bool	write_party(CData* data, const int index);

	int	read_pg(CData* data, const int index);
	bool	write_pg(CData* data, const int index);

	bool	read_event(CData* data);
	bool	write_event(CData* data, const int index);

	bool	read_item(CData* data);
	bool	write_item(CData* data);

	bool	read_shop(CData* data, const int index);
	bool	write_shop(CData* data, const int index);

	bool	read_mess(CData* data);
	bool	write_mess(CData* data);

	MapData	get_map_size(const std::string fname);
	int	read_map(const std::string fname, MapData* mapdata, PosData* posdata, PosData* spposdata, TileData* tiledata, PosEvent* pevent, PosEvent* sevent, std::string* fieldname);
	bool	write_map(const std::string fname, MapData* mapdata, PosData* posdata, PosData* spposdata, TileData* tiledata, PosEvent* pevent, PosEvent* sevent, std::string* fieldname, int tilenum);

	ScnList	read_scenario_list(const std::string fname);

	std::string	input_path_dialog();

protected:
	void	mychop(std::string& cs);
	//void	readcsv(const std::string cs, CList<int>* cl);

private:

};
#endif // CFILE_H
