#pragma once
#include "Player.h"

Player::Player(std::string playerName) : m_playerName(playerName), m_quit(false)
{
}

Player::~Player()
{
}

void Player::updatePlayerTokens(std::vector<std::shared_ptr<Map::City>> &m_ownedCities)
{
	
}

void Player::doPlayerTurn()
{
	return;
}

