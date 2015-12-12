#include "gamestate.h"

#include <iostream>

GameState* GameState::_instance;
GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init(Game* game)
{
	player = &game->get_gameobject()->player;
	resource = game->get_gameobject()->resource;

	width = game->get_width();
	height = game->get_height();

	xp = game->get_gameobject()->resource->get_xp();
	resource_name = game->get_gameobject()->resource->get_name();

	button.init(0, 0, game->get_width(), game->get_height());
}


void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				game->pop_state();
			}break;
			default:
			break;
		}
	}
	if(event.type == sf::Event::MouseButtonPressed)
	{
	    if(event.mouseButton.button == sf::Mouse::Left)
		{
			//- Grab mouse coords
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*game->get_window());
            sf::Vector2f pos = game->get_window()->mapPixelToCoords(pixelPos);

			//- Give player xp
			player->add_xp(game->get_gameobject()->chosen_skill, resource->get_xp());
			std::cout << player->get_xp(game->get_gameobject()->chosen_skill) << "\n";
			player->calculate_total();
		}
		else if(event.mouseButton.button == sf::Mouse::Right)
		{

		}
	}
}

void GameState::update(Game* game,  sf::Time deltaTime)
{

}


void GameState::render(Game* game)
{
	resource->get_source().render(game->get_window());
}


void GameState::cleanup()
{
	_instance = NULL;
}

void GameState::pause()
{
	paused = true;
}

void GameState::resume()
{
	paused = false;
}
