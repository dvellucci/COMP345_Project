#pragma once
#ifndef Playing_H
#define Playing_H
#include "GameState.h"
#include "GameStates.h"
#include "ResourceHolder.h"
#include "Player.h"
#include "GameBoard/Map.h"
#include "GameBoard/MapManager.h"
#include "GridResourceMarket.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <locale> 
#include <string>
#include <cctype>

class PlayingState : public GameState 
{
public:
	PlayingState();
	~PlayingState();

	//Main loop functions
	void handle_events(sf::RenderWindow& window, sf::Event& currEvent) override;
	void logic() override;
	void draw(sf::RenderWindow* window) override;

	//sets up the players and map
	void setUpGame();

private:
	std::vector<std::shared_ptr<Player>> players;
	bool m_playing;
	bool m_quit;

	std::shared_ptr<MapManager> m_mapManager;
	std::shared_ptr<GridResourceMarket> m_gridResourceMarket;

};

#endif