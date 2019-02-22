#pragma once
#include <vector>

class GameSettings
{
public:
	GameSettings(int numOfPlayers);
	~GameSettings();

	void setStep(int step) { m_step = step; }

	int getStep() { return m_step; }
	int getElektroPayment(int index) { return m_elektroPayments[index]; }
	int getMaxPowerPlants() { return m_maxPowerPlants; }
	int getPhase2Cities() { return m_phase2Cities; }
	int getCitiesToEnd() { return m_citiesToEnd; }

private:
	std::vector<int> m_elektroPayments;
	int m_step;
	int m_maxPowerPlants;
	int m_phase2Cities;
	int m_citiesToEnd;
	
	int m_coalToSupply;
	int m_oilToSupply;
	int m_garbageToSupply;
	int m_uraniumToSupply;

};