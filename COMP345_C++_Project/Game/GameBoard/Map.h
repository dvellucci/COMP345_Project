#pragma once
#include "../ResourceHolder.h"
#include "Connection.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#define SLOTS 3
class Map
{
public:

	Map();
	~Map();

	struct City {
		City(std::string cityName) : m_cityName(cityName) {};
		~City() {};

		std::string m_cityName;

		struct CitySlot {
		public:
			CitySlot(int type, std::string name) : m_cost(type), m_name(name) { };
			~CitySlot() {};
		
			void setIsOwned(bool owned) { m_isOwned = owned; }
			int getCost() { return m_cost; }
			bool getIsOwned() { return m_isOwned; }
			std::string getName() { return m_name; }
			sf::Sprite& getSlotSprite() { return m_slotSprite; }

			sf::Sprite m_slotSprite;
		private:
			int m_cost;
			std::string m_name;
			bool m_isOwned = false;
		};

		std::shared_ptr<CitySlot> citySlots[SLOTS];
		std::vector<std::shared_ptr<Connection>> m_connections;

		std::vector<std::shared_ptr<Connection>>& getConnections() { return m_connections; }
	};

	void displayCities();
	void setMapSprite();

	//creates a city object and initializes the 3 slots of the city
	std::shared_ptr<Map::City> setCity(std::string m_cityName, float x1, float y1, float x2, float y2, float x3, float y3);

	std::map<std::string, std::shared_ptr<City>>& getCities() { return m_cities; }
	std::shared_ptr<City> getCityByName(std::string name);
	sf::Sprite& getMapSprite() { return m_mapSprite; }
	sf::Text& getCityText() { return m_cityText; }

	std::string getOppositeOf(const Connection& connection, std::string city);

private:
	std::map<std::string, std::shared_ptr<City>> m_cities;
	sf::Sprite m_mapSprite;
	sf::Text m_cityText;
};