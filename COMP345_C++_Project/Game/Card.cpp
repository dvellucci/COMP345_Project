#include "Card.h"

Card::Card(CardType type) : m_type(type)
{

}

Card::~Card()
{
}

CardType Card::getCardTypeByName(std::string name)
{
	return CardType();
}