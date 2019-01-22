#include "PlayingState.h"

PlayingState::PlayingState() : m_quit(false), m_playing(false)
{
	setUpGame();
	std::cout << players.size() << " player game" << std::endl;
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
			//update map after a player's turn
		}
	}
}

void PlayingState::draw(sf::RenderWindow &window)
{
	
}

//sets up the players and starts the game
void PlayingState::setUpGame()
{
	int numOfPlayers = 0;
	std::cout << "Enter number of players" << std::endl;

	std::cin >> numOfPlayers;
	//initialize players
	for (int i = 0; i < numOfPlayers; i++)
	{
		std::unique_ptr<Player> player = std::make_unique<Player>("player "+std::to_string(i+1));
		players.push_back(std::move(player));
	}

	std::cout << "Press enter to play the game or escape to quit" << std::endl;
}
