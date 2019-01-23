#include "Map.h"

Map::Map() 
{

}

Map::~Map()
{
}

void Map::setRegion(int type)
{
	//create the region and add it to the vector
	std::shared_ptr<Region> region = std::make_shared<Region>(type, 0.f, 0.f);
	m_regions.push_back(region);
}

void Map::setRegionCoords(int regionNumber, float x, float y)
{
	m_regions[regionNumber]->m_xPos = x;
	m_regions[regionNumber]->m_yPos = y;
}

void Map::addEdge(int region1, int region2)
{
	m_edges[region1][region2] = 1;
	m_edges[region2][region1] = 1;
}

Map::Region::Region(int type, float x, float y) : m_regionType(type), m_xPos(x), m_yPos(y)
{

}

Map::Region::~Region()
{
}
