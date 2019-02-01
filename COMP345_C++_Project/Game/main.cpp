#include "game.h"

GameState *currentState = NULL;
int mapWidth = 1700;
int mapHeight = 750;

//the render function that will run on a seperate thread
void renderingThread(sf::RenderWindow*& window)
{
	// activate the window's context
	window->setActive(true);

	// the rendering loop
	while (window->isOpen())
	{
		window->clear();
		currentState->draw(window);
		window->display();
	}
}

//thread for game logic
void logicThread(sf::RenderWindow*& window)
{
//	window->setActive(true);
	while (window->isOpen())
	{
		currentState->logic();
	}
	
}

/*-----------------MAYBE PUT ALL THIS IN GAME CLASS------------*/
int main()
{
	sf::RenderWindow mainWindow;
	mainWindow.create(sf::VideoMode(mapWidth, mapHeight, 32), "COMP 345", sf::Style::Titlebar | sf::Style::Close);
	mainWindow.setFramerateLimit(30);

	Game game;
	//game.start();

	sf::Event currEvent;
	auto stateID = GameStates::PLAYING;
	currentState = new IntroState();
	
	//start the thread that will do the rendering
	mainWindow.setActive(false);
	sf::Thread thread(&renderingThread, &mainWindow);
	thread.launch();

	//start the thread that will do the game logic
	mainWindow.setActive(false);
	sf::Thread thread2(&logicThread, &mainWindow);
	thread2.launch();

	//loop that handles events
	while (mainWindow.isOpen())
	{
		//handle any events in a state
		currentState->handle_events(mainWindow, currEvent);

		//change state when needed
		game.changeState(currentState, mainWindow);
	}

	delete currentState;
	return 0;
}
