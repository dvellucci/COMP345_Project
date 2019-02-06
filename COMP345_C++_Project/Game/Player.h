#pragma once
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include "GridResourceMarket.h"
#include "Card.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <set>

class Player 
{
public:
	Player(std::string playerName, int playerNum);
	~Player();

	void doPlayerTurn();
	void setElektro(int amountSpent);

	int getPlayerNumber() { return m_playerNumber; }
	int countPlayerCities();

	std::string getPlayerName() { return m_playerName; }
	std::vector<std::shared_ptr<Map::City::CitySlot>>& getOwnedCities() { return m_ownedCitySlots; }

	bool buyResources(std::vector<std::shared_ptr<GridResource>> resourceMarket, GridResourceType type, int amount);
	bool buyPowerPlant(std::vector<std::shared_ptr<Card>> deck, int slotIndex);

private:
	std::vector<std::shared_ptr<Map::City::CitySlot>> m_ownedCitySlots;
	std::vector<std::shared_ptr<GridResource>> m_resources;
	std::vector<std::shared_ptr<Card>> m_powerPlants;
	sf::Texture m_playerTexture;

	std::string m_playerName;
	int m_availableHouses;
	int m_playerNumber;
	int m_elektro;
};