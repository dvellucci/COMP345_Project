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
#include "GameSettings.h"
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

	//phase 3: the buying resources phase
	void doPhase3();
	void phase3BuyResources1();
	void phase3BuyResources2(int amount);

	//phase 4: the buying cities phase
	void doPhase4();
	void phase4Start();
	void phase4BuyCities1();
	void phase4BuyCities2(bool isBuying, std::string city, int slot);
	void phase4End();

	void doPhase5();
	void phase5PowerCities1();
	void phase5PowerCities2(std::shared_ptr<PowerPlant> powerPlant);
	void chooseResourceToConsume1(std::shared_ptr<PowerPlant> powerPlant);
	void chooseResourceToConsume2(int amount);
	void phase5Bureaucracy();
	void endPhase5();

	void gameOver();

	void printGameInfo();

	struct checkPlayerPriority
	{
		bool operator() (const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2)
		{
			return (player1->getHighestPowerPlant() > player2->getHighestPowerPlant());
		}
	};

	int getNextPlayer();

	int getNumOfResourcesOwned(GridResourceType type, std::vector<std::shared_ptr<Player>> players);
	int getResourcesInSupply(GridResourceType type, std::vector<std::shared_ptr<Player>> players);

private:

	void clearCinInput(std::string error);

	std::vector<std::shared_ptr<Player>> m_players;
	std::vector<std::shared_ptr<Player>> m_playerOrder; //the order that the players will play in each turn
	std::shared_ptr<Player> m_currentPlayer; //pointer to current player

	//managers for the map and market
	std::shared_ptr<MapManager> m_mapManager;
	std::shared_ptr<GridResourceMarket> m_gridResourceMarket;

	//game settings object
	std::shared_ptr<GameSettings> m_gameSettings;

	//the deck as well as a vector to hold the current power plant cards players can bid on
	std::shared_ptr<Deck> m_deckManager;

	//holds the info of whether a player can bid/buy a power plant in a turn
	std::map<Player*, bool> m_canPlayerBid;
	std::map<Player*, bool> m_canPlayerBuy;
	//keep track of the highest bidder during an auction
	std::shared_ptr<Player> m_highestBidder;

	//holds all potential winners which are players that have more cities than the amount to end the game
	std::vector<std::shared_ptr<Player>> m_potentialWinners;
	std::shared_ptr<Player> m_winner;

	//keeps track of which power plants a player used during their turn of phase 5
	std::vector<std::shared_ptr<Card>> m_usedPowerPlants;
	//keeps track of how many cities players are powering for their turns
	int m_poweredCities;

	int m_currentBid;
	unsigned int m_powerPlantIndex;
	unsigned int m_resourceIndex;

	bool m_initialBid;
	bool m_playing;
	bool m_quit;
	bool m_firstTurn;
	bool m_gameOver;
};

#endif