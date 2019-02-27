#pragma once
#include <vector>

class GameSettings
{
public:
	GameSettings(int numOfPlayers);
	~GameSettings();

	void setStep(int step);

	int getStep() { return m_step; }
	int getElektroPayment(int index) { return m_elektroPayments[index]; }
	int getMaxPowerPlants() { return m_maxPowerPlants; }
	unsigned int getStep2Cities() { return m_step2Cities; }
	unsigned int getCitiesToEnd() { return m_citiesToEnd; }

	int getCoalToSupply() { return m_coalToSupply; }
	int getOilToSupply() { return m_oilToSupply; }
	int getGarbageToSupply() { return m_garbageToSupply; }
	int getUraniumToSupply() { return m_uraniumToSupply; }
private:
	std::vector<int> m_elektroPayments;
	int m_step;
	int m_maxPowerPlants;
	int m_step2Cities;
	int m_citiesToEnd;
	
	int m_coalToSupply;
	int m_oilToSupply;
	int m_garbageToSupply;
	int m_uraniumToSupply;

};