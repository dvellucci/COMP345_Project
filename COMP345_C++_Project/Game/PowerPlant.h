#pragma once
#include "Card.h"

class PowerPlant : public Card
{
public:
	PowerPlant(CardType cardType, GridResourceType resourceType, int minimalBid, int numOfHouse, int numOfResources);
	~PowerPlant();

	int getPlantNumber() { return m_plantNumber; }

private:
	CardType m_cardType;
	GridResourceType m_resourceType;
	int m_plantNumber;
	int m_numOfHouses;
	int m_numOfResources;

};