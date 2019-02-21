#include "PowerPlant.h"

PowerPlant::PowerPlant(CardType cardType, int price, int numOfHouse, int capacity) : Card(cardType),
m_price(price), m_numOfHouses(numOfHouse), m_capacity(capacity)
{
	
}

PowerPlant::~PowerPlant()
{
}

bool PowerPlant::storeResource(GridResourceType type, int amount)
{
	//check if the resource is allowed or if its at max capacity
	if(m_validResources.find(type) == m_validResources.end())
		return false;

	m_storedResources.insert(std::make_pair(type, amount));

	return true;
}

std::string PowerPlant::getResourceTypeName(GridResourceType type)
{
	if (type == GridResourceType::Coal)
		return "Coal";
	else if (type == GridResourceType::Oil)
		return "Oil";
	else if (type == GridResourceType::Garbage)
		return "Garbage";
	else if (type == GridResourceType::Uranium)
		return "Uranium";
	else if (type == GridResourceType::No_Resource)
		return "No resource";

	return "";
}

int PowerPlant::getNumOfPlacedResources()
{
	int total = 0;
	for (auto iterator = m_storedResources.begin(); iterator != m_storedResources.end(); iterator++)
		total += iterator->second;
	return total;
}
