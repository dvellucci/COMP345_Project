#pragma once
#include "Map.h"
#include "Connection.h"
#include <vector>
#include <fstream>
#include <iostream>

#define EDGES 100

class MapManager
{
public:
	MapManager();
	~MapManager();

	Map loadMap(std::string filename);
	void loadCityCoords(std::string filename);

private:
	Map m_map;
	std::vector<std::list<std::shared_ptr<Connection>>> m_connections;
	std::shared_ptr<Connection> connections[EDGES][EDGES];
};