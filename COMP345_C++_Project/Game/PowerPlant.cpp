#include "PowerPlant.h"

PowerPlant::PowerPlant(CardType cardType, GridResourceType resourceType, int plantNumber, int numOfHouse, int numOfResources) : Card(cardType),
m_resourceType(resourceType), m_plantNumber(plantNumber), m_numOfHouses(numOfHouse), m_numOfResources(numOfResources)
{

}

PowerPlant::~PowerPlant()
{
}
