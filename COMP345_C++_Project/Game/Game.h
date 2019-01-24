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
	void changeState();
	void changeState(GameState*& m_currentState, sf::RenderWindow& mainWindow);

private:

	sf::RenderWindow mainWindow;
	std::unique_ptr<GameState> m_currentState;
	GameState* gamestate;

};

#endif