#ifndef Game_H
#define Game_H
#include <memory>
#include "GameState.h"
#include "GameStates.h"
#include "IntroState.h"
#include "PlayingState.h"

class Game
{
public:
	Game();
	~Game();

	void start();
	void gameLoop();
	void changeState(GameState*& m_currentState, sf::RenderWindow& mainWindow);
	void renderingThread();
	void logicThread();


private:

	sf::RenderWindow* mainWindow;
	GameState* m_currentState;
};

#endif