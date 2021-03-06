#include "Map.h"

Map::Map() 
{
	m_cityText.setFont(ResourceHolder::Instance()->get(Fonts::Default));
	m_cityText.setFillColor(sf::Color::Black);
	m_cityText.setPosition(250.0f, 150.0f);
	m_cityText.setStyle(sf::Text::Bold);
}

Map::~Map()
{
}

void Map::setMapSprite()
{
	m_mapSprite.setTexture(ResourceHolder::Instance()->get(Textures::Map));
}

std::shared_ptr<Map::City>  Map::setCity(std::string m_cityName, float x1, float y1, float x2, float y2, float x3, float y3)
{
	//create the region and add it to the vector
	std::shared_ptr<City> city = std::make_shared<City>(m_cityName);

	std::shared_ptr<City::CitySlot> slot1 = std::make_shared<City::CitySlot>(10, m_cityName);
	std::shared_ptr<City::CitySlot> slot2 = std::make_shared<City::CitySlot>(15, m_cityName);
	std::shared_ptr<City::CitySlot> slot3 = std::make_shared<City::CitySlot>(20, m_cityName);

	city->citySlots[0] = slot1;
	city->citySlots[1] = slot2;
	city->citySlots[2] = slot3;

	//set city slot coordinates
	city->citySlots[0]->getSlotSprite().setPosition(x1, y1);
	city->citySlots[0]->getSlotSprite().setTexture(ResourceHolder::Instance()->get(Textures::Default));
	city->citySlots[1]->getSlotSprite().setPosition(x2, y2);
	city->citySlots[1]->getSlotSprite().setTexture(ResourceHolder::Instance()->get(Textures::Default));
	city->citySlots[2]->getSlotSprite().setPosition(x3, y3);
	city->citySlots[2]->getSlotSprite().setTexture(ResourceHolder::Instance()->get(Textures::Default));

	m_cities.emplace(make_pair(m_cityName, city));

	return city;
}

void Map::displayCities()
{

}

std::shared_ptr<Map::City> Map::getCityByName(std::string name)
{
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	return m_cities.at(name);
}

std::string Map::getOppositeOf(const Connection & connection, std::string city)
{
	if (connection.getFirst() == city)
		return connection.getSecond();
	if (connection.getSecond() == city)
		return connection.getFirst();

	return nullptr;
}
