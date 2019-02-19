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
#include <algorithm>
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

	//phase 1: sets the order of the players for the turn
	void phase1Start();
	void updatePlayerOrder(bool reverse);

	//phase 2: auctioning power plants
	void doPhase2();
	void phase2Start();
	void phase2StartAuction();
	void phase2BidOnPlant(int index, int bid, bool skipBid);
	void phase2NextBid(int bid = -1);
	void phase2EndBid();
	void phase2End();

	void doPhase3();
	void buyResourcesPhase();
	void buildingPhase();
	void bureaucracyPhase();

	//player driver for test functionality
	void playerDriver();

	void printGameInfo();

	struct checkPlayerPriority
	{
		bool operator() (const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2)
		{
			return (player1->getHighestPowerPlant() > player2->getHighestPowerPlant());
		}
	};

private:
	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<std::shared_ptr<Player>> m_playerOrder; //the order that the players will play in each turn
	std::shared_ptr<Player> m_currentPlayer; //pointer to current player

	//managers for the map and market
	std::shared_ptr<MapManager> m_mapManager;
	std::shared_ptr<GridResourceMarket> m_gridResourceMarket;

	//the deck as well as a vector to hold the current power plant cards players can bid on
	std::shared_ptr<Deck> m_deckManager;

	//holds the info of whether a player can bid/buy a power plant in a turn
	std::map<Player*, bool> m_canPlayerBid;
	std::map<Player*, bool> m_canPlayerBuy;
	std::shared_ptr<Player> m_highestBidder;

	int m_currentBid;
	int m_powerPlantIndex;
	int m_resourceIndex;

	bool m_initialBid;
	bool m_playing;
	bool m_quit;
	bool m_firstTurn;
};

#endif