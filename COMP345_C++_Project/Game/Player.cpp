#pragma once
#include "Player.h"

Player::Player() 
{
}

Player::~Player()
{
}

void Player::doPlayerTurn()
{

}

void Player::handlePlayerEvents(sf::RenderWindow & window, sf::Event & currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Escape)
			{
				
			}
			break;
		}
	}
}
