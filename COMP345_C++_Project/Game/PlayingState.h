#pragma once
#ifndef Playing_H
#define Playing_H
#include "GameState.h"
#include "GameStates.h"
#include "ResourceHolder.h"
#include "Player.h"
#include <vector>
#include <iostream>

class PlayingState : public GameState 
{
public:
	PlayingState();
	~PlayingState();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent) override;
	void logic() override;
	void draw(sf::RenderWindow& window) override;
	void setUpGame();

private:
	sf::Sprite m_sprite;
	std::vector<std::unique_ptr<Player>> players;
	bool m_playing;
	bool m_quit;
};

#endif