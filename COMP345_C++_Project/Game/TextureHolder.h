#pragma once
#ifndef TextureHolder
#define TextureHolder_H
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Textures.h"

class TextureHolder
{
public:
	//Make a singleton
	static TextureHolder* Instance()
	{
		if (instance == 0)
		{
			instance = new TextureHolder();
			return instance;
		}
		return instance;
	}

	TextureHolder();
	~TextureHolder();

	void load(Textures::ID id, const std::string& filename);
	sf::Texture& get(Textures::ID id);
	const sf::Texture& get(Textures::ID id) const;

private:
	std::map<Textures::ID, std::unique_ptr<sf::Texture>> mTextureMap;
	static TextureHolder* instance;
};

typedef TextureHolder TextureHolder;

#endif