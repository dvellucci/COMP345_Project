#include "Intro.h"
#include <iostream>


Intro::Intro() : close(false)
{
	TextureHolder::Instance()->load(Textures::Title, "Textures/smallworld.jpg");
	m_titleSprite.setTexture(TextureHolder::Instance()->get(Textures::Title));
}

Intro::~Intro()
{

}

void Intro::handle_events(sf::RenderWindow& window, sf::Event& currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Return)
			{
				//Move to the main menu
				setNextState(GameStates::MAIN_MENU);
			}
			else if (currEvent.key.code == sf::Keyboard::Escape)
			{
				setNextState(GameStates::EXIT);
			}
			break;
		}
	}
}

void Intro::logic()
{

}

void Intro::draw(sf::RenderWindow& window)
{
	window.draw(m_titleSprite);
}