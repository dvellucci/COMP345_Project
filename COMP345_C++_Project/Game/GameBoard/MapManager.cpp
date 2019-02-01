#include "MapManager.h"

//std::string mapFile;

MapManager::MapManager()
{
	m_map = std::make_shared<Map>();
}

MapManager::~MapManager()
{
}

std::shared_ptr<Map> MapManager::loadMap(std::string filename)
{
	//open the file
	std::ifstream file;
	file.open(filename);

	if (!file)
	{
		std::cout << "That is an invalid file name." << std::endl;
		return NULL;
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

		//get city slot coordinates
		float x1 = stof(fileStrings[1].substr(0, fileStrings[1].find('-')));
		float y1 = stof(fileStrings[1].substr(fileStrings[1].find('-') + 1));

		float x2 = stof(fileStrings[2].substr(0, fileStrings[2].find('-')));
		float y2 = stof(fileStrings[2].substr(fileStrings[2].find('-') + 1));

		float x3 = stof(fileStrings[3].substr(0, fileStrings[3].find('-')));
		float y3 = stof(fileStrings[3].substr(fileStrings[3].find('-') + 1));

		//the first string is the city name
		m_map->setCity(fileStrings[0], x1, y1, x2, y2, x3, y3);

		std::list<std::string> cityList;
		//set the connections of the city
		for (size_t i = 4; i < fileStrings.size(); i++)
		{
			//create the connection between the 2 cities
			int cost = stoi(fileStrings[i].substr(0, fileStrings[i].find('-')));
			std::string city = fileStrings[i].substr(fileStrings[i].find('-') + 1);
			std::shared_ptr<Connection> connection = std::make_shared<Connection>(fileStrings[0], city, cost);
			m_connections.push_back(connection);

			cityList.push_back(city);
		}
		//make an adjaceny list for the graph
		m_mapGraph.emplace(make_pair(fileStrings[0], cityList));
		cityList.clear();
		fileStrings.clear();
	}
	return m_map;
}

void MapManager::loadCityCoords(std::string filename)
{
}

void MapManager::setConnection(std::string city1, std::string city2, int cost)
{
}

void MapManager::DFSUtil(std::string city, bool visitied[])
{
	

}
