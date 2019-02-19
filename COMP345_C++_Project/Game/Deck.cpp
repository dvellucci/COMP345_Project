#include "Deck.h"

Deck::Deck()
{
	m_deck.reserve(43);
}

Deck::~Deck()
{
	
}

void Deck::setUpDeck()
{
	//place the step 3 card at the bottom
	//m_deck.emplace_back(std::make_shared<StepCard>(CardType::Step_3));
	//initialize power plant cards and place them in the deck (first number is price, second is houses it powers, third is resource capacity)
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Oil, GridResourceType::No_Resource, 3, 1, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::No_Resource, 4, 1, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::Oil, 5, 1, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Garbage, GridResourceType::No_Resource, 6, 1, 2));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Oil, GridResourceType::No_Resource, 7, 2, 6));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::No_Resource, 8, 2, 6));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Garbage, GridResourceType::No_Resource, 9, 1, 2));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::No_Resource, 10, 2, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Uranium, GridResourceType::No_Resource, 11, 2, 2));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::Oil, 12, 2, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::No_Resource, GridResourceType::No_Resource, 13, 1, 0));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Garbage, GridResourceType::No_Resource, 14, 2, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::No_Resource, 15, 3, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Oil, GridResourceType::No_Resource, 16, 3, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Uranium, GridResourceType::No_Resource, 17, 2, 2));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::No_Resource, GridResourceType::No_Resource, 18, 2, 0));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Garbage, GridResourceType::No_Resource, 19, 3, 4));
	m_deck.emplace_back(std::make_shared<PowerPlant>(CardType::Power_Plant, GridResourceType::Coal, GridResourceType::No_Resource, 20, 5, 6));


	setUpMarket();
}

void Deck::setUpMarket()
{
	for (int i = 0; i < POWER_PLANT_MARKET; i++)
	{
		std::shared_ptr<Card> top = m_deck[0];
		m_powerPlantMarket.push_back(top);
		m_deck.erase(m_deck.begin());
	}
}

void Deck::outputMarket()
{
	int i = 0;
	for (auto& plant : m_powerPlantMarket)
	{
		auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(plant);
		std::cout << i << ". ";
		outputPowerPlant(powerPlant);
		i++;
	}
	std::cout << std::endl;
}

void Deck::outputPowerPlant(std::shared_ptr<PowerPlant> plant)
{
	std::cout << "Resources needed: " << plant->getResourceTypeName(plant->getResourceType1());
	if (plant->getResourceType2() != GridResourceType::No_Resource)
		std::cout << ", " << plant->getResourceTypeName(plant->getResourceType2()) << ". ";
	else
		std::cout << ". ";
	std::cout << "Minimum Price: " << plant->getPowerPlantPrice() << ". Houses: " << plant->getPowerPlantHouses() << ". ";
	std::cout << "Storage Capacity: " << plant->getPowerPlantCapacity() << std::endl; 
}

void Deck::shuffle(std::vector<std::shared_ptr<Card>>& m_deck)
{
	
}

void Deck::removePlantFromMarket(int index)
{
	m_powerPlantMarket.erase(m_powerPlantMarket.begin() + index);
}

//draw a card and at it to the power plant market
bool Deck::drawCard()
{
	std::shared_ptr<PowerPlant> powerPlant = nullptr;
	if (m_powerPlantMarket.size() < POWER_PLANT_MARKET && m_deck.size() > 0)
	{
		std::shared_ptr<Card> topCard = m_deck[0];

		m_powerPlantMarket.push_back(topCard);
		m_deck.erase(m_deck.begin());

		//sort the power plants
		std::sort(m_powerPlantMarket.begin(), m_powerPlantMarket.end(), PowerPlantPrice());

		//TODO FOR LATER: Check for step 3 card

		return true;
	}
	return false;
}


std::shared_ptr<PowerPlant> Deck::getPowerPlantCard(int index)
{
	return std::dynamic_pointer_cast<PowerPlant>(m_powerPlantMarket[index]);
}
