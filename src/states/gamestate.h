#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include "state.h"
#include "../player.h"
#include "../resource.hpp"
#include "../skill.hpp"
#include "../gui/notification.hpp"

class GameState : public State
{
private:
	int width, height;
    bool paused = false;
    float xp;
    std::string skill_name;
    std::string resource_name;
    Button button;
    Player* player;
    Resource* resource;
    sf::Sound snd; sf::SoundBuffer bfr;

    SkillEnum skill_type;

    sf::Font font;
    sf::Text res_text;
    sf::Text stats_text;

    std::vector<Notification*> notifications;
protected:
	static GameState* _instance;
	GameState(){}
public:
	static GameState* instance();
    ~GameState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();

 	template<typename T>
 	void clear_vector(std::vector<T*>& v)
 	{
 		for(int i = 0; i < v.size(); ++i)
 			delete (v[i]);
 		v.clear();
 	}
};

#endif // GAMESTATE_H
