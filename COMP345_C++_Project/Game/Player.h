#pragma once
#include "CharacterToken.h"
#include "GameBoard/Map.h"
#include "ResourceHolder.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class Player {
public:
	Player(std::string playerName);
	~Player();

	void updatePlayerTokens(std::vector<std::shared_ptr<Map::City>> &m_ownedCities);
	void doPlayerTurn();
	void firstConquer(Map& map);
	void pickCharacter(std::vector<CharacterToken> m_characterTokens);
	bool getQuit() { return m_quit; }
	std::string getPlayerName() { return m_playerName; }
	std::vector<std::shared_ptr<Map::City>>& getOwnedRegions() { return m_ownedCities; }

private:
	std::vector<std::shared_ptr<Map::City>> m_ownedCities;
	std::unique_ptr<CharacterToken> m_token;
	std::string m_playerName;
	bool m_quit;
};