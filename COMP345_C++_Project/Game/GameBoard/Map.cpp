#include "Map.h"

Map::Map() 
{
	m_cityText.setFont(ResourceHolder::Instance()->get(Fonts::Default));
	m_cityText.setFillColor(sf::Color::Black);
	m_cityText.setPosition(250.0f, 30.0f);
}

Map::~Map()
{
}

void Map::setMapSprite()
{
	m_mapSprite.setTexture(ResourceHolder::Instance()->get(Textures::Map));
}

void Map::setCity(std::string m_cityName, float x1, float y1, float x2, float y2, float x3, float y3)
{
	//create the region and add it to the vector
	std::shared_ptr<City> city = std::make_shared<City>(m_cityName);

	std::shared_ptr<City::CitySlot> slot1 = std::make_shared<City::CitySlot>(10, m_cityName);
	std::shared_ptr<City::CitySlot> slot2 = std::make_shared<City::CitySlot>(15, m_cityName);
	std::shared_ptr<City::CitySlot> slot3 = std::make_shared<City::CitySlot>(20, m_cityName);

	city->citySlots[0] = slot1;
	city->citySlots[1] = slot2;
	city->citySlots[2] = slot3;

	//set city slot coords
	city->citySlots[0]->m_slotSprite.setPosition(x1, y1);
	city->citySlots[0]->m_slotSprite.setTexture(ResourceHolder::Instance()->get(Textures::Default));
	city->citySlots[1]->m_slotSprite.setPosition(x2, y2);
	city->citySlots[2]->m_slotSprite.setPosition(x3, y3);

	m_cities.push_back(city);
}

void Map::addEdge(int city1, int city2)
{
	m_edges[city1][city2] = 1;
	m_edges[city2][city1] = 1;
}

Map::City::City(std::string m_cityName) 
{
	m_cityName = m_cityName;
}

Map::City::~City()
{
}
