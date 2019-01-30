#include "Map.h"

Map::Map() 
{

}

Map::~Map()
{
}

void Map::setMapSprite()
{
	m_mapSprite.setTexture(ResourceHolder::Instance()->get(Textures::Map));
}

void Map::setCity(std::string cityName)
{
	//create the region and add it to the vector
	std::shared_ptr<City> city = std::make_shared<City>(cityName);

	std::shared_ptr<City::CitySlot> slot1 = std::make_shared<City::CitySlot>(10);
	std::shared_ptr<City::CitySlot> slot2 = std::make_shared<City::CitySlot>(15);
	std::shared_ptr<City::CitySlot> slot3 = std::make_shared<City::CitySlot>(20);

	city->citySlots[0] = slot1;
	city->citySlots[1] = slot2;
	city->citySlots[2] = slot3;

	m_cities.push_back(city);
}

void Map::setRegionCoords(int cityNumber, float x, float y)
{

}

void Map::addEdge(int city1, int city2)
{
	m_edges[city1][city2] = 1;
	m_edges[city2][city1] = 1;
}

Map::City::City(std::string cityName) 
{
	m_cityName = cityName;
}

Map::City::~City()
{
}
