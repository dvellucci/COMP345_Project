#pragma once
#ifndef Playing_H
#define Playing_H
#include "GameState.h"
#include "GameStates.h"
#include "TextureHolder.h"
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
	void instantiatePlayers();

private:
	sf::Sprite m_sprite;
	std::vector<std::unique_ptr<Player>> players;

	int m_playerTurn;
};

#endif