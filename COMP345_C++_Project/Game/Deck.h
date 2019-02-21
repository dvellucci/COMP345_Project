#pragma once
#include "Card.h"
#include "PowerPlant.h"
#include "StepCard.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

#define POWER_PLANT_MARKET 8

class Deck
{
public:
	Deck();
	~Deck();
	
	void setUpDeck(std::string filename);
	void setUpMarket();
	void outputMarket();
	void outputPowerPlant(std::shared_ptr<PowerPlant> plant);
	void shuffle(std::vector<std::shared_ptr<Card>>& m_deck);

	void removePlantFromMarket(int index);
	bool drawCard();

	std::vector<std::shared_ptr<Card>>& getDeck() { return m_deck; }
	std::vector<std::shared_ptr<Card>>& getPowerPlantMarket() { return m_powerPlantMarket; }
	std::shared_ptr<PowerPlant> getPowerPlantCard(int index);

	struct PowerPlantPrice
	{
		bool operator() (const std::shared_ptr<Card> plant1, const std::shared_ptr<Card> plant2)
		{
			return (std::dynamic_pointer_cast<PowerPlant>(plant1)->getPowerPlantPrice() < std::dynamic_pointer_cast<PowerPlant>(plant2)->getPowerPlantPrice());
		}
	};

	static std::string cardsFilePath;

private:
	std::vector<std::shared_ptr<Card>> m_deck;
	std::vector<std::shared_ptr<Card>> m_powerPlantMarket;

};