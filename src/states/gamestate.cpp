#include "gamestate.h"

GameState* GameState::_instance;
GameState* GameState::instance(){
	if(_instance == NULL)
		_instance = new GameState();
	return _instance;
}

void GameState::init(Game* game)
{

}


void GameState::handle_events(Game* game, sf::Event event)
{
	if(event.type == sf::Event::KeyPressed)
	{
		switch(event.key.code)
		{
			case sf::Keyboard::Escape:
			{
				game->quit();
			}break;
			default:
			break;
		}
	}
}

void GameState::update(Game* game,  sf::Time deltaTime)
{

}


void GameState::render(Game* game)
{

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
