#include "resourcestate.h"

ResourceState* ResourceState::_instance;
ResourceState* ResourceState::instance(){
	if(_instance == NULL)
		_instance = new ResourceState();
	return _instance;
}

void ResourceState::init(Game* game)
{

}


void ResourceState::handle_events(Game* game, sf::Event event)
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

void ResourceState::update(Game* game,  sf::Time deltaTime)
{

}


void ResourceState::render(Game* game)
{

}


void ResourceState::cleanup()
{
	_instance = NULL;
}

void ResourceState::pause()
{
	paused = true;
}

void ResourceState::resume()
{
	paused = false;
}
