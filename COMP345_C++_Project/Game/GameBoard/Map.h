#pragma once
#include "../ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#define EDGES 100
#define SLOTS 3
class Map
{
public:

	Map();
	~Map();

	struct City {
		City(std::string cityName);
		~City();

		std::string m_cityName;
		std::unique_ptr<sf::Sprite> m_tokenSprite;

		struct CitySlot {
			CitySlot(int type) { m_type = type; };
			~CitySlot() {};

			int m_type;
			float xPos, yPos;
			bool m_isOwned = false;
			sf::Sprite m_slotSprite;
		};

		std::shared_ptr<CitySlot> citySlots[SLOTS];
	};

	void setMapSprite();
	void setCity(std::string cityName);
	void setRegionCoords(int regionNumber, float x, float y);
	void addEdge(int count, int val);

	std::vector<std::shared_ptr<City>>& getCities() { return m_cities; }
	sf::Sprite& getMapSprite() { return m_mapSprite; }

private:
	std::vector<std::shared_ptr<City>> m_cities;
	std::map<std::string, std::list<std::string>> m_mapGraph;
	//this keeps track of the edges between regions that are connected
	int m_edges[EDGES][EDGES] = { 0 };
	sf::Sprite m_mapSprite;
};