#pragma once
#include "Card.h"
#include <set>
#include <vector>
#include <map>

class PowerPlant : public Card
{
public:
	PowerPlant() {};
	PowerPlant(CardType cardType, int price, int numOfHouse, int capacity);
	~PowerPlant();
	
	void setValidResource(GridResourceType type) { m_validResources.push_back(type); }
	std::vector<GridResourceType> getValidResources() { return m_validResources; }

	std::string getResourceTypeName(GridResourceType type);
	bool storeResource(GridResourceType type, int amount);
	bool consumeResource(GridResourceType type, int amount);
	int getPowerPlantPrice() { return m_price; }
	int getPowerPlantCapacity() { return m_capacity; }
	int getPowerPlantHouses() { return m_numOfHouses; }
	int getNumOfPlacedResources();
	int getNumOfPlacedResourcesByType(GridResourceType type);

	std::map<GridResourceType, int>& getStoredResources() { return m_storedResources; }

private:
	CardType m_cardType;
	std::vector<GridResourceType> m_validResources;
	//resources stored by the power plant
	std::map<GridResourceType, int> m_storedResources; 
	int m_price;
	int m_numOfHouses;
	int m_capacity;
};