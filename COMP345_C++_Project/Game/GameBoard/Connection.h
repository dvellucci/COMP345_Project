#pragma once
#include <memory>
#include "Map.h"
class Connection
{
public:
	Connection();
	Connection(std::shared_ptr<Map::City> firstCity,
		std::shared_ptr<Map::City> secondCity, int cost);
	~Connection();

private:
	std::shared_ptr<Map::City> m_first;
	std::shared_ptr<Map::City> m_second;
	int m_cost;
};