#include "PlayingState.h"

std::string mapFile;

PlayingState::PlayingState() : m_quit(false), m_playing(false)
{
	m_mapManager = std::make_shared<MapManager>();
	setUpGame();

	m_sprite.setTexture(ResourceHolder::Instance()->get(Textures::Title));
	//might be usable
	//if (m_image.getPixel(sf::Mouse::getPosition(window).x - m_sprite.getPosition().x, sf::Mouse::getPosition(window).y - m_sprite.getPosition().y).a > 0)
}

PlayingState::~PlayingState()
{
	//players.clear();
}

void PlayingState::handle_events(sf::RenderWindow & window, sf::Event & currEvent)
{
	while (window.pollEvent(currEvent))
	{
		switch (currEvent.type)
		{
		case sf::Event::KeyPressed:
			if (currEvent.key.code == sf::Keyboard::Escape)
			{
				setNextState(GameStates::EXIT);
			}
			else if (currEvent.key.code == sf::Keyboard::Return)
			{
				m_playing = true;
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
	window->draw(m_mapManager->getMap()->getMapSprite());
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
		std::shared_ptr<Player> player = std::make_shared<Player>("player "+std::to_string(i+1));
		
		players.push_back(std::move(player));
	}

	//set player power plant sprites
	for (auto player : players) {

	}

	std::cout << players.size() << " player game" << std::endl;
	std::cout << std::endl;

	//show available maps
	std::cout << "Available maps: " << std::endl;
	for (int i = 0; i < m_mapManager->getAvailableMaps().size(); i++)
	{
		std::cout << i+1 << ". " << m_mapManager->getAvailableMaps()[i] << std::endl;
	}

	//load the map the players want
	std::cout << "Enter the name of the map to play" << std::endl;
	std::cin >> mapFile;

	//parse the map data and the set the coordinates of the regions
	std::transform(mapFile.begin(), mapFile.end(), mapFile.begin(), ::tolower);
	m_mapManager->loadMap("Maps/" + mapFile + ".txt");

	//load map texture
	ResourceHolder::Instance()->loadTexture(Textures::Map, "Textures/Maps/" + mapFile + ".png");
	//global vars to be used for window size
	//mapWidth = ResourceHolder::Instance()->get(Textures::Map).getSize().x;
	//mapHeight = ResourceHolder::Instance()->get(Textures::Map).getSize().y;
	//set the map sprite 
	m_mapManager->getMap()->setMapSprite();

	std::cout << "Press enter to play the game or escape to quit" << std::endl;
}


