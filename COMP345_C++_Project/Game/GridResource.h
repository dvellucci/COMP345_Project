#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cctype>
#include <algorithm>

enum GridResourceType
{
	Coal = 0,
	Oil = 1,
	Garbage = 2,
	Uranium = 3,
	No_Resource = 4,
};


class GridResource
{
public:
	GridResource(GridResourceType resourceType, bool isAvailable, int cost);
	~GridResource();

	void setResourceSprite();
	void setAvailability(bool available) { m_isAvailable = available; }

	int getCost() { return m_cost; }
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