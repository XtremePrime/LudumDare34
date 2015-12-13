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
	skill_lvl_text.setFont(game->get_font());
	skill_lvl_text.setCharacterSize(15);
	skill_lvl_text.setColor(sf::Color::White);


	skill_xp = game->get_gameobject()->get_player().get_xp(skill_type);
	std::stringstream ss;
	ss << skill_name << " Exp: " << std::fixed << std::setprecision(0) <<  std::trunc(skill_xp);
	skill_text.setString(ss.str());
	std::stringstream ss2;
	ss2 << skill_name << " Lvl: " << game->get_gameobject()->get_player().get_lvl(skill_type);
	skill_lvl_text.setString(ss2.str());

	{
		sf::FloatRect fr = skill_text.getLocalBounds();
		skill_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		skill_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
	{
		sf::FloatRect fr = skill_lvl_text.getLocalBounds();
		skill_lvl_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		skill_lvl_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}
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
					if(resources[i]->get_req_lvl() <= game->get_gameobject()->player.get_lvl(skill_type))
					{
						game->get_gameobject()->resource = resources[i];
						std::cout << "Clicked resource " << i << "!\n";
						game->push_state(GameState::instance());
						break;
					}else
					{
						// NO REQ LVL!
					}
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
	std::stringstream ss2;
	ss2 << skill_name << " Lvl: " << game->get_gameobject()->get_player().get_lvl(skill_type);
	skill_lvl_text.setString(ss2.str());
	{
		sf::FloatRect fr = skill_text.getLocalBounds();
		skill_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		skill_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
	{
		sf::FloatRect fr = skill_lvl_text.getLocalBounds();
		skill_lvl_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		skill_lvl_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}
}


void ResourceState::render(Game* game)
{
	game->get_window()->draw(this->skill_text);
	game->get_window()->draw(this->skill_lvl_text);
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
	#define n(a,b,c,d,e,f,g) new Resource(a,b,c,d,e,f,g)
	switch(chosen_skill)
	{
		case SkillEnum::MINING:{
		add(n("Copper Ore", 1, 17.5, "null.png", "null.png", 20, 20));
		add(n("Iron Ore", 15, 35, "null.png", "null.png", 420/2-16, 20));
		add(n("Silver Ore", 20, 55, "null.png", "null.png", 420-32-20, 20));
		add(n("Gold Ore", 40, 85, "null.png", "null.png", 20, 32+70));
		add(n("Mithril Ore", 55, 150, "null.png", "null.png", 420/2-16, 32+70));
		add(n("Adamantite Ore", 70, 300, "null.png", "null.png", 420-32-20, 32+70));
		add(n("Titanium Ore", 80, 555.5, "null.png", "null.png", 420/2-16, 32+150));
		}break;

		case SkillEnum::FISHING:{
		// add(new Resource("Fish", 3.2, 1, "fish_0.png", "fish_0.png", 10, 10));
		add(n("Dark Fish", 1, 10, "fish_0.png", "fish_0.png", 20, 20));
		add(n("Leaf Fish", 10, 40, "fish_1.png", "fish_1.png", 420/2-16, 20));
		add(n("Sun Fish", 15, 55.5, "fish_2.png", "fish_2.png", 420-32-20, 20));
		add(n("Gold Fish", 30, 70, "fish_3.png", "fish_3.png", 20, 32+70));
		add(n("Fire Fish", 45, 90, "fish_4.png", "fish_4.png", 420/2-16, 32+70));
		add(n("Feral Fish", 60, 120, "fish_5.png", "fish_5.png", 420-32-20, 32+70));
		add(n("God Fish", 75, 555.5, "fish_6.png", "fish_6.png", 420/2-16, 32+150));
		}break;

		case SkillEnum::WOODCUTTING:{
		int xx = 10, yy = 10;
		add(n("Tree", 1, 1, "null.png", "null.png", 20, 20));
		add(n("Evergreen", 1, 1, "null.png", "null.png", 420/2-16, 20));
		add(n("Oak", 1, 1, "null.png", "null.png", 420-32-20, 20));
		add(n("Maple", 1, 1, "null.png", "null.png", 20, 32+70));
		add(n("Yew", 1, 1, "null.png", "null.png", 420/2-16, 32+70));
		}break;
	}
}
