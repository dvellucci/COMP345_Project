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
	Card(CardType type);
	~Card();

	CardType getCardTypeByName(std::string name);

protected:
	CardType m_type;
	int m_numOfHouses;
	int m_numOfResources;
};