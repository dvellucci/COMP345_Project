#pragma once
#include "GridResource.h"
#include <iostream>

enum CardType
{
	Power_Plant,
	Summary, 
	Step_3
};

class Card
{
public:
	Card() {};
	explicit Card(CardType type);
	virtual ~Card() {}

	CardType getCardTypeByName(std::string name);

protected:
	CardType m_type;
};