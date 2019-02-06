#pragma once

#include "Card.h"

class StepCard : public Card
{
public:
	StepCard(CardType cardType) : Card(cardType) {};
	~StepCard() {};

private:
	CardType m_cardType;
};