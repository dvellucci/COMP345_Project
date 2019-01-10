#pragma once
#ifndef Intro_H
#define Intro_H
#include "GameState.h"
#include "GameStates.h"
#include "TextureHolder.h"

class Intro : public GameState
{
public:
	Intro();
	~Intro();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent);
	void logic();
	void draw(sf::RenderWindow& window);
	bool getIsClosed() { return close; };

private:
	bool close;
	sf::Sprite m_titleSprite;
};

#endif