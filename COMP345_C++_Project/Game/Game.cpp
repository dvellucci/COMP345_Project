#include "Game.h"

Game::Game() {

}

Game::~Game() {

}

void Game::start()
{
	mainWindow.create(sf::VideoMode(1600, 1062, 32), "COMP 345", sf::Style::Titlebar | sf::Style::Close);
	gameLoop();
}

void Game::gameLoop()
{
	sf::Event currEvent;

	auto stateID = GameStates::PLAYING;
	m_currentState = std::make_unique<Intro>();

	while (mainWindow.isOpen())
	{
		m_currentState->handle_events(mainWindow, currEvent);

		//Do state logic
		m_currentState->logic();

		changeState();

		//Do state rendering
		mainWindow.clear();
		m_currentState->draw(mainWindow);
		mainWindow.display();
	}
}

void Game::changeState()
{
	auto nextState = m_currentState->getNextState();

	//If the state needs to be changed
	if (m_currentState->getNextState() != null) {
		//Delete the current state
		if (nextState != EXIT)
		{
			m_currentState.reset();
		}

		//Change the state
		switch (nextState)
		{
		case INTRO:
			m_currentState = std::make_unique<Intro>();
			break;
		case MAIN_MENU:
			m_currentState = std::make_unique<Intro>();
			break;
		case EXIT:
			mainWindow.close();
			break;
		}
	}
}
