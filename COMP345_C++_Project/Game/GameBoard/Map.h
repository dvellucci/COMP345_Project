#pragma once
#include "RegionTypes.h"
#include "../Player.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <list>

#define EDGES 50
class Map
{
public:

	Map();
	~Map();

	struct Region {
		Region(int type, float x, float y);
		~Region();

		int m_regionType;
		float m_xPos, m_yPos;
		bool m_isOwned;

		std::shared_ptr<Player> player;
		sf::Sprite m_tokenSprite;
	};

	void setRegion(int type);
	void setRegionCoords(int regionNumber, float x, float y);
	void addEdge(int count, int val);

	std::vector<std::shared_ptr<Region>> getRegions() { return m_regions; }

private:
	std::vector<std::shared_ptr<Region>> m_regions;
	//this keeps track of the edges between regions that are connected
	int m_edges[EDGES][EDGES] = { 0 };
};