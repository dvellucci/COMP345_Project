#pragma once
#include "Dice.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
	Player(std::string playerName);
	~Player();

	void doPlayerTurn();
	bool getQuit() { return m_quit; }
	std::string getPlayerName() { return m_playerName; }

private:
	std::string m_playerName;
	bool m_quit;
};