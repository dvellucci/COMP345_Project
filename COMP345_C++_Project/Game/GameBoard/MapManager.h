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
#include <algorithm>

#define EDGES 100

// Status
const int UNVISITED = 0;
const int VISITING = 1;
const int VISITED = 2;

class MapManager
{
public:
	MapManager();
	~MapManager();

	std::shared_ptr<Map> loadMap(std::string filename);
	void setConnection(std::string city1, std::string city2, int cost);

	//functions to check for a connected map
	bool isMapValid(std::map<std::string, std::list<std::string>> m_mapGraph, std::string node);
	std::list<std::string> depthFirstSearch(std::map<std::string, std::list<std::string>> m_mapGraph, std::string node);

	std::shared_ptr<Map>& getMap() { return m_map; }
	std::map<std::string, std::list<std::string>>& getMapGraph() { return m_mapGraph; }
	std::vector<std::shared_ptr<Connection>> getConnections() { return m_connections; }
	std::vector<std::string> getAvailableMaps() { return m_avaliableMaps; }

	int getShortestPath(std::string fromCity, std::string toCity);
	int getShortestPathFromPlayer(std::shared_ptr<Player> player, std::string toCity);

	//object to create a city with it's cost to be used for comparisons
	class  CityComparable 
	{
	public:
		CityComparable(std::shared_ptr<Map::City> city) : city(city) {};
		int cost = std::numeric_limits<int>::max();
		int visited = UNVISITED;
		std::string parent;
		std::shared_ptr<Map::City> city;
	};

	//operator overloader to compare to cities by the cost to get there
	struct CityCostComparator {
		bool operator()(const std::shared_ptr<CityComparable> city1, const std::shared_ptr<CityComparable> city2) const 
		{
			return city1->cost > city2->cost;
		}
	};

private:

	std::shared_ptr<Map> m_map;
	//m_mapGraph is used to check if the map is strongly connected after loading
	std::map<std::string, std::list<std::string>> m_mapGraph;
	//stores the connections between 2 cities
	std::vector<std::shared_ptr<Connection>> m_connections;

	std::list<std::string> m_discoveredNodes;

	std::vector<std::string> m_avaliableMaps = { "Turkey", "China", "turkey-unconnected", "bad-map" };
};