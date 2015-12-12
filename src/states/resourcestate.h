#ifndef RESOURCESTATE_H
#define RESOURCESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <iostream>
#include <locale>
#include <iostream>
#include <iomanip>
#include "state.h"
#include "gamestate.h"
#include "../skill.hpp"
#include "../resource.hpp"

class ResourceState : public State
{
private:
	sf::Text skill_text;
	std::string skill_name;
	float skill_xp;
	SkillEnum skill_type;

    bool paused = false;
    std::vector<Resource*> resources;
protected:
	static ResourceState* _instance;
	ResourceState(){}
public:
	static ResourceState* instance();
    ~ResourceState(){}
	void init(Game* game);
	void cleanup();
	void init_resources(SkillEnum chosen_skill);

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

#endif // RESOURCESTATE_H
