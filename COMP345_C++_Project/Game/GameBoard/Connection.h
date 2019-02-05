#pragma once
#include <memory>
#include <string>
class Connection
{
public:
	Connection(std::string firstCity,
		std::string secondCity, int cost);
	~Connection();

    std::string getFirst() const { return m_first; }
	std::string getSecond() const  { return m_second; }
	int getCost() { return m_cost; }

private:
	std::string m_first;
	std::string m_second;
	int m_cost;
};