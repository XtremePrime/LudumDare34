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
	skill_type = game->get_gameobject()->skill->get_type();

	button.init(0, 0, game->get_width(), game->get_height());

	//- BG
	bg_txr.loadFromFile("res/background/"+game->get_gameobject()->background_name);
	bg.setTexture(bg_txr);
	bg.setPosition(sf::Vector2f(0, 0));

	res_text.setFont(game->get_font());
	res_text.setCharacterSize(15);
	res_text.setColor(sf::Color::White);
	stats_text.setFont(game->get_font());
	stats_text.setCharacterSize(15);
	stats_text.setColor(sf::Color::White);

	std::stringstream ss;
	ss << "Resource Name: " << resource_name;
	res_text.setString(ss.str());
	std::stringstream ss2;
	ss2 << game->get_gameobject()->skill->get_name() << " Exp: " << player->get_xp(skill_type) << " / Lvl: " << player->get_lvl(skill_type);
	stats_text.setString(ss2.str());
	{
		sf::FloatRect fr = res_text.getLocalBounds();
		res_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		res_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
	{
		sf::FloatRect fr = stats_text.getLocalBounds();
		stats_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		stats_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}

	//- Init sound
	bfr.loadFromFile("res/sfx/action.wav");
	snd.setBuffer(bfr);
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
				if(player->check_levelup(game->get_gameobject()->chosen_skill)){
					player->levelup(game->get_gameobject()->chosen_skill);
				}
				player->calculate_total();
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
			snd.stop();
			snd.play();
			player->add_xp(game->get_gameobject()->chosen_skill, resource->get_xp());
			std::cout << player->get_xp(game->get_gameobject()->chosen_skill) << "\n";

            {
                std::stringstream ss;
                ss << "+" << resource->get_xp() << "xp";
                notifications.push_back(new Notification(ss.str(), (int)pos.x, (int)pos.y, 20, sf::Color::Yellow, 0));
            }

			if(player->check_levelup(game->get_gameobject()->chosen_skill)){
				player->levelup(game->get_gameobject()->chosen_skill);
				std::stringstream ss;
				// ss << "Congratulations! You just advanced a " << game->get_gameobject()->skill->get_name() << " level!";
				// notifications.push_back(new Notification(ss.str(), game->get_width()/2, 20, 40, sf::Color::White, 1));
				ss << "Your " << game->get_gameobject()->skill->get_name() << " level is " << player->get_lvl(game->get_gameobject()->chosen_skill);
				notifications.push_back(new Notification(ss.str(), game->get_width()/2, 25, 40, sf::Color(200, 0, 0), 1));
			}
			player->calculate_total();
			game->get_save().save_file(*player);
		}
		else if(event.mouseButton.button == sf::Mouse::Right)
		{

		}
	}
}

void GameState::update(Game* game,  sf::Time deltaTime)
{
	if(notifications.size() > 0)
	{
		for(int i = 0; i < notifications.size(); ++i){
			if(notifications[i]->is_dead())
				notifications.erase(notifications.begin()+i);
		}
		for(Notification* n : notifications){
			n->update(deltaTime);
		}
	}

	std::stringstream ss;
	ss << "Resource Name: " << resource_name;
	res_text.setString(ss.str());
	std::stringstream ss2;
	ss2 << game->get_gameobject()->skill->get_name() << " Exp: " << player->get_xp(skill_type) << " / Lvl: " << player->get_lvl(skill_type);
	stats_text.setString(ss2.str());
	{
		sf::FloatRect fr = res_text.getLocalBounds();
		res_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		res_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-30));
	}
	{
		sf::FloatRect fr = stats_text.getLocalBounds();
		stats_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		stats_text.setPosition(sf::Vector2f(game->get_width()/2, game->get_height()-10));
	}
}


void GameState::render(Game* game)
{
	game->get_window()->draw(bg);
	resource->get_source().render(game->get_window());
	if(notifications.size() > 0)
	{
		for(Notification* n : notifications)
			n->render(game->get_window());
	}

	game->get_window()->draw(res_text);
	game->get_window()->draw(stats_text);	
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
