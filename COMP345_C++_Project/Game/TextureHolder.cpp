#include "TextureHolder.h"

TextureHolder* TextureHolder::instance = NULL;

TextureHolder::TextureHolder() {
}

TextureHolder::~TextureHolder() {
}

void TextureHolder::load(Textures::ID id, const std::string & filename) {
	std::unique_ptr<sf::Texture> texture(new sf::Texture());

	//load the texture from the file
	if (!texture->loadFromFile(filename))
		throw
		std::runtime_error("TextureHolder::load - Failed to load " + filename);

	//if the texture is loaded properly, insert the texture into the map
	mTextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture & TextureHolder::get(Textures::ID id)
{
	auto found = mTextureMap.find(id);
	return *found->second;
}

const sf::Texture & TextureHolder::get(Textures::ID id) const
{
	auto found = mTextureMap.find(id);
	return *found->second;
}
