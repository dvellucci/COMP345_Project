#pragma once
#ifndef Playing_H
#define Playing_H
#include "GameState.h"
#include "GameStates.h"
#include "ResourceHolder.h"
#include "GameBoard/Map.h"
#include "GameBoard/MapManager.h"
#include "GridResourceMarket.h"
#include "Deck.h"
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
	void handle_events(sf::RenderWindow* mainWindow, sf::Event& currEvent) override;
	void logic() override;
	void draw(sf::RenderWindow* mainWindow) override;

	//sets up the players and map
	void setNumOfPlayers();
	void setUpMap();
	void setUpGame();

	bool comparePriority(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2);
	void updatePlayerOrder(bool reverse);

	void buyResourcesTestDriver();
	void buyPlayerHouseTestDriver();

private:
	std::vector<std::shared_ptr<Player>> players;
	bool m_initialBuyingPhase;
	bool m_playing;
	bool m_quit;

	std::shared_ptr<MapManager> m_mapManager;
	std::shared_ptr<GridResourceMarket> m_gridResourceMarket;
};

#endif