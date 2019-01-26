#include "Map.h"

Map::Map() 
{

}

Map::~Map()
{
}

void Map::setCity(int type, int cityNumber)
{
	//create the region and add it to the vector
	std::shared_ptr<City> region = std::make_shared<City>(type, cityNumber);
	m_cities.push_back(region);
}

void Map::setRegionCoords(int cityNumber, float x, float y)
{
	m_cities[cityNumber]->m_xPos = x;
	m_cities[cityNumber]->m_yPos = y;
}

void Map::addEdge(int city1, int city2)
{
	m_edges[city1][city2] = 1;
	m_edges[city2][city1] = 1;
}

Map::City::City(int type, int regionNumber) : m_regionType(type), m_cityNumber(regionNumber),
m_xPos(0.0f), m_yPos(0.0f), m_isOwned(false)
{

}

Map::City::~City()
{
}
