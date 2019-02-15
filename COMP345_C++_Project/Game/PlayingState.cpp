#include "PlayingState.h"

//globals
std::string mapFile;

PlayingState::PlayingState() : m_quit(false), m_playing(false), m_initialBuyingPhase(true)
{
	//instantiate the map manager and resouce market
	m_mapManager = std::make_shared<MapManager>();
	m_gridResourceMarket = std::make_shared<GridResourceMarket>();

	//set up the number of players and the map that will be played
	setUpGame();
}

PlayingState::~PlayingState()
{
	
}

//handles any keyboard or mouse events
void PlayingState::handle_events(sf::RenderWindow* mainWindow, sf::Event & currEvent)
{
	while (mainWindow->pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Escape)
			{
				setNextState(GameStates::INTRO);
				m_quit = true;
			}
			else if (currEvent.key.code == sf::Keyboard::Return)
			{
				m_playing = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			//show the name of a city by clicking on the first slot
			if (currEvent.type == sf::Event::MouseButtonReleased)
			{
				for (auto& cityPair : m_mapManager->getMap()->getCities())
				{
					auto city = cityPair.second;
					if (city->citySlots[0]->m_slotSprite.getGlobalBounds().contains((float)sf::Mouse::getPosition(*mainWindow).x, (float)sf::Mouse::getPosition(*mainWindow).y))
					{
						city->citySlots[0]->m_name[0] = toupper(city->citySlots[0]->m_name[0]);
						m_mapManager->getMap()->getCityText().setString(city->citySlots[0]->m_name);
					}
				}
			}
		break;
		}
	}
}

void PlayingState::logic()
{
	while (m_playing)
	{
		if (m_quit)
		{
			setNextState(GameStates::INTRO);
			break;
		}
		
		buyResourcesPhase();
		//testPlayerDriver();

		//do the initial city buying phase
		for (const auto &player : players)
		{
			
		}
	}
}

//draw the map/resources/player houses
void PlayingState::draw(sf::RenderWindow *mainWindow)
{
	//draw the map
	mainWindow->draw(m_mapManager->getMap()->getMapSprite());
	//draw the houses the player has on the map
	for (auto player : players) 
	{
		for (auto& citySlot : player->getOwnedCities())
		{
			mainWindow->draw(citySlot->m_slotSprite);
		}
	}
	//draw the resource market
	m_gridResourceMarket->drawResourceMarket(mainWindow);

	mainWindow->draw(m_mapManager->getMap()->getCityText());
}

//sets up the number of players the user specifies
void PlayingState::setNumOfPlayers()
{
	int numOfPlayers = 0;
	std::cout << "Enter number of players between 2 and 6." << std::endl;
	while (!(std::cin >> numOfPlayers) || numOfPlayers < 2 || numOfPlayers > 6)
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Enter a number between 2 and 6." << std::endl;
	}

	for (int i = 1; i <= numOfPlayers; i++)
	{
		std::shared_ptr<Player> player = std::make_shared<Player>("Player " + std::to_string(i + 1), i);
		players.push_back(player);
	}

	std::cout << players.size() << " player game" << std::endl;
	std::cout << std::endl;
}

//set up the map by reading from the map text file and load the resource market
void PlayingState::setUpMap()
{
	//show available maps
	std::cout << "Available maps: " << std::endl;
	for (size_t i = 0; i < m_mapManager->getAvailableMaps().size(); i++)
	{
		std::cout << i + 1 << ". " << m_mapManager->getAvailableMaps()[i] << std::endl;
	}

	int mapNum = 0;
	std::cout << "Enter the number of the map to play" << std::endl;
	while (!(std::cin >> mapNum) || mapNum < 0 || mapNum > (int)m_mapManager->getAvailableMaps().size())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Enter a number corresponding with a map." << std::endl;
	}

	//parse the map data and the set the coordinates of the regions
	std::string mapStr = m_mapManager->getAvailableMaps()[mapNum - 1];
	std::transform(mapStr.begin(), mapStr.end(), mapStr.begin(), ::tolower);
	//this will be "Maps/" + mapStr + ".txt"
	m_mapManager->loadMap("Maps/turkey.txt");

	//load map texture
	ResourceHolder::Instance()->loadTexture(Textures::Map, "Textures/Maps/" + mapStr + ".png");
	//set the map sprite 
	m_mapManager->getMap()->setMapSprite();

	//create the resource market and load data for resource market from file
	m_gridResourceMarket->loadMarketResource("Maps/turkeyResourceCoords.txt");
}

//sets up the players and starts the game
void PlayingState::setUpGame()
{
	setNumOfPlayers();
	setUpMap();
	std::cout << "Press enter to begin playing the game." << std::endl;
}

bool PlayingState::comparePriority(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2)
{
	if (player1->getOwnedCities().size() > player2->getOwnedCities().size())
		return true;
	
	if (player1->getOwnedCities().size() < player2->getOwnedCities().size())
		return false;

	//check power plants if tied
	return false;
}

void PlayingState::updatePlayerOrder(bool reverse)
{

}

void PlayingState::powerPlantAuctionPhase()
{
}

//buying resources test
void PlayingState::buyResourcesPhase()
{
	std::cout << "Buying resources phase: " << std::endl;
	int oil = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Oil);
	int coal = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Coal);
	int garbage = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Garbage);
	int uranium = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Uranium);
	
	for (auto& player : players)
	{
		std::cout << "Type the type of resource to buy" << std::endl;
		std::string resource;
		std::transform(resource.begin(), resource.end(), resource.begin(), ::tolower);
		while (!(std::cin >> resource) || (resource != "coal" && resource != "oil" && 
			resource != "garbage" && resource != "uranium"))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "That is an invalid resource. Input another resource." << std::endl;
		}

		std::cout << "Enter how many you would like to buy." << std::endl;
		int num = 0;
		GridResourceType type = m_gridResourceMarket->getResourceTypeByName(resource);
		//Ask again if the input is wrong or there isn't enough resources available in the market
		while (!(std::cin >> num) || !player->purchaseResource(m_gridResourceMarket, nullptr, type, num))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Enter a valid number of the resource to buy." << std::endl;
		}

		if (resource == "coal")
		{

		}
	}
}

void PlayingState::buildingPhase()
{
}

void PlayingState::bureaucracyPhase()
{
}

//test to place player houses
void PlayingState::playerDriver()
{
	std::map<std::string, std::shared_ptr<Map::City>>::iterator it;
	//TODO: Test auction
	int i = 1;
	for (it = m_mapManager->getMap()->getCities().begin(); it != m_mapManager->getMap()->getCities().end(); it++)
	{
		std::cout << i << ". " << it->first << std::endl;
		i++;
	}

	for (auto& player : players)
	{
		std::string city;
		std::cout << "Select city to buy." << std::endl;
		while (!(std::cin >> city) || m_mapManager->getMap()->getCityByName(city)->citySlots[2]->m_isOwned)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << city << " is already owned by somebody or invalid input. Pick another city." << std::endl;
		}

		auto pickedCity = m_mapManager->getMap()->getCities().at(city);
		int cost = m_mapManager->getShortestPathFromPlayer(player, pickedCity->m_cityName) + pickedCity->citySlots[2]->m_type;

		int buy = 0;
		std::cout << "Your cost is " << cost << ". You have " << player->getElektro() << ". Would you like to purchase?" << std::endl;
		while (!(std::cin >> buy) || buy < 0 || buy > 1)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Enter 1 for yes, 0 for no." << std::endl;
		}

		player->setElektro(cost);
		player->getOwnedCities().push_back(pickedCity->citySlots[2]);
		pickedCity->citySlots[2]->m_slotSprite.setTexture(player->getPlayerTexture());
		pickedCity->citySlots[2]->m_isOwned = true;
		std::cout << "Player " << player->getPlayerNumber() << " has " << player->getElektro() << " elektro left." << std::endl;
	}
	
}


