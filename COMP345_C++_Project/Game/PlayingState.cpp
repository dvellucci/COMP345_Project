#include "PlayingState.h"

//globals
std::string mapFile;

PlayingState::PlayingState() : m_quit(false), m_playing(false), m_firstTurn(true)
{
	//instantiate the map manager and resouce market
	m_mapManager = std::make_shared<MapManager>();
	m_gridResourceMarket = std::make_shared<GridResourceMarket>();
	m_deckManager = std::make_shared<Deck>();

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
		
		phase1Start();
	}
}

//draw the map/resources/player houses
void PlayingState::draw(sf::RenderWindow *mainWindow)
{
	//draw the map
	mainWindow->draw(m_mapManager->getMap()->getMapSprite());

	//draw the houses the player has on the map
	for (auto player : m_players) 
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
		std::shared_ptr<Player> player = std::make_shared<Player>(i);
		m_players.push_back(player);
	}

	std::cout << m_players.size() << " player game" << std::endl;
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
	m_deckManager->setUpDeck();

	//set up the player order container and randomize it for the first turn
	for (auto& player : m_players)
		m_playerOrder.push_back(player);
	std::random_shuffle(m_playerOrder.begin(), m_playerOrder.end());

	std::cout << "Press enter to begin playing the game." << std::endl;
}

void PlayingState::phase1Start()
{
	std::cout << "Starting phase 1." << std::endl;

	if (!m_firstTurn)
		updatePlayerOrder(false);

	m_currentPlayer = m_playerOrder[0];

	std::cout << "Current player order:" << std::endl;
	for (auto player : m_playerOrder)
		std::cout << "Player " << player->getPlayerNumber() << std::endl;

	doPhase2();
}

void PlayingState::updatePlayerOrder(bool reverse)
{
	//sort the player order based on who has the highest power plant
	std::sort(m_playerOrder.begin(), m_playerOrder.end(), checkPlayerPriority());

	//reverse the order (used in step 4)
	if (reverse)
		std::reverse(m_playerOrder.begin(), m_playerOrder.end());
}

void PlayingState::doPhase2()
{
	printGameInfo();
	phase2Start();
}

void PlayingState::phase2Start()
{
	//sort the player
	std::cout << "Beginning step 2. The power plant auction phase." << std::endl << std::endl;;

	//set the attribute that the players can bid to true
	for (auto& player : m_playerOrder)
	{
		m_canPlayerBuy[player.get()] = true;
	}
	phase2StartAuction();
}

void PlayingState::phase2StartAuction()
{
	int isPlayerBidding = 1;
	if (m_firstTurn)
	{
		std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " turn." << std::endl;
		std::cout << "This is the first turn. Each player must buy a power plant." << std::endl << std::endl;
	}
	else
	{
		std::cout << "Would player " << m_currentPlayer->getPlayerNumber() << " like to start an auction? Enter 1 for yes, 0 for no." << std::endl;
		while (!(std::cin >> isPlayerBidding) || (isPlayerBidding != 0 && isPlayerBidding != 1))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Enter 1 for yes, 0 for no." << std::endl;
		}
	}

	if (isPlayerBidding == 0)
	{
		phase2BidOnPlant(0, 0, true);
	}
	else
	{
		std::cout << "Pick a plant to bid on by entering it's corresponding number." << std::endl;
		m_deckManager->outputMarket();
		int index = 0;
		while (!(std::cin >> index) || index < 0 || index >= m_deckManager->getPowerPlantMarket().size())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid number for the power plant. Enter a valid number." << std::endl;
		}

		std::cout << "Place a bid for the power plant." << std::endl;
		int bid = 0;
		while (!(std::cin >> bid))
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input for a bid. Place a bid for the power plant." << std::endl;
		}

		phase2BidOnPlant(index, bid, false);
	}
	std::cout << std::endl;
}

void PlayingState::phase2BidOnPlant(int index, int bid, bool skipBid)
{
	m_powerPlantIndex = index;
	//if the current player is going to skip the bidding this turn
	if (skipBid)
	{
		//make it so the current player cannot bid for the rest of the turn
		m_canPlayerBuy[m_currentPlayer.get()] = false;

		//go to the next player and check if that player will start an auction on a power plant
		for (auto& player : m_playerOrder)
		{
			if (m_canPlayerBuy[player.get()])
			{
				m_currentPlayer = player;
				return phase2StartAuction();
			}
		}
		//No more players can bid which means phase 3 can start
		return phase2End();
	}

	//the powerplant the current player bids on
	auto powerPlant = m_deckManager->getPowerPlantCard(index);

	//check if the player has enough elektro for the bid or if the bid is a high enough value
	if (bid > m_currentPlayer->getElektro())
	{
		std::cout << "You don't have enough elektro for this bid." << std::endl;
		std::cout << std::endl;
		return phase2StartAuction();
	}
	else if (bid < powerPlant->getPowerPlantPrice())
	{
		std::cout << "The mininum bid for this power plant is " << powerPlant->getPowerPlantPrice() << "." << std::endl << std::endl;
		std::cout << std::endl;
		return phase2StartAuction();
	}

	//show the info of the power plant being put on auction
	std::cout << std::endl;
	std::cout << "The power plant being put on auction: " << std::endl;
    m_deckManager->outputPowerPlant(powerPlant);

	//reset bid attribute of other players if they can purchase this round
	for (auto& player : m_players)
	{
		if (m_canPlayerBuy[player.get()])
			m_canPlayerBid[player.get()] = true;
		else
			m_canPlayerBid[player.get()] = false;
	}

	std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " makes the initial bid of " << bid << "." << std::endl;

	m_currentBid = bid;
	m_highestBidder = m_currentPlayer;
	m_initialBid = true;
	phase2NextBid();
}

void PlayingState::phase2NextBid(int bid)
{
	//get the index of the next player that is not the current player and check if they will bid on the auction
	int nextIndex = (distance(m_playerOrder.begin(), find(m_playerOrder.begin(), m_playerOrder.end(), m_currentPlayer)) + 1) % m_playerOrder.size();
	while (m_playerOrder[nextIndex] != m_currentPlayer)
	{
		//check if the next player can bid and check if they have enough elektro to beat the current bid
		if (m_canPlayerBid[m_playerOrder[nextIndex].get()] && m_playerOrder[nextIndex]->getElektro() > m_currentBid)
		{
			m_currentPlayer = m_playerOrder[nextIndex];
			std::cout << std::endl;
			std::cout << "Does player " << m_currentPlayer->getPlayerNumber() << " want to bid on this auction?" << std::endl;
			std::cout << "Current bid is at " << m_currentBid << ". Enter 1 for yes, 0 for no." << std::endl;
			int isPlayerBidding = 0;
			while (!(std::cin >> isPlayerBidding) || (isPlayerBidding != 0 && isPlayerBidding != 1) || m_currentPlayer->getElektro() < m_currentBid)
			{
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cout << "Invalid input for a bid. Enter 1 for yes, 0 for no." << std::endl;
			}

			//if player wants to bid
			if (isPlayerBidding == 1)
			{
				std::cout << "Place a bid for the power plant." << std::endl;
				int bid = 0;
				while (!(std::cin >> bid) || bid <= m_currentBid || bid > m_currentPlayer->getElektro())
				{
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cout << "Invalid input for a bid. Place a bid for the power plant. Current bid is at " << m_currentBid << "." << std::endl;
				}

				//set the new highest bid and make the current player the highest bidder
				m_currentBid = bid;
				m_highestBidder = m_currentPlayer;
			}
			else //if player doesn't want to bid, set their can bid attribute to false for this auction
			{
				m_canPlayerBid[m_currentPlayer.get()] = false;
			}
		}
		//go to next player
		nextIndex = (nextIndex + 1) % m_playerOrder.size();
	}

	//if no players want to bid for this auction, give the power plant to the winner
	if (m_currentPlayer.get() == m_highestBidder.get())
	{
		// Check if the current player won the bidding round
		std::cout << std::endl;
		std::cout << "The winner of this auction is player " << m_currentPlayer->getPlayerNumber() << std::endl << std::endl;
		m_canPlayerBuy[m_currentPlayer.get()] = false;

		//give the player the new power plant
		if(m_currentPlayer->getPowerPlants().size() == 3)
			m_currentPlayer->replacePowerPlant(m_deckManager, m_powerPlantIndex, m_currentBid);
		else
			m_currentPlayer->buyPowerPlant(m_deckManager, m_powerPlantIndex, m_currentBid);

		//draw a new card for the deck
		m_deckManager->drawCard();

		phase2EndBid();
	}
}

void PlayingState::phase2EndBid()
{
	//check who will begin the next bid war
	m_currentPlayer = nullptr;
	for (auto& player : m_playerOrder)
	{
		if (m_canPlayerBuy[player.get()])
		{
			m_currentPlayer = player;
			break;
		}
	}

	//if m_currentPlayer is empty then there are no more players that can start an auction, so end phase 2
	if (m_currentPlayer == nullptr) 
	{
		//end phase 2 of the turn here
		return phase2End();
	}

	m_currentBid = 0;
	return phase2StartAuction();
}

void PlayingState::phase2End()
{
	//check for step 3 card

	m_firstTurn = false;
	m_powerPlantIndex = 0;
	//start phase 3
	doPhase3();
}

void PlayingState::doPhase3()
{
	std::cout << "Press enter to continue to phase 3." << std::endl;
	m_playing = false;
	while (!m_playing);
	std::cout << "Phase 3 of the turn will now begin." << std::endl;
	
	m_currentPlayer = m_playerOrder[0];
	m_resourceIndex = 0;
	m_powerPlantIndex = 0;

}

//buying resources test
void PlayingState::buyResourcesPhase()
{
	std::cout << "Buying resources phase: " << std::endl;
	int oil = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Oil);
	int coal = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Coal);
	int garbage = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Garbage);
	int uranium = m_gridResourceMarket->getAvailableResourceType(GridResourceType::Uranium);
	
	for (auto& player : m_players)
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

	for (auto& player : m_players)
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

void PlayingState::printGameInfo()
{
	std::cout << std::endl;
	std::cout << "The current state of the game: " << std::endl << std::endl;
	for (auto player : m_players)
	{
		std::cout << "Player: " << player->getPlayerNumber() << std::endl;
		std::cout << "Has " << player->getElektro() << " elektro." << std::endl;
		std::cout << "Owns " << player->getOwnedCities().size() << " cities." << std::endl;
		std::cout << "Power plants: " << std::endl;
		for (auto& plant : player->getPowerPlants())
		{
			m_deckManager->outputPowerPlant(std::dynamic_pointer_cast<PowerPlant>(plant));		
		}
		std::cout << std::endl;
	}
}
