#pragma once
#include "Player.h"

Player::Player(std::string playerName, int playerNum) : m_playerName(playerName), m_elektro(50), 
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


bool Player::buyPowerPlant(std::vector<std::shared_ptr<Card>> deck, int slotIndex)
{
	for (auto& card : deck)
	{

	}
	return false;
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

