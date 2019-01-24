#pragma once
#include "GameState.h"
#include "GameStates.h"
#include "ResourceHolder.h"

class IntroState : public GameState
{
public:
	IntroState();
	~IntroState();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent) ;
	void logic();
	void draw(sf::RenderWindow* window);
	bool getIsClosed() { return close; };

private:
	bool close;
	sf::Sprite m_titleSprite;
};
