#pragma once
#ifndef ResourceHolder
#define ResourceHolder_H
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Textures.h"

class ResourceHolder
{
public:
	//Make a singleton
	static ResourceHolder* Instance()
	{
		if (instance == 0)
		{
			instance = new ResourceHolder();
			return instance;
		}
		return instance;
	}

	//loading textures
	void loadTexture(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;

	//loading fonts
	void loadFont(Fonts::ID id, const std::string &filename);
	sf::Font& get(Fonts::ID id);

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> m_textureMap;
	std::map<Fonts::ID, std::unique_ptr<sf::Font>> m_fontMap;
	static ResourceHolder* instance;

	ResourceHolder();
	~ResourceHolder();
};

typedef ResourceHolder ResourceHolder;

#endif