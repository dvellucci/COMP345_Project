#pragma once
#include "Player.h"

Player::Player(std::string playerName) : m_playerName(playerName), m_quit(false)
{
}

Player::~Player()
{
}

void Player::doPlayerTurn()
{
	return;
}
