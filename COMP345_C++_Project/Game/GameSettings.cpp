#include "GameSettings.h"

GameSettings::GameSettings(int numOfPlayers) : m_step(1)
{
	m_elektroPayments = { 10, 22, 33, 44, 54, 64, 73, 82, 90, 98, 105, 112, 118, 124, 129, 134, 138, 142, 145, 148, 150 };

	m_coalToSupply = 4;
	m_oilToSupply = 3;
	m_garbageToSupply = 2;
	m_uraniumToSupply = 1;

	switch (numOfPlayers)
	{
	case 2:
		m_maxPowerPlants = 4;
		m_step2Cities = 10;
		m_citiesToEnd = 21;
		break;
	case 3:
		m_maxPowerPlants = 3;
		m_step2Cities = 7;
		m_citiesToEnd = 17;
		break;
	case 4:
		m_maxPowerPlants = 3;
		m_step2Cities = 7;
		m_citiesToEnd = 17;
		break;
	case 5: 
		m_maxPowerPlants = 3;
		m_step2Cities = 7;
		m_citiesToEnd = 15;
		break;
	case 6: 
		m_maxPowerPlants = 3;
		m_step2Cities = 6;
		m_citiesToEnd = 14;
		break;
	}
}

GameSettings::~GameSettings()
{
}

void GameSettings::setStep(int step)
{
	m_step = step;
	if (step == 2)
	{
		m_coalToSupply = 5;
		m_oilToSupply = 4;
		m_garbageToSupply = 3;
		m_uraniumToSupply = 2;
	}
	else if (step == 3)
	{
		m_coalToSupply = 3;
		m_oilToSupply = 5;
		m_garbageToSupply = 4;
		m_uraniumToSupply = 2;
	}
}
