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

void Player::setElektro(int amountSpent)
{
	m_elektro = m_elektro - amountSpent;
}


void Player::buyPowerPlant(std::shared_ptr<Deck> deckManager, int slotIndex, int price)
{
	setElektro(price);
	m_powerPlants.push_back(deckManager->getPowerPlantMarket()[slotIndex]);
	deckManager->removePlantFromMarket(slotIndex);
}

void Player::replacePowerPlant(std::shared_ptr<Deck> deckManager, int slotIndex, int price)
{
	setElektro(price);

	//ask the player which plant to replace
	std::cout << "Select a power plant to replace. " << std::endl;
	std::cout << "Your power plants: " << std::endl;
	for (size_t i = 0; i < m_powerPlants.size(); i++)
	{
		auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(m_powerPlants[i]);
		std::cout << i << ". ";
		deckManager->outputPowerPlant(powerPlant);
	}

	int index = 0;
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

	//do transfer of resources here
}


bool Player::purchaseResource(std::shared_ptr<GridResourceMarket> market, std::shared_ptr<Card> plant, GridResourceType type, int amount)
{
	//return false if there isn't the required amount of resources available
	if (amount > market->getAvailableResourceType(type))
		return false;

	auto resourceType = type;
	if (type == GridResourceType::Coal)
	{
		m_storedResources.emplace(std::make_pair(GridResourceType::Coal, amount));		
	}
	else if (type == GridResourceType::Oil)
	{
		m_storedResources.emplace(std::make_pair(GridResourceType::Oil, amount));
	}
	else if (type == GridResourceType::Garbage)
	{
		m_storedResources.emplace(std::make_pair(GridResourceType::Garbage, amount));
	}
	else if (type == GridResourceType::Uranium)
	{
		m_storedResources.emplace(std::make_pair(GridResourceType::Uranium, amount));
	}
	//remove the resources bought by the player from the market
	market->removeResourcesFromMarket(resourceType, amount);

	return true;
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

