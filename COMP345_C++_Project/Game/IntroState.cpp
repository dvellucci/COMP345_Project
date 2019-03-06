#include "IntroState.h"
#include <iostream>


IntroState::IntroState() : close(false)
{
	std::cout << "Press enter to enter the game setup." << std::endl;
	m_titleSprite.setTexture(ResourceHolder::Instance()->get(Textures::Title));
	m_titleSprite.setOrigin(m_titleSprite.getLocalBounds().width / 2.0f, m_titleSprite.getLocalBounds().height / 2.0f);
	m_titleSprite.setPosition((float)mapWidth / 2, (float)mapHeight / 2);
}

IntroState::~IntroState()
{

}

//handles any keyboard or mouse events
void IntroState::handle_events(sf::RenderWindow* mainWindow, sf::Event& currEvent)
{
	while (mainWindow->pollEvent(currEvent))
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

void IntroState::draw(sf::RenderWindow* mainWindow)
{
	mainWindow->draw(m_titleSprite);
}