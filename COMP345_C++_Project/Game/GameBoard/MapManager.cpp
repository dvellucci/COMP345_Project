#include "MapManager.h"

using namespace std;

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

	int line = 1;
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
		graph.push_back(cityList);
		cityList.clear();
		fileStrings.clear();
	}
	return m_map;
}


void MapManager::setConnection(std::string city1, std::string city2, int cost)
{
}

void MapManager::DFSUtil(std::string city, std::set<std::string> set)
{

}

//Credit for function: https://github.com/amirbawab/PowerGrid/blob/master/Map.cpp
//get shortest path between 2 cities
int MapManager::getShortestPath(std::string fromCity, std::string toCity)
{
	// Status
	static const int UNVISITED = 0;
	static const int VISITING = 1;
	static const int VISITED = 2;

	class  CityCostComparable {
	public:
		int cost = std::numeric_limits<int>::max();
		int visited = UNVISITED;
		std::string parent;
		std::shared_ptr<Map::City> city;
		CityCostComparable(std::shared_ptr<Map::City> city) : city(city) {};
	};

	struct CityCostComparator {
		bool operator()(const std::shared_ptr<CityCostComparable> lhs, const std::shared_ptr<CityCostComparable> rhs) const {
			return lhs->cost > rhs->cost;
		}
	};

	
	// If any city was not found
	if (m_map->getCities().find(fromCity) == m_map->getCities().end() || m_map->getCities().find(toCity) == m_map->getCities().end()) 
	{
		std::cout << "Cannot find " << fromCity << " or " << toCity << "." << std::endl;
		return -1;
	}

	// Prepare required information
	std::map<std::string, std::shared_ptr<CityCostComparable>> citiesComparable;

	// Create comparable cities
	for (auto city = m_map->getCities().begin(); city != m_map->getCities().end(); ++city) {
		citiesComparable[city->first] = make_shared<CityCostComparable>(m_map->getCities()[city->first]);
	}
	
	// Create priority queue
	std::priority_queue<shared_ptr<CityCostComparable>, vector<shared_ptr<CityCostComparable>>, CityCostComparator> pQueue;

	// Prepare first city
	citiesComparable[fromCity]->cost = 0;
	citiesComparable[fromCity]->visited = VISITING;
	pQueue.push(citiesComparable[fromCity]);

	while (!pQueue.empty())
	{
		// Get top
		shared_ptr<CityCostComparable> topCityCostComparable = pQueue.top();

		// Mark visited
		topCityCostComparable->visited = VISITED;

		// If found my target, no need to continue calculating the other path
		if (topCityCostComparable->city->m_cityName == toCity)
		{
			// Prepare stack
			std::stack<string> path;
			auto tmpCity = citiesComparable[toCity];

			// Print the path
			while (tmpCity)
			{
				path.push(tmpCity->city->m_cityName);
				tmpCity = citiesComparable[tmpCity->parent];
			}
			cout << "Possible path:";
			while (!path.empty())
			{
				cout << "\t" << path.top();
				path.pop();
			}
			cout << endl;

			return topCityCostComparable->cost;
		}

		// Remove top
		pQueue.pop();

		// Get neighbor connections
		vector<shared_ptr<Connection>> topConnections = topCityCostComparable->city->getConnections();

		// Loop on connections
		for (auto connection = topConnections.begin(); connection != topConnections.end(); ++connection)
		{
			// Get opposite city
			std::string oppositeCityStr = m_map->getOppositeOf(**connection, topCityCostComparable->city->m_cityName);
			auto oppositeCity = m_map->getCityByName(oppositeCityStr);
			// Get city cost comparable
			shared_ptr<CityCostComparable> oppositeCityCostComparable = citiesComparable[oppositeCity->m_cityName];

			// If not visited
			if (oppositeCityCostComparable->visited != VISITED)
			{
				// Calculate path
				int pathCost = (*connection)->getCost() + topCityCostComparable->cost;

				// If new path is less then update
				if (pathCost < oppositeCityCostComparable->cost)
				{
					// If unvisited
					if (oppositeCityCostComparable->visited == UNVISITED) 
					{
						oppositeCityCostComparable->cost = pathCost;
						oppositeCityCostComparable->parent = topCityCostComparable->city->m_cityName;
					}
					else
					{
						// Empty queue into a tmp vector, make the changes then reput everything into the queue
						vector<shared_ptr<CityCostComparable>> tmpVector;
						while (!pQueue.empty()) { tmpVector.push_back(pQueue.top()); pQueue.pop(); }
						oppositeCityCostComparable->cost = pathCost;
						oppositeCityCostComparable->parent = topCityCostComparable->city->m_cityName;
						while (!tmpVector.empty()) { pQueue.push(tmpVector[tmpVector.size() - 1]); tmpVector.pop_back(); }
					}
				}
				// If unvisited, add to queue
				if (oppositeCityCostComparable->visited == UNVISITED)
					pQueue.push(oppositeCityCostComparable);

				// Mark visiting
				oppositeCityCostComparable->visited = VISITING;
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

	int minCost = getShortestPath(player->getOwnedCities()[0]->m_name, toCity);

	for (size_t i = 1; i < player->getOwnedCities().size(); i++)
	{
		int pathCost = getShortestPath(player->getOwnedCities()[i]->m_name, toCity);
		if (minCost > pathCost)
			minCost = pathCost;
	}
	return minCost;
}
