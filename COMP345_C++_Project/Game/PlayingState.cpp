#include "PlayingState.h"

PlayingState::PlayingState() : m_quit(false), m_playing(false)
{
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
			player->doPlayerTurn();
		}
	}
}

void PlayingState::draw(sf::RenderWindow *window)
{
	window->draw(m_sprite);
}

//sets up the players and starts the game
void PlayingState::setUpGame()
{
	int numOfPlayers = 0;
	std::cout << "Enter number of players" << std::endl;

	std::cin >> numOfPlayers;
	std::cout << players.size() << " player game" << std::endl;

	//initialize players
	for (int i = 0; i < numOfPlayers; i++)
	{
		std::unique_ptr<Player> player = std::make_unique<Player>("player "+std::to_string(i+1));
		players.push_back(std::move(player));
	}

	//parse the map data and the set the coordinates of the regions
	m_map = loadMap("Maps/2_player_map.txt");
	loadRegionCoords("Maps/2_player_map_coords.txt");

	std::cout << "Press enter to play the game or escape to quit" << std::endl;
}

//parse the file
Map PlayingState::loadMap(std::string filename)
{	
	//open the file
	std::ifstream file;
	try {
		file.open(filename);
	}
	catch (...)
	{
		std::cout << "Failed to open file " + filename + "." << std::endl;
	}

	//first line is number of regions
	std::string s;
	getline(file, s);

	//create the map
	Map map;

	char delimiter = ',';
	//this keeps track of which region we are at in the text file 
	int regionNumber = 1;
	//lines are seperated by regions
	while (!file.eof())
	{
		std::string s1;
		getline(file, s1);

		char regionType = s1.at(0);
		map.setRegion(regionType);

		//look at the other regions connected to the current region
		std::string number = "";
		for (int i = 4; i < s1.length(); i++)
		{
			if (s1.at(i) == delimiter)
			{
				//add an edge between the currennt region and it's adjacent regions
				int adjacentRegion = std::stoi(number);
				map.addEdge(regionNumber, adjacentRegion);
				number = "";
				continue;
			}
			number += s1.at(i);
		}
		
		//go to the next region (the next line) in the text file
		regionNumber++;
	}
	
	file.close();
	return map;
}

//parse the file with the region coordinates
void PlayingState::loadRegionCoords(std::string filename)
{
	//open the file
	std::ifstream file;
	try {
		file.open(filename);
	}
	catch (...)
	{
		std::cout << "Failed to open file " + filename + "." << std::endl;
	}

	char delimiter = ',';
	float x, y;
	//this keeps track of which region we are at in the text file (line 3 = region 3)
	int regionNumber = 0;
	while (!file.eof())
	{
		file >> x >> delimiter >> y;
		m_map.getRegions()[regionNumber]->m_xPos = x;
		m_map.getRegions()[regionNumber]->m_yPos = y;
		regionNumber++;
	}
}
