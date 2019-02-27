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
	std::vector<GridResourceType>::iterator it = std::find(m_validResources.begin(), m_validResources.end(), type);
	if (it == m_validResources.end())
		return false;

	auto resourceType = m_storedResources.find(type);
	if (resourceType != m_storedResources.end())
		m_storedResources.at(type) += amount;
	else
		m_storedResources.insert(std::make_pair(type, amount));

	return true;
}

bool PowerPlant::consumeResource(GridResourceType type, int amount)
{
	if (m_storedResources.empty())
		return false;

	//if the powerplant does not have enough of a resource
	if (m_storedResources.at(type) - amount < 0)
		return false;

	m_storedResources.at(type) -= amount;
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

int PowerPlant::getNumOfPlacedResourcesByType(GridResourceType type)
{
	auto resourceType = m_storedResources.find(type);
	if (resourceType != m_storedResources.end())
		return m_storedResources.at(type);

	return 0;
}
