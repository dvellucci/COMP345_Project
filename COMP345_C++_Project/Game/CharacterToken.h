#pragma once
#include <SFML/Graphics.hpp>

enum PlayerCharacters {
	Amazon = 1,
	Troll = 2
};

class CharacterToken
{
public:
	CharacterToken() {};
	CharacterToken(PlayerCharacters character);
	~CharacterToken();

	bool getIsPicked() { return m_isPicked; }

private:
	bool m_isPicked;
	PlayerCharacters m_character;
	sf::Sprite m_characterSprite;
};