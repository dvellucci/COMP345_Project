#include "IntroState.h"
#include <iostream>


IntroState::IntroState() : close(false)
{
	m_titleSprite.setTexture(TextureHolder::Instance()->get(Textures::Title));
}

IntroState::~IntroState()
{

}

void IntroState::handle_events(sf::RenderWindow& window, sf::Event& currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Return)
			{
				//Move to the main menu
				setNextState(GameStates::PLAYING);
			}
			else if (currEvent.key.code == sf::Keyboard::Escape)
			{
				setNextState(GameStates::EXIT);
			}
			break;
		}
	}
}

void IntroState::logic()
{

}

void IntroState::draw(sf::RenderWindow& window)
{
	window.draw(m_titleSprite);
}