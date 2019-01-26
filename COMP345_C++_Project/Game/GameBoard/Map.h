#pragma once
#include "RegionTypes.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <list>

#define EDGES 100
#define SLOTS 3
class Map
{
public:

	Map();
	~Map();

	struct City {
		City(int type, int regionNumber);
		~City();

		int m_regionType;
		int m_cityNumber;
		float m_xPos, m_yPos;
		bool m_isOwned;
		std::unique_ptr<sf::Sprite> m_tokenSprite;

		struct CitySlot {
			CitySlot() {};
			~CitySlot() {};

			int type;
			float xPos, yPos;
			std::unique_ptr<sf::Sprite> slotSprite;
		};

		CitySlot citySlots[SLOTS];
	};

	void setCity(int type, int regionNumber);
	void setRegionCoords(int regionNumber, float x, float y);
	void addEdge(int count, int val);

	std::vector<std::shared_ptr<City>>& getCities() { return m_cities; }

private:
	std::vector<std::shared_ptr<City>> m_cities;
	//this keeps track of the edges between regions that are connected
	int m_edges[EDGES][EDGES] = { 0 };
	sf::Sprite m_mapSprite;
};