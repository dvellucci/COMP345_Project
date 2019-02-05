#pragma once
#include "Player.h"

Player::Player(std::string playerName, int playerNum) : m_playerName(playerName), m_elektro(50),
m_cities(22), m_playerNumber(playerNum)
{
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

int Player::countPlayerCities()
{	
	std::set<std::string> cities;
	for (std::shared_ptr<Map::City::CitySlot> slot : m_ownedCitySlots)
	{
		
	}
	return 0;
}

std::vector<std::shared_ptr<Player>>& Player::getPlayerOrder(std::vector<std::shared_ptr<Player>>& players)
{
	//check if no players have a city so that order is random


	//determine player order by most cities
	
	
	return players;
}

