#include "Deck.h"

Deck::Deck()
{
	m_deck.reserve(43);
}

Deck::~Deck()
{
	//clear the deck when the game is exited
	for (auto* card : m_deck)
		delete card;
	m_deck.clear();
}

void Deck::setUpDeck()
{
	//initialize power plant cards and place them in the deck (3 is plant price, 1 is number of houses it powers, 2 is number of resources it stores)
	m_deck.emplace_back(new PowerPlant(CardType::Power_Plant, GridResourceType::Oil, 3, 1, 2));
	m_deck.emplace_back(new PowerPlant(CardType::Power_Plant, GridResourceType::Coal, 4, 1, 2));
	m_deck.emplace_back(new StepCard(CardType::Step_3));
}

void Deck::shuffle(std::vector<std::shared_ptr<Card>>& m_deck)
{
	
}
 
std::shared_ptr<PowerPlant> Deck::getPowerPlantByNumber(int n)
{
	return std::shared_ptr<PowerPlant>();
}
