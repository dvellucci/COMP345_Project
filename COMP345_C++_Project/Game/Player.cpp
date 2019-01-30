#pragma once
#include "Player.h"

Player::Player(std::string playerName) : m_playerName(playerName), m_quit(false), m_elektro(50),
m_houses(22)
{
}

Player::~Player()
{
}

void Player::doPlayerTurn()
{
	return;
}

