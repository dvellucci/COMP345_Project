#pragma once
#include <memory>
#include "Map.h"
class Connection
{
public:
	Connection(std::string firstCity,
		std::string secondCity, int cost);
	~Connection();

	std::string& getFirst() { return m_first; }
	std::string& getSecond() { return m_second; }
	int getCost() { return m_cost; }

private:
	std::string m_first;
	std::string m_second;
	int m_cost;
};