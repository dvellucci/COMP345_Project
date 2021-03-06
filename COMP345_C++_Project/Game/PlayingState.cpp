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

	//set the game settings based on how many players there will be
	m_gameSettings = std::make_shared<GameSettings>(m_players.size());
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
					if (city->citySlots[0]->getSlotSprite().getGlobalBounds().contains((float)sf::Mouse::getPosition(*mainWindow).x, (float)sf::Mouse::getPosition(*mainWindow).y))
					{
						city->citySlots[0]->getName()[0] = toupper(city->citySlots[0]->getName()[0]);
						m_mapManager->getMap()->getCityText().setString(city->citySlots[0]->getName());
					}
					else if (city->citySlots[1]->getSlotSprite().getGlobalBounds().contains((float)sf::Mouse::getPosition(*mainWindow).x, (float)sf::Mouse::getPosition(*mainWindow).y))
					{
						city->citySlots[1]->getName()[1] = toupper(city->citySlots[1]->getName()[1]);
						m_mapManager->getMap()->getCityText().setString(city->citySlots[1]->getName());
					}
					else if (city->citySlots[2]->getSlotSprite().getGlobalBounds().contains((float)sf::Mouse::getPosition(*mainWindow).x, (float)sf::Mouse::getPosition(*mainWindow).y))
					{
						city->citySlots[2]->getName()[2] = toupper(city->citySlots[2]->getName()[2]);
						m_mapManager->getMap()->getCityText().setString(city->citySlots[2]->getName());
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
			mainWindow->draw(citySlot->getSlotSprite());
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
		clearCinInput("Invalid input. Enter a number between 2 and 6.");
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
		clearCinInput("Invalid input. Enter a number corresponding with a map.");
	}

	//parse the map data and the set the coordinates of the regions
	std::string mapStr = m_mapManager->getAvailableMaps()[mapNum - 1];
	std::transform(mapStr.begin(), mapStr.end(), mapStr.begin(), ::tolower);

	//if the map is not valid, go back to game setup
	if (!m_mapManager->loadMap("Maps/" + mapStr + ".txt"))
	{
		std::cout << "Invalid map." << std::endl;
		setNextState(GameStates::INTRO);
		m_quit = true;
		return;
	}

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
	m_deckManager->setUpDeck(Deck::cardsFilePath);

	//if map setup is successful
	if (!m_quit)
	{
		//set up the player order container and randomize it for the first turn
		for (auto& player : m_players)
			m_playerOrder.push_back(player);
		std::random_shuffle(m_playerOrder.begin(), m_playerOrder.end());

		std::cout << "Press enter to begin playing the game." << std::endl;
	}
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

	//reverse the order 
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
	std::cout << "Beginning phase 2. The power plant auction phase." << std::endl << std::endl;;

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
			clearCinInput("Invalid input. Enter 1 for yes, 0 for no.");
		}
	}

	if (isPlayerBidding == 0)
	{
		phase2BidOnPlant(0, 0, true);
	}
	else
	{
		std::shared_ptr<PowerPlant> tempCard = nullptr;	
		std::cout << std::endl;
		std::cout << "Pick a plant to bid on by entering it's corresponding number." << std::endl << std::endl;
		m_deckManager->outputMarket();
		unsigned int index = 0;
		auto tempCard2 = std::dynamic_pointer_cast<PowerPlant>(m_deckManager->getPowerPlantMarket()[index]);
		while (!(std::cin >> index) || index < 0 || index >= m_deckManager->getPowerPlantMarket().size())
		{
			clearCinInput("Invalid number for the power plant. Enter a valid number.");
		}

		std::cout << "Place a bid for the power plant." << std::endl;
		int bid = 0;
		while (!(std::cin >> bid))
		{
			clearCinInput("Invalid input for a bid. Place a bid for the power plant.");
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
				clearCinInput("Invalid input for a bid. Enter 1 for yes, 0 for no.");
			}

			//if player wants to bid
			if (isPlayerBidding == 1)
			{
				std::cout << "Place a bid for the power plant." << std::endl;
				int bid = 0;
				while (!(std::cin >> bid) || bid <= m_currentBid || bid > m_currentPlayer->getElektro())
				{
					clearCinInput("Invalid input for a bid. Place a bid for the power plant.");
					std::cout << "Current bid is at " << m_currentBid << "." << std::endl;
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
		if(m_currentPlayer->getPowerPlants().size() == m_gameSettings->getMaxPowerPlants())
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
	if (m_deckManager->drewStep3Card())
	{
		m_deckManager->setStep3Market();
		m_deckManager->shuffleMainDeck();
		m_gameSettings->setStep(3);
	}

	m_firstTurn = false;
	m_powerPlantIndex = 0;

	m_deckManager->outputMarket();
	//start phase 3
	doPhase3();
}

void PlayingState::doPhase3()
{
	std::cout << "Press enter to continue to phase 3." << std::endl << std::endl;
	m_playing = false;
	while (!m_playing);
	std::cout << "Phase 3 of the turn will now begin." << std::endl << std::endl;

	printGameInfo();

	//reverse the player order 
	updatePlayerOrder(true);

	m_currentPlayer = m_playerOrder[0];
	m_resourceIndex = 0;
	m_powerPlantIndex = 0;

	phase3BuyResources1();
}

void PlayingState::phase3BuyResources1()
{
	//get the next power plant of the player
	auto temp = m_currentPlayer->getPowerPlants()[m_powerPlantIndex];
	auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(temp);
	
	//get the resource of the power plant
	auto tempSet = powerPlant->getValidResources();
	std::vector<GridResourceType> resources;
	for (auto resource : tempSet) resources.push_back(resource);

	std::cout << "Player " << m_currentPlayer->getPlayerNumber() << "'s turn to buy resources." << std::endl << std::endl;

	std::cout << "Current power plant: ";
	//m_deckManager->outputPowerPlant(powerPlant);
	m_currentPlayer->displayPowerPlant(m_gridResourceMarket, powerPlant);
	std::cout << std::endl;

	if (resources[m_resourceIndex] != GridResourceType::No_Resource)
	{
		//ask the player how many resources he will buy
		std::cout << "How many " << m_gridResourceMarket->getResourceType(resources[m_resourceIndex]) << " will you buy for this power plant?" << std::endl;
		int amount = 0;
		while (!(std::cin >> amount))
		{
			clearCinInput("Invalid Input. Enter an amount to buy.");
		}
		phase3BuyResources2(amount);
	}
	phase3BuyResources2(0);
}

void PlayingState::phase3BuyResources2(int amount)
{
	//check if there are other resources for the current power plant
	auto temp = m_currentPlayer->getPowerPlants()[m_powerPlantIndex];
	auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(temp);

	auto tempSet = powerPlant->getValidResources();
	std::vector<GridResourceType> resources;
	for (auto resource : tempSet) resources.push_back(resource);

	if (amount > 0)
	{
		bool canBuy = m_currentPlayer->purchaseResource(m_gridResourceMarket, powerPlant, resources[m_resourceIndex], amount);
		if (!canBuy)
		{
			std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " cannot buy " << amount << 
				" " << m_gridResourceMarket->getResourceType(resources[m_resourceIndex]) << " for this power plant." << std::endl << std::endl;
			return phase3BuyResources1();
		}
	}
	
	m_resourceIndex++;
	//check if there are no more possible resources for this plant
	if (m_resourceIndex >= resources.size())
	{
		m_powerPlantIndex++;
		m_resourceIndex = 0;

		if (m_powerPlantIndex >= m_currentPlayer->getPowerPlants().size())
		{
			m_currentPlayer = m_playerOrder[getNextPlayer()];
			m_powerPlantIndex = 0;

			//if the next current player is the first player, go to step 4
			if (m_currentPlayer.get() == m_playerOrder[0].get())
				return doPhase4();

			return phase3BuyResources1();
		}
	}

	//get the next resource if the power plant holds more than one type
	if (m_resourceIndex < resources.size())
	{
		return phase3BuyResources1();
	}
	
}

void PlayingState::doPhase4()
{
	std::cout << "Press enter to continue to phase 4." << std::endl << std::endl;
	m_playing = false;
	while (!m_playing);
	printGameInfo();
	std::cout << "Phase 4 of the turn will now begin." << std::endl << std::endl;
	phase4Start();
}

void PlayingState::phase4Start()
{
	updatePlayerOrder(true);
	m_currentPlayer = m_playerOrder[0];
	phase4BuyCities1();
}

void PlayingState::phase4BuyCities1()
{
	//check if player would like to buy a city
	std::cout << "Player " << m_currentPlayer->getPlayerNumber() << "'s turn to buy a city." << std::endl;
	std::cout << "Would you like to buy a city? Enter 1 for yes, 0 for no." << std::endl;
	bool isBuying = false;
	while (!(std::cin >> isBuying) || (isBuying != 0 && isBuying != 1))
	{
		clearCinInput("Invalid Input. Enter a 1 for yes, 0 for no.");
	}

	if (!isBuying)
		return phase4BuyCities2(false, "", 0);

	std::cout << "Type the name of the city to buy." << std::endl;
	std::string city;
	auto tempCities = m_mapManager->getMap()->getCities();
	std::transform(city.begin(), city.end(), city.begin(), ::tolower);
	while (!(std::cin >> city) || tempCities.find(city) == tempCities.end())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid Input. Enter a valid city." << std::endl;
	}

	//check if the player has a house in the specified city
	if (m_currentPlayer->doesPlayerOwnCity(city))
	{
		std::cout << "You already own a slot in that city. Pick another city" << std::endl;
		return phase4BuyCities1();
	}

	std::cout << "Enter the number of the slot you would like to purchase in the city" << std::endl;
	std::cout << "During phase " << m_gameSettings->getStep() << " of the game, " 
		<< m_gameSettings->getStep() << " slots are available." << std::endl;
	int slot = 0;
	while (!(std::cin >> slot) || (slot != 1 && slot != 2 && slot != 3))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid slot." << std::endl;
	}
	slot -= 1; //decrement the slot value by 1 to get the proper index of the city slot

	//check if the city slot is ooccupied
	auto tempCitySlot = m_mapManager->getMap()->getCities().find(city)->second->citySlots[slot];
	if (tempCitySlot->getIsOwned())
	{
		std::cout << "That city slot is already occupied." << std::endl;
		return phase4BuyCities1();
	}

	phase4BuyCities2(isBuying, city, slot);
}

void PlayingState::phase4BuyCities2(bool isBuying, std::string city, int slot)
{
	//if the player decides to not buy, check for the next player
	if (!isBuying)
	{
		m_currentPlayer = m_playerOrder[getNextPlayer()];
		//end phase 4 if the next player is the starting player
		if (m_currentPlayer.get() == m_playerOrder[0].get())
		{
			return phase4End();
		}
		return phase4BuyCities1();
	}

	auto tempCity = m_mapManager->getMap()->getCityByName(city);

	//check if the slot in the city is available in the current step 
	if (slot > m_gameSettings->getStep())
	{
		std::cout << "That slot is not available during step " << m_gameSettings->getStep() << "." << std::endl;
		return phase4BuyCities1();
	}

	auto citySlot = tempCity->citySlots[slot];
	//get cost to connect to that city
	int cost;
	if (m_currentPlayer->getOwnedCities().empty())
	{
		cost = citySlot->getCost();
	}
	else
	{
		cost = citySlot->getCost() + m_mapManager->getShortestPathFromPlayer(m_currentPlayer, citySlot->getName());
	}

	//check if the current player has enough elektro
	if (m_currentPlayer->getElektro() < cost)
	{
		std::cout << "You don't have enough elektro for " << citySlot->getName() << "." << std::endl;
		return phase4BuyCities1();
	}

	//the player can buy the city
	m_currentPlayer->spendElektro(cost);
	m_currentPlayer->getOwnedCities().push_back(citySlot);
	citySlot->m_slotSprite.setTexture(m_currentPlayer->getPlayerTexture());
	citySlot->setIsOwned(true);
	std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " has " << m_currentPlayer->getElektro() << " elektro remaining." << std::endl << std::endl;

	//check if the player would like to buy another city
	return phase4BuyCities1();
}

void PlayingState::phase4End()
{
	//remove the lowest power plant(s) if necessary
	unsigned int mostHouses = 0;
	for (auto player : m_players)
	{
		if (player->getOwnedCities().size() > mostHouses)
			mostHouses = player->getOwnedCities().size();
	}
	while (std::dynamic_pointer_cast<PowerPlant>(m_deckManager->getPowerPlantMarket()[0])->getPowerPlantPrice() <= mostHouses)
	{
		m_deckManager->removeSmallestPowerPlant();
		m_deckManager->drawCard();
	}

	//check if we enter step 3
	if (m_deckManager->drewStep3Card())
	{
		m_deckManager->setStep3Market();
		m_deckManager->shuffleMainDeck();
		m_gameSettings->setStep(3);
	}


	std::cout << "Press enter to continue to phase 5." << std::endl;
	m_playing = false;
	while (!m_playing);
	doPhase5();
}

void PlayingState::doPhase5()
{
	printGameInfo();
	std::cout << "Phase 5 of the turn will now begin." << std::endl << std::endl;

	updatePlayerOrder(false);
	m_currentPlayer = m_playerOrder[0];

	//check if we enter step 2
	if (m_gameSettings->getStep() == 1)
	{
		for (auto player : m_players)
		{
			if (player->getOwnedCities().size() >= m_gameSettings->getStep2Cities())
			{
				m_gameSettings->setStep(2);
				m_deckManager->removeSmallestPowerPlant();
				m_deckManager->drawCard();
				std::cout << "The game is now in phase 2!" << std::endl;
				break;
			}
		}
	}

	m_poweredCities = 0;
	phase5PowerCities1();
}

void PlayingState::phase5PowerCities1()
{
	std::cout << std::endl;
	std::cout << "Player " << m_currentPlayer->getPlayerNumber() << "'s power plants." << std::endl << std::endl;
	int count = 0;
	for (auto card : m_currentPlayer->getPowerPlants())
	{
		auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(card);
		//std::cout << count << ". ";
		//m_deckManager->outputPowerPlant(powerPlant);
		m_currentPlayer->listPlayerPowerPlants(m_gridResourceMarket);
		count++;
	}

	std::shared_ptr<PowerPlant> powerPlant = nullptr;

	std::cout << "Would you like to use a power plant? Enter 1 for yes, 0 for no." << std::endl;
	bool usePlant = false;
	while (!(std::cin >> usePlant) || (usePlant != 0 && usePlant != 1))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input. Enter 1 for yes, 0 for no" << std::endl;
	}

	if (!usePlant)
		return phase5PowerCities2(powerPlant);

	std::cout << "Which power plant would you like to use?" << std::endl;
	unsigned int index;
	while (!(std::cin >> index) || index < 0 || index > m_currentPlayer->getPowerPlants().size())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input for a power plant." << std::endl;
	}

	auto temp = m_currentPlayer->getPowerPlants()[index];
	powerPlant = std::dynamic_pointer_cast<PowerPlant>(temp);
	phase5PowerCities2(powerPlant);
}

void PlayingState::phase5PowerCities2(std::shared_ptr<PowerPlant> powerPlant)
{
	//check if the player would like to use the power plant
	if (powerPlant)
	{
		//check if the power plant was already powered
		if (std::find(m_usedPowerPlants.begin(), m_usedPowerPlants.end(), powerPlant) != m_usedPowerPlants.end())
		{
			std::cout << "This power plant was already used to power cities." << std::endl;
			return phase5PowerCities1();
		}
		m_usedPowerPlants.push_back(powerPlant);
	}

	//if the player decides to not use power plants
	if (!powerPlant)
	{
		//make sure the player does not power more houses than he owns
		int numOfHouses = m_currentPlayer->getOwnedCities().size();
		m_poweredCities = std::min(numOfHouses, m_poweredCities);

		std::cout << std::endl;
		std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " powered " << m_poweredCities << " cities." << std::endl;
		std::cout << "Player " << m_currentPlayer->getPlayerNumber() << " earns " << m_gameSettings->getElektroPayment(m_poweredCities) << " elektro." << std::endl;
		std::cout << std::endl;

		//set the elektro of the player
		m_currentPlayer->setElektro(m_currentPlayer->getElektro() + m_gameSettings->getElektroPayment(m_poweredCities));

		//if a player has required amount of cities to win, add as potential winner
		if (m_currentPlayer->getOwnedCities().size() >= m_gameSettings->getCitiesToEnd())
		{
			m_gameOver = true;
			m_potentialWinners.push_back(m_currentPlayer);
		}

		//reset the used power plants vector for the next player
		m_usedPowerPlants.clear();

		//check for next player
		m_currentPlayer = m_playerOrder[getNextPlayer()];
		if (m_currentPlayer.get() == m_playerOrder[0].get())
		{
			//end phase 5 if there are no more players
			return phase5Bureaucracy();
		}
		
		//let the next player power some cities
		return phase5PowerCities1();
	}

	//if the power plant has only 1 resource, consume
	if (powerPlant->getValidResources().size() == 1)
	{
		//if the power plant does not require resources
		if (powerPlant->getValidResources()[0] == GridResourceType::No_Resource)
		{
			m_poweredCities += powerPlant->getPowerPlantHouses();
			std::cout << "No resources required by power plant ";
			m_deckManager->outputPowerPlant(powerPlant);
			return phase5PowerCities1();
		}

		auto resourceType = powerPlant->getValidResources()[0];
		if (powerPlant->consumeResource(resourceType, powerPlant->getPowerPlantCapacity()))
		{
			m_poweredCities += powerPlant->getPowerPlantHouses();
			std::cout << "Resources consumed by power plant ";
			m_deckManager->outputPowerPlant(powerPlant);
		}
		else
		{
			std::cout << "This power plant does not have enough resources to consume." << std::endl;
		}
	}
	else 
	{
		//Make user pick which resources to use
		return chooseResourceToConsume1(powerPlant);
	}

	//let the player pick another power plant
	return phase5PowerCities1();
}

void PlayingState::chooseResourceToConsume1(std::shared_ptr<PowerPlant> powerPlant)
{
	auto tempMap = powerPlant->getStoredResources();
	int amount = 0;
	for (auto temp : tempMap)
	{
		int num = 0;
		auto resource = temp.first;
		std::cout << "How many " << m_gridResourceMarket->getResourceType(resource) << " will you consume?" << std::endl;
		while (!(std::cin >> num) || num > powerPlant->getNumOfPlacedResourcesByType(resource) || num < 0)
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "This power plant does not have " << num << " m_gridResourceMarket->getResourceType(resource) to consume." << std::endl;
		}

		powerPlant->consumeResource(resource, num);
	}
	
	m_poweredCities += powerPlant->getPowerPlantHouses();
	return phase5PowerCities1();
}

void PlayingState::chooseResourceToConsume2(int amount)
{

}

void PlayingState::phase5Bureaucracy()
{
	if (m_gameOver)
	{
		if (m_potentialWinners.size() == 1)
		{
			m_winner = m_potentialWinners[0];
		}
		else
		{
			//player with the most elektro wins
			int maxElektro = 0;
			for (auto player : m_potentialWinners)
			{
				if (player->getElektro() > maxElektro)
				{
					m_winner = player;
					maxElektro = player->getElektro();
				}
			}
		}
		gameOver();
	}

	//if in phase 1 or 2, update the power plant market by removing the highest card 
	//and drawing a new card
	if (m_gameSettings->getStep() == 1 || m_gameSettings->getStep() == 2)
	{
		m_deckManager->removeHighestPlantFromMarket();
		m_deckManager->drawCard();
	}

	//check if the step 3 card was drawn
	if (m_deckManager->drewStep3Card())
	{
		m_deckManager->setStep3Market();
		m_deckManager->shuffleMainDeck();
		m_gameSettings->setStep(3);
		std::cout << "The game is now in step 3." << std::endl;
	}

	//resupply the resource market
	int amount = std::min(m_gameSettings->getCoalToSupply(), getResourcesInSupply(GridResourceType::Coal, m_players));
	m_gridResourceMarket->reSupplyResource(GridResourceType::Coal, amount);

	int oilAmount = std::min(m_gameSettings->getOilToSupply(), getResourcesInSupply(GridResourceType::Oil, m_players));
	m_gridResourceMarket->reSupplyResource(GridResourceType::Oil, oilAmount);
	
	int garbageAmount = std::min(m_gameSettings->getGarbageToSupply(), getResourcesInSupply(GridResourceType::Garbage, m_players));
	m_gridResourceMarket->reSupplyResource(GridResourceType::Garbage, garbageAmount);

	int uraniumAmount = std::min(m_gameSettings->getUraniumToSupply(), getResourcesInSupply(GridResourceType::Uranium, m_players));
	m_gridResourceMarket->reSupplyResource(GridResourceType::Uranium, uraniumAmount);

	std::cout << "The market has been re-supplied." << std::endl;

	return endPhase5();
}

void PlayingState::endPhase5()
{
	//if the step 3 card was drawn, 
	if (m_deckManager->drewStep3Card())
	{
		m_deckManager->setStep3Market();
		m_deckManager->shuffleMainDeck();
		m_gameSettings->setStep(3);
	}

	//print the status of each player
	printGameInfo();

	std::cout << "Press enter to do the next turn." << std::endl;
	m_playing = false;
	while (!m_playing);
	std::cout << "Phase 1 of the next turn will begin." << std::endl;
	phase1Start();
}

void PlayingState::gameOver()
{
	std::cout << "The game is over. The winner is Player " << m_winner->getPlayerNumber() << std::endl;
	m_playing = false;
	while (!m_playing);
}


//print the information of each player
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
		player->listPlayerPowerPlants(m_gridResourceMarket);
		std::cout << std::endl;
	}
}

int PlayingState::getNextPlayer()
{
	return (std::distance(m_playerOrder.begin(), std::find(m_playerOrder.begin(), m_playerOrder.end(), m_currentPlayer)) + 1) % m_playerOrder.size();
}

//gets the number of a resource type stored by the players
int PlayingState::getNumOfResourcesOwned(GridResourceType type, std::vector<std::shared_ptr<Player>> players)
{
	int amount = 0;
	for (auto player : players)
	{
		for (auto plant : player->getPowerPlants())
		{
			auto powerPlant = std::dynamic_pointer_cast<PowerPlant>(plant);

			auto tempMap = powerPlant->getStoredResources();
			std::map<GridResourceType, int>::iterator it;
			it = tempMap.find(type);

			if(it != tempMap.end())
				amount += powerPlant->getStoredResources().at(type);
		}
	}
	return amount;
}

//gets number of resources not in the market or not stored by players
int PlayingState::getResourcesInSupply(GridResourceType type, std::vector<std::shared_ptr<Player>> players)
{
	//get resources owned by players
	int amount = getNumOfResourcesOwned(type, players);

	//get resources in the market
	amount += m_gridResourceMarket->getAvailableResourceType(type);

	return m_gridResourceMarket->getMaxCapacity(type) - amount;
}

void PlayingState::clearCinInput(std::string error)
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << error << std::endl;
}

