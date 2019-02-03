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

	void createCoalResources();

	void loadMarketResource(std::string filename);
	std::vector<std::shared_ptr<GridResource>>& getCoalResources() { return m_coalResources; }

private:
	std::vector<std::shared_ptr<GridResource>> m_coalResources;
	//std::shared_ptr<GridResource> m_coalResources[RESOURCE];
};