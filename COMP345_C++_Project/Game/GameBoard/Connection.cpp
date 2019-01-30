#include "Connection.h"

Connection::Connection(std::string firstCity, std::string secondCity, int cost) : m_first(firstCity), 
m_second(secondCity), m_cost(cost)
{
}

Connection::~Connection()
{
}
