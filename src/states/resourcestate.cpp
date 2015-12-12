#include "resourcestate.h"

ResourceState* ResourceState::_instance;
ResourceState* ResourceState::instance(){
	if(_instance == NULL)
		_instance = new ResourceState();
	return _instance;
}

void ResourceState::init(Game* game)
{
	init_resources(game->get_gameobject()->chosen_skill);
	game->get_gameobject()->player.calculate_total();

	skill_name = game->get_gameobject()->skill->get_name();
	skill_type = game->get_gameobject()->skill->get_type();

	skill_text.setFont(game->get_font());
	skill_text.setCharacterSize(15);
	skill_text.setColor(sf::Color::White);

	skill_xp = game->get_gameobject()->get_player().get_xp(skill_type);
	std::stringstream ss;
	ss << skill_name << " Exp: " << std::fixed << std::setprecision(0) <<  std::trunc(skill_xp);
	skill_text.setString(ss.str());

	sf::FloatRect fr = skill_text.getLocalBounds();
	skill_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
	skill_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));

}


void ResourceState::handle_events(Game* game, sf::Event event)
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
	    if (event.mouseButton.button == sf::Mouse::Left)
		{
			//- Grab mouse coords
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*game->get_window());
            sf::Vector2f pos = game->get_window()->mapPixelToCoords(pixelPos);

            //- Handle skill clicking
			for(int i = 0; i < resources.size(); ++i)
			{
			    if(resources[i]->clicked(pos))
				{
					game->get_gameobject()->resource = resources[i];
					std::cout << "Clicked resource " << i << "!\n";
					game->push_state(GameState::instance());
					break;
				}
			}
		}
	}
}

void ResourceState::update(Game* game,  sf::Time deltaTime)
{
	// game->get_gameobject()->player.update(deltaTime);

	//- Update skill xp
	skill_xp = game->get_gameobject()->get_player().get_xp(skill_type);
	std::stringstream ss;
	ss << skill_name << " Exp: " << std::fixed << std::setprecision(0) <<  std::trunc(skill_xp);
	skill_text.setString(ss.str());

	sf::FloatRect fr = skill_text.getLocalBounds();
	skill_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
	skill_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
}


void ResourceState::render(Game* game)
{
	game->get_window()->draw(this->skill_text);
	for(Resource* r : resources)
		r->render(game->get_window());
}


void ResourceState::cleanup()
{
	clear_vector(resources);
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

void ResourceState::init_resources(SkillEnum chosen_skill)
{
	//init(name, xp, filename, x, y);
	#define add(x) resources.push_back(x)
	switch(chosen_skill)
	{
		case SkillEnum::MINING:
		add(new Resource("Copper", 5, "null.png", "tree_0.png", 10, 10));
		break;
		case SkillEnum::FISHING:
		add(new Resource("Fish", 3.2, "fish_0.png", "fish_0.png", 10, 10));
		break;
	}
}
