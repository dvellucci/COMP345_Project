#pragma once
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Player {
public:
	Player(std::string playerName);
	~Player();

	void setPlayerSprite(sf::Sprite sprite) { m_playerSprite = sprite; }
	void updatePlayerTokens(std::vector<std::shared_ptr<Map::City>> &m_ownedCities);
	void doPlayerTurn();
	bool getQuit() { return m_quit; }
	std::string getPlayerName() { return m_playerName; }
	std::vector<std::shared_ptr<Map::City>>& getOwnedRegions() { return m_ownedCities; }

private:
	std::vector<std::shared_ptr<Map::City>> m_ownedCities;
	std::string m_playerName;
	sf::Sprite m_playerSprite;
	bool m_quit;
};