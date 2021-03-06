#include "GridResourceMarket.h"

GridResourceMarket::GridResourceMarket()
{
	m_coalResources.reserve(24);
	m_oilResources.reserve(24);
	m_garbageResources.reserve(24);
	m_uraniumResources.reserve(12);
}

GridResourceMarket::~GridResourceMarket()
{

}

void GridResourceMarket::setResourceMarket()
{
	createCoalResources();
	createOilResources();
	createGarbageResources();
	createUraniumResources();

	m_market.emplace(std::make_pair(GridResourceType::Coal, m_coalResources));
	m_market.emplace(std::make_pair(GridResourceType::Oil, m_oilResources));
	m_market.emplace(std::make_pair(GridResourceType::Garbage, m_garbageResources));
	m_market.emplace(std::make_pair(GridResourceType::Uranium, m_uraniumResources));
}

//load the coordinates of the resource sprites from the text file
void GridResourceMarket::loadMarketResource(std::string filename)
{
	setResourceMarket();

	std::ifstream file;
	file.open(filename);

	if (!file)
	{
		std::cout << filename << " is an invalid file name." << std::endl;
		return;
	}

	char delimiter = ',';
	//store strings seperated by comma into the vector
	std::vector<std::string> fileStrings;
	while (!file.eof())
	{
		std::string str;
		getline(file, str);
		std::stringstream stream(str);
		//split the string from the text file and put those strings in a vector
		while (getline(stream, str, delimiter))
		{
			fileStrings.push_back(str);
		}

		//set coal sprite positions
		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			float x = stof(fileStrings[i].substr(0, fileStrings[i].find('-')));
			float y = stof(fileStrings[i].substr(fileStrings[i].find('-') + 1));
			m_coalResources[i]->getResourceSprite().setPosition(x, y);
		}
		str.clear();
		fileStrings.clear();

		//get the next line of the file which are coordinates for oil
		getline(file, str);
		std::stringstream stream2(str);
		//split the string from the text file and put those strings in a vector
		while (getline(stream2, str, delimiter))
		{
			fileStrings.push_back(str);
		}

		//set oil sprite positions
		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			float x = stof(fileStrings[i].substr(0, fileStrings[i].find('-')));
			float y = stof(fileStrings[i].substr(fileStrings[i].find('-') + 1));
			m_oilResources[i]->getResourceSprite().setPosition(x, y);			
		}
		str.clear();
		fileStrings.clear();

		//get the next line of the file which are coordinates for garbage
		getline(file, str);
		std::stringstream stream3(str);
		//split the string from the text file and put those strings in a vector
		while (getline(stream3, str, delimiter))
		{
			fileStrings.push_back(str);
		}

		//set garbage sprite positions
		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			float x = stof(fileStrings[i].substr(0, fileStrings[i].find('-')));
			float y = stof(fileStrings[i].substr(fileStrings[i].find('-') + 1));
			m_garbageResources[i]->getResourceSprite().setPosition(x, y);
		}
		str.clear();
		fileStrings.clear();

		//get the next line of the file which are coordinates for uranium
		getline(file, str);
		std::stringstream stream4(str);
		//split the string from the text file and put those strings in a vector
		while (getline(stream4, str, delimiter))
		{
			fileStrings.push_back(str);
		}

		//set uranium sprite positions
		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			float x = stof(fileStrings[i].substr(0, fileStrings[i].find('-')));
			float y = stof(fileStrings[i].substr(fileStrings[i].find('-') + 1));
			m_uraniumResources[i]->getResourceSprite().setPosition(x, y);
		}

		break;
	}
}

//create the coal resources, true means they are available for purchase at the start of the game
void GridResourceMarket::createCoalResources()
{
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 1));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 1));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 1));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 2));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 2));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 2));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 3));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 3));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 3));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 4));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 4));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 4));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 5));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 5));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 5));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 6));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 6));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 6));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 7));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 7));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 7));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 8));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 8));
	m_coalResources.push_back(std::make_shared<GridResource>(GridResourceType::Coal, true, 8));

	for (auto& resource : m_coalResources)
		resource->getResourceSprite().setTexture(ResourceHolder::Instance()->get(Textures::Coal));
		
}

//create objects for oil resource
void GridResourceMarket::createOilResources()
{
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 1));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 1));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 1));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 2));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 2));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, false, 2));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 3));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 3));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 3));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 4));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 4));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 4));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 5));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 5));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 5));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 6));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 6));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 6));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 7));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 7));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 7));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 8));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 8));
	m_oilResources.push_back(std::make_shared<GridResource>(GridResourceType::Oil, true, 8));

	for (auto& resource : m_oilResources)
		resource->getResourceSprite().setTexture(ResourceHolder::Instance()->get(Textures::Oil));

}

//create objects for garbage resource
void GridResourceMarket::createGarbageResources()
{
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 1));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 1));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 1));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 2));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 2));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 2));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 3));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 3));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 3));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 4));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 4));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 4));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 5));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 5));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 5));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 6));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 6));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, false, 6));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 7));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 7));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 7));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 8));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 8));
	m_garbageResources.push_back(std::make_shared<GridResource>(GridResourceType::Garbage, true, 8));

	for(auto& resource : m_garbageResources)
		resource->getResourceSprite().setTexture(ResourceHolder::Instance()->get(Textures::Garbage));
}

//create objects for uranium resource
void GridResourceMarket::createUraniumResources()
{
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 1));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 2));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 3));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 4));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 5));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 6));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 7));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 8));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 10));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, false, 12));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, true, 14));
	m_uraniumResources.push_back(std::make_shared<GridResource>(GridResourceType::Uranium, true, 16));

	for(auto& resource : m_uraniumResources)
		resource->getResourceSprite().setTexture(ResourceHolder::Instance()->get(Textures::Uranium));
}

void GridResourceMarket::reSupplyResource(GridResourceType type, int amount)
{
	auto resources = m_market.at(type);
	for (size_t i = resources.size() - 1; i >= 0; i--)
	{
		//if theres no more of the resource to supply
		if (amount == 0)
			break;

		if (!resources[i]->getIsAvailable())
		{
			resources[i]->setAvailability(true);
			amount--;
		}
	}
}

//draw all the resources if they are available for purchase
void GridResourceMarket::drawResourceMarket(sf::RenderWindow *&mainWindow)
{
	for (auto& resource : m_coalResources)
	{
		if (resource->getIsAvailable())
			mainWindow->draw(resource->getResourceSprite());
	}

	for (auto& resource : m_oilResources)
	{
		if (resource->getIsAvailable())
			mainWindow->draw(resource->getResourceSprite());
	}

	for (auto& resource : m_garbageResources)
	{
		if (resource->getIsAvailable())
			mainWindow->draw(resource->getResourceSprite());
	}

	for (auto& resource : m_uraniumResources)
	{
		if (resource->getIsAvailable())
			mainWindow->draw(resource->getResourceSprite());
	}
}

//remove resources from the market
bool GridResourceMarket::removeResourcesFromMarket(GridResourceType type, int amount)
{
	int count = 0;
	if (type == GridResourceType::Coal)
	{
		for (auto& resource : m_coalResources)
			if (resource->getIsAvailable())
			{
				resource->setAvailability(false);
				count++;
				if (count == amount)
					break;
			}
				
	}
	else if (type == GridResourceType::Oil)
	{
		for (auto& resource : m_oilResources)
			if (resource->getIsAvailable())
			{
				resource->setAvailability(false);
				count++;
				if (count == amount)
					break;
			}
	}
	else if (type == GridResourceType::Garbage)
	{
		for (auto& resource : m_garbageResources)
			if (resource->getIsAvailable())
			{
				resource->setAvailability(false);
				count++;
				if (count == amount)
					break;
			}
	}
	else if (type == GridResourceType::Uranium)
	{
		for (auto& resource : m_uraniumResources)
			if (resource->getIsAvailable())
			{
				resource->setAvailability(false);
				count++;
				if (count == amount)
					break;
			}
	}
	return true;
}

//returns number of resources available for a type
int GridResourceMarket::getAvailableResourceType(GridResourceType type)
{
	int count = 0;
	if (type == GridResourceType::Coal)
	{
		for (auto& resource : m_coalResources)
			if (resource->getIsAvailable())
				count++;
	}
	else if (type == GridResourceType::Oil)
	{
		for (auto& resource : m_oilResources)
			if (resource->getIsAvailable())
				count++;
	}
	else if (type == GridResourceType::Garbage)
	{
		for (auto& resource : m_garbageResources)
			if (resource->getIsAvailable())
				count++;
	}
	else if (type == GridResourceType::Uranium)
	{
		for (auto& resource : m_uraniumResources)
			if (resource->getIsAvailable())
				count++;
	}
	return count;
}

//gets the price by taking the cheapest resources of the type available
int GridResourceMarket::getPriceOfResources(GridResourceType type, int amount)
{
	int price = 0;
	//checks if there are not enough resources for the amount
	if (getAvailableResourceType(type) < amount)
	{
		return -1;
	}

	int counter = 0;
	if (type == GridResourceType::Coal)
	{
		for (auto resource : m_coalResources)
		{
			if (resource->getIsAvailable())
			{
				price += resource->getCost();
				counter++;
				if (counter == amount)
					break;
			}
		}
	}
	else if (type == GridResourceType::Oil)
	{
		for (auto resource : m_oilResources)
		{
			if (resource->getIsAvailable())
			{
				price += resource->getCost();
				counter++;
				if (counter == amount)
					break;
			}
		}
	}
	else if (type == GridResourceType::Garbage)
	{
		for (auto resource : m_garbageResources)
		{
			if (resource->getIsAvailable())
			{
				price += resource->getCost();
				counter++;
				if (counter == amount)
					break;
			}
		}
	}
	else if (type == GridResourceType::Uranium)
	{
		for (auto resource : m_uraniumResources)
		{
			if (resource->getIsAvailable())
			{
				price += resource->getCost();
				counter++;
				if (counter == amount)
					break;
			}
		}
	}

	return price;
}

int GridResourceMarket::getMaxCapacity(GridResourceType type)
{
	if (type == GridResourceType::Coal || type == GridResourceType::Oil || type == GridResourceType::Garbage)
		return RESOURCE;
	else if (type == GridResourceType::Uranium)
		return URANIUM;

	return 0;
}

GridResourceType GridResourceMarket::getResourceTypeByName(std::string name)
{
	//return coal by default
	GridResourceType resourceType = No_Resource;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	if (name == "coal")
		resourceType = Coal;
	else if (name == "oil")
		resourceType = Oil;
	else if (name == "garbage")
		resourceType = Garbage;
	else if (name == "uranium")
		resourceType = Uranium;

	return resourceType;
}

std::string GridResourceMarket::getResourceType(GridResourceType type)
{
	if (type == GridResourceType::Coal)
		return "Coal";
	else if (type == GridResourceType::Oil)
		return "Oil";
	else if (type == GridResourceType::Garbage)
		return "Garbage";
	else if (type == GridResourceType::Uranium)
		return "Uranium";
	
	return "No Resource";
}

