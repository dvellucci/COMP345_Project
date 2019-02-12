#include "PowerPlant.h"

PowerPlant::PowerPlant(CardType cardType, GridResourceType resourceType, int price, int numOfHouse, int capacity) : Card(cardType),
m_resourceType(resourceType), m_price(price), m_numOfHouses(numOfHouse), m_capacity(capacity)
{

}

PowerPlant::~PowerPlant()
{
}
