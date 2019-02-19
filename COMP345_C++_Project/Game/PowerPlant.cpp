#include "PowerPlant.h"

PowerPlant::PowerPlant(CardType cardType, GridResourceType type1, GridResourceType type2, int price, int numOfHouse, int capacity) : Card(cardType),
m_resourceType(type1), m_resourceType2(type2), m_price(price), m_numOfHouses(numOfHouse), m_capacity(capacity)
{
	m_validResources.insert(type1);
	if (type1 != type2)
		m_validResources.insert(type2);
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
