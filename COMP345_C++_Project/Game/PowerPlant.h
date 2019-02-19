#pragma once
#include "Card.h"
#include "GridResourceMarket.h"
#include <set>

class PowerPlant : public Card
{
public:
	PowerPlant(CardType cardType, GridResourceType type1, GridResourceType type2, int price, int numOfHouse, int capacity);
	~PowerPlant();

	bool storeResource(GridResourceType type, int amount);
	GridResourceType getResourceType1() { return m_resourceType; }
	GridResourceType getResourceType2() { return m_resourceType2; }
	std::string getResourceTypeName(GridResourceType type);
	int getPowerPlantPrice() { return m_price; }
	int getPowerPlantCapacity() { return m_capacity; }
	int getPowerPlantHouses() { return m_numOfHouses; }

private:
	CardType m_cardType;
	GridResourceType m_resourceType;
	GridResourceType m_resourceType2;
	std::set<GridResourceType> m_validResources;
	//resources stored by the power plant
	std::map<GridResourceType, int> m_storedResources; 
	int m_price;
	int m_numOfHouses;
	int m_capacity;
};