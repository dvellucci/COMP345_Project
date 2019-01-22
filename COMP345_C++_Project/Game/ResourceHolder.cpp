#include "ResourceHolder.h"

ResourceHolder* ResourceHolder::instance = NULL;

ResourceHolder::ResourceHolder() {
}

ResourceHolder::~ResourceHolder() {
}

void ResourceHolder::loadTexture(Textures::ID id, const std::string & filename) 
{
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	//load the texture from the file
	if (!texture->loadFromFile(filename))
		throw
		std::runtime_error("ResourceHolder::loadTexture - Failed to load " + filename);

	//if the texture is loaded properly, insert the texture into the map
	m_textureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture & ResourceHolder::get(Textures::ID id)
{
	auto found = m_textureMap.find(id);
	return *found->second;
}

const sf::Texture & ResourceHolder::get(Textures::ID id) const
{
	auto found = m_textureMap.find(id);
	return *found->second;
}

void ResourceHolder::loadFont(Fonts::ID id, const std::string & filename)
{
	std::unique_ptr<sf::Font> font(new sf::Font());

	//load font from a file
	if(!font->loadFromFile(filename)) 
		throw
		std::runtime_error("ResourceLoader::loadFont - Failed to load " + filename);

	m_fontMap.insert(std::make_pair(id, std::move(font)));
}

sf::Font & ResourceHolder::get(Fonts::ID id)
{
	auto found = m_fontMap.find(id);
	return *found->second;
}
