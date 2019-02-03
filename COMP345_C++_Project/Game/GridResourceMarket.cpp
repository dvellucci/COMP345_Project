#include "GridResourceMarket.h"

GridResourceMarket::GridResourceMarket()
{
	//m_coalResources.reserve(24);
}

GridResourceMarket::~GridResourceMarket()
{

}

void GridResourceMarket::loadMarketResource(std::string filename)
{
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

		for (size_t i = 0; i < fileStrings.size(); i++)
		{
			float x = stof(fileStrings[i].substr(0, fileStrings[i].find('-')));
			float y = stof(fileStrings[i].substr(fileStrings[i].find('-') + 1));
			m_coalResources[i]->getResourceSprite().setPosition(x, y);
		}
		break;
	}
}

//load the coal resources, true means they are available for purchase at the start of the game
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

	for (std::shared_ptr<GridResource>& resource : m_coalResources)
		resource->getResourceSprite().setTexture(ResourceHolder::Instance()->get(Textures::Coal));
		
}