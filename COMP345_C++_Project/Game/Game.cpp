#include "Game.h"

unsigned int mapWidth = 1700;
unsigned int mapHeight = 1231;

Game::Game() 
{
	//load fonts
	ResourceHolder::Instance()->loadFont(Fonts::Default, "Fonts/font.ttf");

	//load textures
	ResourceHolder::Instance()->loadTexture(Textures::Title, "Textures/power_grid_cover.png");
	ResourceHolder::Instance()->loadTexture(Textures::Default, "Textures/transparent.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_1, "Textures/Houses/player1house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_2, "Textures/Houses/player2house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_3, "Textures/Houses/player3house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_4, "Textures/Houses/player4house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_5, "Textures/Houses/player5house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Player_6, "Textures/Houses/player6house.png");
	ResourceHolder::Instance()->loadTexture(Textures::Coal, "Textures/Resources/coal.png");
	ResourceHolder::Instance()->loadTexture(Textures::Oil, "Textures/Resources/oil.png");
	ResourceHolder::Instance()->loadTexture(Textures::Garbage, "Textures/Resources/garbage.png");
	ResourceHolder::Instance()->loadTexture(Textures::Uranium, "Textures/Resources/uranium.png");
}

Game::~Game() 
{
	delete m_currentState;
	delete mainWindow;
}


void Game::start()
{
	//create the window and set the max fps
	mainWindow = new sf::RenderWindow();
	mainWindow->create(sf::VideoMode(mapWidth, mapHeight, 32), "COMP 345", sf::Style::Titlebar | sf::Style::Close);
	mainWindow->setFramerateLimit(30);

	//run the main game loop
	gameLoop();
}

void Game::gameLoop()
{
	sf::Event currEvent;

	auto stateID = GameStates::PLAYING;
	m_currentState = new IntroState();

	//start the thread that will do the rendering
	mainWindow->setActive(false);
	sf::Thread thread(&Game::renderingThread, this);
	thread.launch();

	//start the thread that will do the game logic
	mainWindow->setActive(false);
	sf::Thread thread2(&Game::logicThread, this);
	thread2.launch();

	//loop to handle events
	while (mainWindow->isOpen())
	{
		//handle any events in a state
		m_currentState->handle_events(mainWindow, currEvent);

		//change state when needed
		changeState(m_currentState, *mainWindow);
	}
}

void Game::changeState(GameState*& m_currentState, sf::RenderWindow& mainWindow)
{
	auto nextState = m_currentState->getNextState();

	//If the state needs to be changed
	if (m_currentState->getNextState() != null) {
		//Delete the current state
		if (nextState != EXIT)
		{
			///TODO: FIND SOLUTION FOR THIS
			//delete m_currentState;
		}

		//Change the state
		switch (nextState)
		{
		case INTRO:
			m_currentState = new IntroState();
			break;
		case PLAYING:
			m_currentState = new PlayingState();
			break;
		case EXIT:
			mainWindow.close();
			break;
		}
	}
}

void Game::renderingThread()
{
	// activate the window's context
	mainWindow->setActive(true);

	// the rendering loop
	while (mainWindow->isOpen())
	{
		mainWindow->clear();
		m_currentState->draw(mainWindow);
		mainWindow->display();
	}
}

void Game::logicThread()
{
	while (mainWindow->isOpen())
	{
		m_currentState->logic();
	}
}

