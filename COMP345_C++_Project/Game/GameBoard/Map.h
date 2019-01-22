#pragma once
#include "RegionTypes.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class Map
{
public:
	Map();
	~Map();


private:

	struct Region {
		Region(std::string name, Regions type, float x, float y);
		~Region();


		Regions m_regionType;
		sf::Sprite m_tokenSprite;
		float m_xPos, m_yPos;
		bool m_isOwned;
	};

	std::vector<std::unique_ptr<Regions>> m_regions;
};