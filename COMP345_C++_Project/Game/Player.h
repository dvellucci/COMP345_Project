#pragma once
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include "GridResourceMarket.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <set>

class Player {
public:
	Player(std::string playerName, int playerNum);
	~Player();

	void doPlayerTurn();

	int getPlayerNumber() { return m_playerNumber; }
	int countPlayerCities();
	std::string getPlayerName() { return m_playerName; }
	std::vector<std::shared_ptr<Map::City::CitySlot>>& getOwnedCities() { return m_ownedCitySlots; }
	static std::vector<std::shared_ptr<Player>>& getPlayerOrder(std::vector<std::shared_ptr<Player>>& players);

private:
	std::vector<std::shared_ptr<Map::City::CitySlot>> m_ownedCitySlots;
	std::vector<std::shared_ptr<GridResource>> m_resources;
	sf::Texture m_playerTexture;

	std::string m_playerName;
	int m_playerNumber;
	int m_cities;
	int m_elektro;
};