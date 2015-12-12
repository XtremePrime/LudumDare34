#ifndef SKILLSTATE_H
#define SKILLSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <sstream>
#include <locale>
#include <iostream>
#include <iomanip>
#include "resourcestate.h"
#include "../skill.hpp"
#include "state.h"

class SkillState : public State
{
private:
    bool paused = false;
    std::vector<Skill*> skills;
    float total;
    sf::Text total_text;
    sf::Text total_lvl_text;
protected:
	static SkillState* _instance;
	SkillState(){}
public:
	static SkillState* instance();
    ~SkillState(){}
	void init(Game* game);
	void cleanup();
	void init_skills();

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

#endif // SKILLSTATE_H
