#include "skillstate.h"

SkillState* SkillState::_instance;
SkillState* SkillState::instance(){
	if(_instance == NULL)
		_instance = new SkillState();
	return _instance;
}

void SkillState::init(Game* game)
{
	//- Init skills
	skills.push_back(new Skill("Mining", "null.png", 100, 100));
	skills.push_back(new Skill("Fishing", "null.png", 132, 100));	
}


void SkillState::handle_events(Game* game, sf::Event event)
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

void SkillState::update(Game* game,  sf::Time deltaTime)
{

}


void SkillState::render(Game* game)
{
	for(Skill* s : skills){
		s->render(game->get_window());
	}
}


void SkillState::cleanup()
{
	_instance = NULL;
}

void SkillState::pause()
{
	paused = true;
}

void SkillState::resume()
{
	paused = false;
}
