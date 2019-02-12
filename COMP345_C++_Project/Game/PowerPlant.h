#pragma once
#include "Card.h"
#include "GridResourceMarket.h"

class PowerPlant : public Card
{
public:
	PowerPlant(CardType cardType, GridResourceType resourceType, int price, int numOfHouse, int capacity);
	~PowerPlant();

	int getPowerPlantPrice() { return m_price; }

private:
	CardType m_cardType;
	GridResourceType m_resourceType;
	//resources stored by the power plant
	std::map<GridResourceType, int> m_storedResources; 
	int m_price;
	int m_numOfHouses;
	int m_capacity;

};