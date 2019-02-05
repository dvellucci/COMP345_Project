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

