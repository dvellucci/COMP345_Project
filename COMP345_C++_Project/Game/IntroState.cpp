#include "IntroState.h"
#include <iostream>


IntroState::IntroState() : close(false)
{
	m_titleSprite.setTexture(ResourceHolder::Instance()->get(Textures::Title));
	m_titleSprite.setOrigin(m_titleSprite.getLocalBounds().width / 2.0f, m_titleSprite.getLocalBounds().height / 2.0f);
	m_titleSprite.setPosition(1200 / 2, 800 / 2);
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

void IntroState::draw(sf::RenderWindow* window)
{
	window->draw(m_titleSprite);
}