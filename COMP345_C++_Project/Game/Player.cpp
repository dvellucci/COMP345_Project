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

int Player::countPlayerCities()
{	
	std::set<std::string> cities;
	for (std::shared_ptr<Map::City::CitySlot> slot : m_ownedCitySlots)
	{
		
	}
	return 0;
}

bool Player::buyResources(std::vector<std::shared_ptr<GridResource>> resourceMarket, GridResourceType type, int amount)
{
	return false;
}

bool Player::buyPowerPlant(std::vector<std::shared_ptr<Card>> deck, int slotIndex)
{
	for (auto card : deck)
	{

	}
	return false;
}

