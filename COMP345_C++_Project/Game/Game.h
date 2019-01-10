#ifndef Game_H
#define Game_H
#include <memory>
#include "GameState.h"
#include "GameStates.h"
#include "Intro.h"


class Game
{
public:
	Game();
	~Game();

	void start();
	void gameLoop();
	void changeState();

private:

	sf::RenderWindow mainWindow;
	//Game state object
	//GameState *m_currentState;
	std::unique_ptr<GameState> m_currentState;


};

#endif