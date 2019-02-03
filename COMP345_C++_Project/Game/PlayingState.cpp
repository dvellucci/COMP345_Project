#include "PlayingState.h"

//globals
std::string mapFile;

PlayingState::PlayingState() : m_quit(false), m_playing(false)
{
	//instantiate the map manager and resouce market
	m_mapManager = std::make_shared<MapManager>();
	m_gridResourceMarket = std::make_shared<GridResourceMarket>();

	//create the resources
	m_gridResourceMarket->createCoalResources();

	//set up the number of players and the map that will be played
	setUpGame();

	//might be usable
	//if (m_image.getPixel(sf::Mouse::getPosition(window).x - m_sprite.getPosition().x, sf::Mouse::getPosition(window).y - m_sprite.getPosition().y).a > 0)
}

PlayingState::~PlayingState()
{
	
}

void PlayingState::handle_events(sf::RenderWindow& window, sf::Event & currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Escape)
			{
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
				for (auto& city : m_mapManager->getMap()->getCities())
				{
					if (city->citySlots[0]->m_slotSprite.getGlobalBounds().contains((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y))
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
		
		//make each player do their turn
		for (const auto &player : players)
		{
		
		}
	}
}

void PlayingState::draw(sf::RenderWindow *window)
{
	//draw the map
	window->draw(m_mapManager->getMap()->getMapSprite());
	//draw the houses the player has on the map
	for (auto player : players) 
	{
		for (auto& citySlot : player->getOwnedCities())
		{
			window->draw(citySlot->m_slotSprite);
		}
	}

	for (auto resource : m_gridResourceMarket->getCoalResources())
	{
		if(resource->getIsAvailable())
			window->draw(resource->getResourceSprite());
	}

	window->draw(m_mapManager->getMap()->getCityText());
}

//sets up the players and starts the game
void PlayingState::setUpGame()
{
	int numOfPlayers = 0;
	std::cout << "Enter number of players" << std::endl;

	std::cin >> numOfPlayers;

	//initialize players
	for (int i = 1; i <= numOfPlayers; i++)
	{
		//std::string playerSprite = "Player_" + std::to_string(i);
		int tex = atoi("Player_" + i);
		std::shared_ptr<Player> player = std::make_shared<Player>("Player "+std::to_string(i+1));
		players.push_back(player);
	}

	//set player house sprites
	for (auto player : players) {

	}

	std::cout << players.size() << " player game" << std::endl;
	std::cout << std::endl;

	//show available maps
	std::cout << "Available maps: " << std::endl;
	for (size_t i = 0; i < m_mapManager->getAvailableMaps().size(); i++)
	{
		std::cout << i+1 << ". " << m_mapManager->getAvailableMaps()[i] << std::endl;
	}

	//load the map the players want
	int mapNum = 0;
	std::cout << "Enter the number of the map to play" << std::endl;
	std::cin >> mapNum;

	//parse the map data and the set the coordinates of the regions
	std::string mapStr = m_mapManager->getAvailableMaps()[mapNum - 1];
	std::transform(mapStr.begin(), mapStr.end(), mapStr.begin(), ::tolower);
	m_mapManager->loadMap("Maps/" + mapStr + ".txt");
	//load map texture
	ResourceHolder::Instance()->loadTexture(Textures::Map, "Textures/Maps/" + mapStr + ".png");
	//set the map sprite 
	m_mapManager->getMap()->setMapSprite();

	//load data for resource market from file
	m_gridResourceMarket->loadMarketResource("Maps/" + mapStr + "ResourceCoords.txt");

	std::cout << "Press enter to play the game or escape to quit" << std::endl;
}


