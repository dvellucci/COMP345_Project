#pragma once
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include "GridResourceMarket.h"
#include "Deck.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <set>

class Player 
{
public:
	Player(int playerNum);
	~Player();

	void doPlayerTurn();
	void setElektro(int amountSpent);

	void buyPowerPlant(std::shared_ptr<Deck> deck, int slotIndex, int price);
	void replacePowerPlant(std::shared_ptr<Deck> deck, int slotIndex, int price);

	int getPlayerNumber() { return m_playerNumber; }
	int getElektro() { return m_elektro; }
	int countPlayerCities();
	int getHighestPowerPlant();

	std::vector<std::shared_ptr<Map::City::CitySlot>>& getOwnedCities() { return m_ownedCitySlots; }
	std::vector<std::shared_ptr<Card>>& getPowerPlants() { return m_powerPlants; }

	bool purchaseResource(std::shared_ptr<GridResourceMarket> market, std::shared_ptr<Card> plant, GridResourceType type, int amount);

	sf::Texture& getPlayerTexture() { return m_playerTexture; }

private:
	std::vector<std::shared_ptr<Map::City::CitySlot>> m_ownedCitySlots;
	std::map<GridResourceType, int> m_storedResources;
	std::vector<std::shared_ptr<Card>> m_powerPlants;
	sf::Texture m_playerTexture;

	int m_availableHouses;
	int m_playerNumber;
	int m_elektro;
};