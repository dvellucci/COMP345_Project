#pragma once
#include "Map.h"
#include "../Player.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <exception>
#include <set>
#include <stack>
#include <queue>

#define EDGES 100

class MapManager
{
public:
	MapManager();
	~MapManager();

	std::shared_ptr<Map> loadMap(std::string filename);
	void setConnection(std::string city1, std::string city2, int cost);
	void DFSUtil(std::string city, std::set<std::string> set);

	std::shared_ptr<Map>& getMap() { return m_map; }
	std::map<std::string, std::list<std::string>> getMapGraph() { return m_mapGraph; }
	std::vector<std::shared_ptr<Connection>> getConnections() { return m_connections; }
	std::vector<std::string> getAvailableMaps() { return m_avaliableMaps; }

	int getShortestPath(std::string fromCity, std::string toCity);
	int getShortestPathFromPlayer(std::shared_ptr<Player> player, std::string toCity);

private:
	std::shared_ptr<Map> m_map;
	//m_mapGraph is used to check if the map is strongly connected after loading
	std::map<std::string, std::list<std::string>> m_mapGraph;
	std::vector<std::list<std::string>> graph;
	//stores the connections between 2 cities
	std::vector<std::shared_ptr<Connection>> m_connections;

	std::vector<std::string> m_avaliableMaps = { "Turkey", "China" };
};