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
	init_skills();
	game->get_gameobject()->player.calculate_total();

	total_text.setFont(game->get_font());
	total_text.setCharacterSize(15);
	total_text.setColor(sf::Color::White);
	total_lvl_text.setFont(game->get_font());
	total_lvl_text.setCharacterSize(15);
	total_lvl_text.setColor(sf::Color::White);

	total = game->get_gameobject()->get_player().get_total_xp();
	std::stringstream ss;
	ss << "Total Exp: " << std::fixed << std::setprecision(0) <<  std::trunc(total);
	total_text.setString(ss.str());

	std::stringstream ss2;
	ss2 << "Total Lvl: " << game->get_gameobject()->get_player().get_total_lvl();
	total_lvl_text.setString(ss2.str());

	{
		sf::FloatRect fr = total_text.getLocalBounds();
		total_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		total_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
	{
		sf::FloatRect fr = total_lvl_text.getLocalBounds();
		total_lvl_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		total_lvl_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}

	std::cout << game->get_width() << "," << game->get_height() << "\n";
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
	if(event.type == sf::Event::MouseButtonPressed)
	{
	    if (event.mouseButton.button == sf::Mouse::Left)
		{
			//- Grab mouse coords
            sf::Vector2i pixelPos = sf::Mouse::getPosition(*game->get_window());
            sf::Vector2f pos = game->get_window()->mapPixelToCoords(pixelPos);

            //- Handle skill clicking
			for(int i = 0; i < skills.size(); ++i)
			{
			    // std::cout << pos.x << "," << pos.y << "/" << skills[i]->get_button().debug() << "\n";
				if(skills[i]->clicked(pos))
				{
					game->get_gameobject()->chosen_skill = skills[i]->get_type();
					game->get_gameobject()->skill = skills[i];
					std::cout << "Clicked skill " << i << "!\n";
					game->push_state(ResourceState::instance());
					break;
				}
			}
		}
	}
}

void SkillState::update(Game* game,  sf::Time deltaTime)
{
	// game->get_gameobject()->player.update(deltaTime);

	//- Total XP update
	total = game->get_gameobject()->get_player().get_total_xp();
	std::stringstream ss;
	ss << "Total Exp: " << std::fixed << std::setprecision(0) <<  std::trunc(total);
	total_text.setString(ss.str());
	std::stringstream ss2;
	ss2 << "Total Lvl: " << game->get_gameobject()->get_player().get_total_lvl();
	total_lvl_text.setString(ss2.str());

	//- Set level pos
	{
		sf::FloatRect fr = total_text.getLocalBounds();
		total_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		total_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
	{
		sf::FloatRect fr = total_lvl_text.getLocalBounds();
		total_lvl_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		total_lvl_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}
}


void SkillState::render(Game* game)
{
	for(Skill* s : skills){
		s->render(game->get_window());
	}
	game->get_window()->draw(this->total_text);
	game->get_window()->draw(this->total_lvl_text);
}


void SkillState::cleanup()
{
	clear_vector(skills);
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

void SkillState::init_skills()
{
	#define add(x) skills.push_back(x)
	add(new Skill(SkillEnum::MINING, "Mining", "pickaxe.png", 32, 10));
	add(new Skill(SkillEnum::FISHING, "Fishing", "null.png", 32*3, 10));
	#undef add
}
