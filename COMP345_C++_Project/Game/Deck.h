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
	void shuffleMainDeck();
	void shuffleMarket(std::vector<std::shared_ptr<Card>>& m_deck);
	void setMarketSize(int size) { m_powerPlantMarketSize = size; }
	void removeSmallestPowerPlant();
	void removePlantFromMarket(int index);
	void removeStep3Card();
	void setStep3Market();
	
	bool drawCard();
	bool drewStep3Card() { return m_step3CardDrawn; }

	std::vector<std::shared_ptr<Card>>& getDeck() { return m_deck; }
	std::vector<std::shared_ptr<Card>>& getPowerPlantMarket() { return m_powerPlantMarket; }
	std::shared_ptr<PowerPlant> getPowerPlantCard(int index);

	//Sort the power plant market with comparison operator
	struct PowerPlantPrice
	{
		bool operator() (const std::shared_ptr<Card> plant1, const std::shared_ptr<Card> plant2)
		{
			//avoid the sorting if the one of the cards is a stepCard
			std::shared_ptr<PowerPlant> temp = nullptr;
			auto powerPlant1 = std::dynamic_pointer_cast<PowerPlant>(plant1);
			auto powerPlant2 = std::dynamic_pointer_cast<PowerPlant>(plant2);
			if (temp != powerPlant1) return false;
			if (temp != powerPlant2) return false;
			return (powerPlant1->getPowerPlantPrice() < powerPlant2->getPowerPlantPrice());
		}
	};

	static std::string cardsFilePath;

private:
	bool m_step3CardDrawn;
	unsigned int m_powerPlantMarketSize;
	std::vector<std::shared_ptr<Card>> m_deck;
	std::vector<std::shared_ptr<Card>> m_powerPlantMarket;

};