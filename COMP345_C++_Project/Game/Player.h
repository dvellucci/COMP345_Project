#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
	Player();
	~Player();

	void doPlayerTurn();
	bool getQuit() { return m_quit; }

private:
	bool m_quit;
};