#include "PlayingState.h"

PlayingState::PlayingState()
{
	
}

PlayingState::~PlayingState()
{
}

void PlayingState::handle_events(sf::RenderWindow & window, sf::Event & currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Escape)
			{
				setNextState(GameStates::EXIT);
			}
			break;
		}
	}
}

void PlayingState::logic()
{
}

void PlayingState::draw(sf::RenderWindow & window)
{
	
}
