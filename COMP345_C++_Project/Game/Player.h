#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
	Player();
	~Player();

	void doPlayerTurn();
	void handlePlayerEvents(sf::RenderWindow& window, sf::Event& currEvent);
private:
	
};