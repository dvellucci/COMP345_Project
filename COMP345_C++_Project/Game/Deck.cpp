#include "Deck.h"

std::string Deck::cardsFilePath = "Cards/resourceCardsData.txt";

Deck::Deck() : m_powerPlantMarketSize(8), m_step3CardDrawn(false)
{
	m_deck.reserve(43);
}

Deck::~Deck()
{
	
}

//load the data of each card from a file
void Deck::setUpDeck(std::string filename)
{
	//open file
	std::ifstream file;
	file.open(filename);

	if (!file)
	{
		std::cout << "That is an invalid file name." << std::endl;
		return;
	}
	
	char delimiter = ',';
	//store strings seperated by comma into the vector
	std::vector<std::string> fileStrings;

	while (!file.eof())
	{
		std::string str;
		getline(file, str);
		std::stringstream stream(str);
		//split the string from the text file and put those strings in a vector
		while (getline(stream, str, delimiter))
		{
			fileStrings.push_back(str);
		}
	
		//get the attributes of the power plant
		int price = stoi(fileStrings[0]);
		int houses = stoi(fileStrings[1]);
		int capacity = stoi(fileStrings[2]);

		GridResourceType type;
		std::shared_ptr<PowerPlant> powerPlant = std::make_shared<PowerPlant>(CardType::Power_Plant, price, houses, capacity);
		m_deck.emplace_back(powerPlant);

		//set the types of resources used by the power plant
		for (size_t i = 3; i < fileStrings.size(); i++)
		{
			if (fileStrings[i] == "coal")
				type = GridResourceType::Coal;
			else if (fileStrings[i] == "oil")
				type = GridResourceType::Oil;
			else if (fileStrings[i] == "garbage")
				type = GridResourceType::Garbage;
			else if (fileStrings[i] == "uranium")
				type = GridResourceType::Uranium;
			else
				type = GridResourceType::No_Resource;

			powerPlant->setValidResource(type);
		}
		fileStrings.clear();
	}

	//add the step 3 card
	std::shared_ptr<StepCard> stepCard = std::make_shared<StepCard>(CardType::Step_3);
	m_deck.emplace_back(stepCard);
	fileStrings.clear();

	setUpMarket();
}

void Deck::setUpMarket()
{
	for (int i = 0; i < m_powerPlantMarketSize; i++)
	{
		std::shared_ptr<Card> top = m_deck[0];
		m_powerPlantMarket.push_back(top);
		m_deck.erase(m_deck.begin());
	}
}

void Deck::outputMarket()
{
	int i = 0;
	std::shared_ptr<PowerPlant> powerPlantCard = nullptr;
	for (auto& card : m_powerPlantMarket)
	{
		if (powerPlantCard = std::dynamic_pointer_cast<PowerPlant>(card))
		{
			std::cout << i << ". ";
			outputPowerPlant(std::dynamic_pointer_cast<PowerPlant>(card));
			i++;
		}
		else
		{
			std::cout << i << ". Step 3 Card." << std::endl;
			i++;
		}
		
	}
	std::cout << std::endl;
}

void Deck::outputPowerPlant(std::shared_ptr<PowerPlant> plant)
{
	std::cout << "Resources needed: ";
	for (auto resource : plant->getValidResources())
	{
		std::cout << plant->getResourceTypeName(resource) << ", ";
	}
	std::cout << "Minimum Price: " << plant->getPowerPlantPrice() << ". Houses: " << plant->getPowerPlantHouses() << ". ";
	std::cout << "Storage Capacity: " << plant->getPowerPlantCapacity() * 2 << std::endl; 
}

void Deck::shuffleMainDeck()
{
}

void Deck::shuffleMarket(std::vector<std::shared_ptr<Card>>& m_deck)
{
	
}

void Deck::removeSmallestPowerPlant()
{
	if (m_powerPlantMarket.size() > 0)
	{
		m_powerPlantMarket.erase(m_powerPlantMarket.begin());
	}
}

void Deck::removePlantFromMarket(int index)
{
	m_powerPlantMarket.erase(m_powerPlantMarket.begin() + index);
}

void Deck::removeStep3Card()
{
	std::shared_ptr<StepCard> tempCard = nullptr;
	for (size_t i = 0; i < m_powerPlantMarket.size(); i++)
	{
		if (tempCard = std::dynamic_pointer_cast<StepCard>(m_powerPlantMarket[i]))
		{
			m_powerPlantMarket.erase(m_powerPlantMarket.begin() + i);
			return;
		}
	}
}

//when the game is in step 3, change the size of the power plant market
void Deck::setStep3Market()
{
	std::cout << "The market has been re-adjusted for step 3." << std::endl;
	m_powerPlantMarketSize = 6;
	while (m_powerPlantMarket.size() > m_powerPlantMarketSize)
	{
		removeSmallestPowerPlant();
		removeStep3Card();
	}
	//fill up the market
	drawCard();
}

//draw a card and at it to the power plant market
bool Deck::drawCard()
{
	std::shared_ptr<PowerPlant> powerPlant = nullptr;
	std::shared_ptr<StepCard> stepCard = nullptr;
	while(m_powerPlantMarket.size() < m_powerPlantMarketSize && m_deck.size() > 0)
	{
		std::shared_ptr<Card> topCard = m_deck[0];
		m_powerPlantMarket.push_back(topCard);
		m_deck.erase(m_deck.begin());

		if (powerPlant = std::dynamic_pointer_cast<PowerPlant>(topCard))
		{
			//sort the power plants
			std::sort(m_powerPlantMarket.begin(), m_powerPlantMarket.end(), PowerPlantPrice());
			return true;
		}
		
		//check for step 3 card
		if (stepCard = std::dynamic_pointer_cast<StepCard>(topCard))
		{
			std::cout << "The step 3 card has been drawn." << std::endl << std::endl;
			m_step3CardDrawn = true;
			m_powerPlantMarketSize = 7;
			return true;
		}

		return true;
	}
	return false;
}


std::shared_ptr<PowerPlant> Deck::getPowerPlantCard(int index)
{
	return std::dynamic_pointer_cast<PowerPlant>(m_powerPlantMarket[index]);
}
