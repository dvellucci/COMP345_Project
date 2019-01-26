#pragma once
#include "Player.h"

Player::Player(std::string playerName) : m_playerName(playerName), m_quit(false)
{
}

Player::~Player()
{
}

void Player::updatePlayerTokens(std::vector<std::shared_ptr<Map::City>> &m_ownedCities)
{
	for (std::shared_ptr<Map::City> region : m_ownedCities)
	{
		//region->m_tokenSprite->setTexture(ResourceHolder::Instance()->get(Textures::Title));
		//region->m_tokenSprite->setPosition(region->m_xPos, region->m_yPos);
	}
}

void Player::doPlayerTurn()
{
	return;
}

void Player::firstConquer(Map &map)
{
	std::cout << "Pick a map to conquer" << std::endl;
	int choice = 0;
	int i = 1;
	for (std::shared_ptr<Map::City> region : map.getCities())
	{
		std::cout << i << ". " << "City" << std::endl;
		i++;
	}
	std::cin >> choice;

	for (std::shared_ptr<Map::City>& region : map.getCities())
	{
		if (choice == region->m_cityNumber && !region->m_isOwned)
		{
			region->m_isOwned = true;
			region->m_tokenSprite = std::make_unique<sf::Sprite>();
			region->m_tokenSprite->setTexture(ResourceHolder::Instance()->get(Textures::Title));
			region->m_tokenSprite->setPosition(region->m_xPos, region->m_yPos);
			m_ownedCities.push_back(region);
			break;
		}
			
	}
}

void Player::pickCharacter(std::vector<CharacterToken> m_characterTokens)
{

}
