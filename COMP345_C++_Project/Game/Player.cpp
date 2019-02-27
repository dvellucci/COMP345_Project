#pragma once
#include "Player.h"

Player::Player(int playerNum) : m_elektro(50), 
m_availableHouses(22), m_playerNumber(playerNum)
{
	m_ownedCitySlots.reserve(22);
	//TO BE REFACTORED
	switch (m_playerNumber)
	{
	case 1:
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_1);
		break;
	case 2:
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_2);
		break;
	case 3: 
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_3);
		break;
	case 4:
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_4);
		break;
	case 5:
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_5);
		break;
	case 6:
		m_playerTexture = ResourceHolder::Instance()->get(Textures::Player_6);
		break;
	default:
		break;
	}
}

Player::~Player()
{
}

void Player::doPlayerTurn()
{
	return;
}

void Player::spendElektro(int amountSpent)
{
	m_elektro = m_elektro - amountSpent;
}


void Player::buyPowerPlant(std::shared_ptr<Deck> deckManager, int slotIndex, int price)
{
	spendElektro(price);
	m_powerPlants.push_back(deckManager->getPowerPlantMarket()[slotIndex]);
	deckManager->removePlantFromMarket(slotIndex);
}

void Player::replacePowerPlant(std::shared_ptr<Deck> deckManager, int slotIndex, int price)
{
	spendElektro(price);

	//ask the player which plant to replace
	std::cout << "Select a power plant to replace. " << std::endl;
	std::cout << "Your power plants: " << std::endl;
	for (size_t i = 0; i < m_powerPlants.size(); i++)
	{
		auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(m_powerPlants[i]);
		std::cout << i << ". ";
		deckManager->outputPowerPlant(powerPlant);
	}

	unsigned int index = 0;
	while (!(std::cin >> index) || index < 0 || index >= m_powerPlants.size())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for a power plant." << std::endl;
	}

	//place the old power plant at the bottom of the deck and remove it from the player deck
	deckManager->getDeck().push_back(m_powerPlants[index]);
	m_powerPlants.erase(m_powerPlants.begin() + index);

	//give the player the new power plant and remove it from the market
	m_powerPlants.push_back(deckManager->getPowerPlantMarket()[slotIndex]);
	deckManager->removePlantFromMarket(slotIndex);
}

void Player::displayPowerPlant(std::shared_ptr<GridResourceMarket> market, std::shared_ptr<PowerPlant> plant)
{
	std::cout << "Resources needed: ";
	for (auto resource : plant->getValidResources())
	{
		std::cout << plant->getResourceTypeName(resource) << ", ";
	}
	std::cout << "Houses:" << plant->getPowerPlantHouses() << ", Storage Capacity: " << plant->getPowerPlantCapacity() << " Stored Resources: ";
	for (auto temp2 : plant->getStoredResources())
	{
		std::cout << temp2.second << " " << market->getResourceType(temp2.first) << ". ";
	}
	std::cout << std::endl;
}

void Player::listPlayerPowerPlants(std::shared_ptr<GridResourceMarket> market)
{
	int index = 0;
	for (auto temp : m_powerPlants)
	{
		auto plant = std::dynamic_pointer_cast<PowerPlant>(temp);
		std::cout << index << ". ";
		displayPowerPlant(market, plant);
		index++;
	}
}


std::shared_ptr<PowerPlant> Player::getPowerPlant(int index)
{
	auto card = m_powerPlants[index];
	auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(card);
	return powerPlant;
}

bool Player::purchaseResource(std::shared_ptr<GridResourceMarket> market, std::shared_ptr<PowerPlant> plant, GridResourceType type, int amount)
{
	int price = market->getPriceOfResources(type, amount);
	
	//plant->GetActiveResources().find(resource) != plant->GetActiveResources().end())
	if (amount >= 0 && m_elektro >= price && (plant->getNumOfPlacedResources() + amount <= 2 * plant->getPowerPlantCapacity()))
	{
		plant->storeResource(type, amount);
		m_elektro = m_elektro - price;
		market->removeResourcesFromMarket(type, amount);
		std::cout << "You have " << m_elektro << " elektro remaining after this purchase." << std::endl << std::endl;
		return true;
	}

	return false;
}

bool Player::doesPlayerOwnCity(std::string city)
{
	std::transform(city.begin(), city.end(), city.begin(), ::tolower);
	for (auto& citySlot : m_ownedCitySlots)
	{
		if (citySlot->getName() == city)
			return true;
	}
	return false;
}

int Player::countPlayerCities()
{	
	return m_ownedCitySlots.size();
}

int Player::getHighestPowerPlant()
{
	int highestPlantPrice = 0;
	for (std::shared_ptr<Card> p : m_powerPlants) 
	{
		auto plant = std::dynamic_pointer_cast<PowerPlant>(p);
		if (plant->getPowerPlantPrice() > highestPlantPrice)
			highestPlantPrice = plant->getPowerPlantPrice();
	}
	return highestPlantPrice;

}

