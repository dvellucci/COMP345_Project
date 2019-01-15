#pragma once
#ifndef Playing_H
#define Playing_H
#include "GameState.h"
#include "GameStates.h"
#include "TextureHolder.h"

class PlayingState : public GameState 
{
public:
	PlayingState();
	~PlayingState();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent) override;
	void logic() override;
	void draw(sf::RenderWindow& window) override;

private:
	sf::Sprite m_sprite;
};

#endif