#pragma once
#ifndef Intro_H
#define Intro_H
#include "GameState.h"
#include "GameStates.h"
#include "TextureHolder.h"

class IntroState : public GameState
{
public:
	IntroState();
	~IntroState();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent) override;
	void logic() override;
	void draw(sf::RenderWindow& window) override;
	bool getIsClosed() { return close; };

private:
	bool close;
	sf::Sprite m_titleSprite;
};

#endif