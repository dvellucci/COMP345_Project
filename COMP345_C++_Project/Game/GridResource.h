#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>
#include <algorithm>

enum GridResourceType
{
	Coal,
	Oil,
	Garbage,
	Uranium
};


class GridResource
{
public:
	GridResource(GridResourceType resourceType, bool isAvailable, int cost);
	~GridResource();

	void setResourceSprite();

	GridResourceType getResourceTypeByName(std::string name);
	bool getIsAvailable() { return m_isAvailable; }
	sf::Sprite& getResourceSprite() { return m_resourceSprite; }

private:
	sf::Sprite m_resourceSprite;
	GridResourceType m_resourceType;
	bool m_isAvailable;
	int m_cost;
	float m_xPos;
	float m_yPos;
};