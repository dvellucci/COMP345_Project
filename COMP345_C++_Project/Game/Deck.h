#pragma once
#include "Card.h"
#include "PowerPlant.h"
#include <vector>
#include <memory>

class Deck
{
public:
	Deck();
	~Deck();
	
	void setUpDeck();
	void shuffle(std::vector<std::shared_ptr<Card>>& m_deck);
	std::shared_ptr<PowerPlant> getPowerPlantByNumber(int n);

private:

	std::vector<Card*> m_deck;
};