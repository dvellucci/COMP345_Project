#pragma once
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include "GridResourceMarket.h"
#include "PowerPlant.h"
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
	int getElektro() { return m_elektro; }
	int countPlayerCities();

	std::string getPlayerName() { return m_playerName; }
	std::vector<std::shared_ptr<Map::City::CitySlot>>& getOwnedCities() { return m_ownedCitySlots; }
	std::vector<std::shared_ptr<Card>>& getPowerPlants() { return m_powerPlants; }

	bool buyPowerPlant(std::vector<std::shared_ptr<Card>> deck, int slotIndex);
	bool purchaseResource(std::shared_ptr<GridResourceMarket> market, std::shared_ptr<Card> plant, GridResourceType type, int amount);

	sf::Texture& getPlayerTexture() { return m_playerTexture; }

private:
	std::vector<std::shared_ptr<Map::City::CitySlot>> m_ownedCitySlots;
	std::map<GridResourceType, int> m_storedResources;
	std::vector<std::shared_ptr<Card>> m_powerPlants;
	sf::Texture m_playerTexture;

	std::string m_playerName;
	int m_availableHouses;
	int m_playerNumber;
	int m_elektro;
};