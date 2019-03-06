#include "MapManager.h"


using namespace std;

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

		if (fileStrings.size() < 5 || isdigit(fileStrings[0][0]))
		{
			std::cout << "Invalid file data." << std::endl;
			return NULL;
		}

		//get city slot coordinates
		float x1 = stof(fileStrings[1].substr(0, fileStrings[1].find('-')));
		float y1 = stof(fileStrings[1].substr(fileStrings[1].find('-') + 1));

		float x2 = stof(fileStrings[2].substr(0, fileStrings[2].find('-')));
		float y2 = stof(fileStrings[2].substr(fileStrings[2].find('-') + 1));

		float x3 = stof(fileStrings[3].substr(0, fileStrings[3].find('-')));
		float y3 = stof(fileStrings[3].substr(fileStrings[3].find('-') + 1));

		//the first string is the city name
		auto newCity = m_map->setCity(fileStrings[0], x1, y1, x2, y2, x3, y3);

		std::list<std::string> cityList;
		//set the connections of the city which start at the 4th index of the string read from the file
		for (size_t i = 4; i < fileStrings.size(); i++)
		{
			//create the connection between the 2 cities
			int cost = stoi(fileStrings[i].substr(0, fileStrings[i].find('-')));
			std::string city = fileStrings[i].substr(fileStrings[i].find('-') + 1);
			std::shared_ptr<Connection> connection = std::make_shared<Connection>(fileStrings[0], city, cost);
			newCity->getConnections().push_back(connection);

			cityList.push_back(city);
		}
		//make an adjaceny list for the graph
		m_mapGraph.emplace(make_pair(fileStrings[0], cityList));
		cityList.clear();
		fileStrings.clear();
	}

	if (!isMapValid(m_mapGraph, m_mapGraph.begin()->first))
	{
		std::cout << "This map is not connected." << std::endl;
		return NULL;
	}

	return m_map;
}


void MapManager::setConnection(std::string city1, std::string city2, int cost)
{
}

bool contains(std::list<std::string> list, std::string element) {
	return (std::find(list.begin(), list.end(), element) != list.end());
}

bool MapManager::isMapValid(std::map<std::string, std::list<std::string>> m_mapGraph, std::string node)
{
	//std::list<std::string> discovered;
	m_discoveredNodes.clear();
	auto res = depthFirstSearch(m_mapGraph, m_mapGraph.begin()->first);
	return res.size() == m_mapGraph.size();
}

std::list<std::string> MapManager::depthFirstSearch(std::map<std::string, std::list<std::string>> m_mapGraph, std::string node)
{
	/*
	1  procedure DFS(G,v):
	2      label v as discovered
	3      for all edges from v to w in G.adjacentEdges(v) do
	4          if vertex w is not labeled as discovered then
	5              recursively call DFS(G,w)
	*/
	if (!contains(m_discoveredNodes, node)) {
		m_discoveredNodes.push_back(node);
	}
	try {
		for (std::string city : m_mapGraph.at(node)) {
			if (!contains(m_discoveredNodes, city)) {
				m_discoveredNodes.push_back(city);
				depthFirstSearch(m_mapGraph, city);
			}
		}
	}
	catch (const std::out_of_range& err) {
		//m_mapGraph.at(node) failed, graph does not have this node
		std::cout << "Node not found! Map may be invalid" << '\n';
	}
	return m_discoveredNodes;
}

//Credit for function: https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/
//get shortest path between 2 cities
int MapManager::getShortestPath(std::string fromCity, std::string toCity)
{
	
	// If any city was not found
	std::transform(fromCity.begin(), fromCity.end(), fromCity.begin(), ::tolower);
	if (m_map->getCities().find(fromCity) == m_map->getCities().end() || m_map->getCities().find(toCity) == m_map->getCities().end()) 
	{
		return -1;
	}

	// Prepare required information
	std::map<std::string, std::shared_ptr<CityComparable>> citiesComparable;

	// for each city in the game, create the comparable object
	for (auto city = m_map->getCities().begin(); city != m_map->getCities().end(); ++city) {
		citiesComparable[city->first] = std::make_shared<CityComparable>(m_map->getCities()[city->first]);
	}
	
	// Create priority queue
	std::priority_queue<std::shared_ptr<CityComparable>, vector<std::shared_ptr<CityComparable>>, CityCostComparator> pQueue;

	// Prepare first city
	citiesComparable[fromCity]->cost = 0;
	citiesComparable[fromCity]->visited = VISITING;
	pQueue.push(citiesComparable[fromCity]);

	while (!pQueue.empty())
	{
		// Get top
		shared_ptr<CityComparable> topCityComparable = pQueue.top();

		// Mark visited
		topCityComparable->visited = VISITED;

		// If found my target, no need to continue calculating the other path
		if (topCityComparable->city->m_cityName == toCity)
		{
			// Prepare stack
			std::stack<string> path;
			auto tmpCity = citiesComparable[toCity];

			while (tmpCity)
			{
				path.push(tmpCity->city->m_cityName);
				tmpCity = citiesComparable[tmpCity->parent];
			}

			return topCityComparable->cost;
		}

		// Remove top
		pQueue.pop();

		// Get neighbor connections
		vector<shared_ptr<Connection>> topConnections = topCityComparable->city->getConnections();

		// Loop on connections
		for (auto connection = topConnections.begin(); connection != topConnections.end(); ++connection)
		{
			// Get opposite city
			std::string oppositeCityStr = m_map->getOppositeOf(**connection, topCityComparable->city->m_cityName);
			auto oppositeCity = m_map->getCityByName(oppositeCityStr);
			// Get city cost comparable
			shared_ptr<CityComparable> oppositeCityComparable = citiesComparable[oppositeCity->m_cityName];

			// If not visited
			if (oppositeCityComparable->visited != VISITED)
			{
				// Calculate path
				int pathCost = (*connection)->getCost() + topCityComparable->cost;

				// If new path is less then update
				if (pathCost < oppositeCityComparable->cost)
				{
					// If unvisited
					if (oppositeCityComparable->visited == UNVISITED) 
					{
						oppositeCityComparable->cost = pathCost;
						oppositeCityComparable->parent = topCityComparable->city->m_cityName;
					}
					else
					{
						// Empty queue into a tmp vector, make the changes then reput everything into the queue
						vector<shared_ptr<CityComparable>> tmpVector;
						while (!pQueue.empty()) { tmpVector.push_back(pQueue.top()); pQueue.pop(); }
						oppositeCityComparable->cost = pathCost;
						oppositeCityComparable->parent = topCityComparable->city->m_cityName;
						while (!tmpVector.empty()) { pQueue.push(tmpVector[tmpVector.size() - 1]); tmpVector.pop_back(); }
					}
				}
				// If unvisited, add to queue
				if (oppositeCityComparable->visited == UNVISITED)
					pQueue.push(oppositeCityComparable);

				// Mark visiting
				oppositeCityComparable->visited = VISITING;
			}
		}

	}

	// Invalid
	return -1;
}

//get smallest elektro cost to a city from any of the player's cities
int MapManager::getShortestPathFromPlayer(std::shared_ptr<Player> player, std::string toCity)
{
	// If no houses
	if (player->getOwnedCities().size() == 0) 
		return 0;

	int minCost = getShortestPath(player->getOwnedCities()[0]->getName(), toCity);

	//for every player city, see which one gives the shortest path to the city that the player wants to buy
	for (size_t i = 1; i < player->getOwnedCities().size(); i++)
	{
		int pathCost = getShortestPath(player->getOwnedCities()[i]->getName(), toCity);
		if (minCost > pathCost)
			minCost = pathCost;
	}
	return minCost;
}
