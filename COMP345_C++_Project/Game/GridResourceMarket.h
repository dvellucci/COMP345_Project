#pragma once
#include "GridResource.h"
#include "ResourceHolder.h"
#include <vector>
#include <memory>
#include <sstream>
#include <exception>
#include <fstream>
#include <iostream>

#define RESOURCE 24
#define URANIUM 12

class GridResourceMarket
{
public:
	GridResourceMarket();
	~GridResourceMarket();

	void setResourceMarket();
	void createCoalResources();
	void createOilResources();
	void createGarbageResources();
	void createUraniumResources();

	void drawResourceMarket(sf::RenderWindow *&mainWindow);

	void loadMarketResource(std::string filename);
	std::vector<std::shared_ptr<GridResource>>& getCoalResources() { return m_coalResources; }
	std::vector<std::shared_ptr<GridResource>>& getOilResources() { return m_oilResources; }

private:
	std::vector<std::shared_ptr<GridResource>> m_coalResources;
	std::vector<std::shared_ptr<GridResource>> m_oilResources;
	std::vector<std::shared_ptr<GridResource>> m_garbageResources;
	std::vector<std::shared_ptr<GridResource>> m_uraniumResources;
};