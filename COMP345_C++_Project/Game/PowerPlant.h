#pragma once
#include "Card.h"
#include "GridResourceMarket.h"
#include <set>

class PowerPlant : public Card
{
public:
	PowerPlant(CardType cardType, int price, int numOfHouse, int capacity);
	~PowerPlant();
	
	void setValidResource(GridResourceType type) { m_validResources.insert(type); }

	bool storeResource(GridResourceType type, int amount);
	std::string getResourceTypeName(GridResourceType type);
	int getPowerPlantPrice() { return m_price; }
	int getPowerPlantCapacity() { return m_capacity; }
	int getPowerPlantHouses() { return m_numOfHouses; }
	int getNumOfPlacedResources();
	std::set<GridResourceType> getValidResources() { return m_validResources; }

private:
	CardType m_cardType;
	std::set<GridResourceType> m_validResources;
	//resources stored by the power plant
	std::map<GridResourceType, int> m_storedResources; 
	int m_price;
	int m_numOfHouses;
	int m_capacity;
};