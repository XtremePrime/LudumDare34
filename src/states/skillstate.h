#ifndef SKILLSTATE_H
#define SKILLSTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include "../skill.hpp"
#include "state.h"

class SkillState : public State
{
private:
    bool paused = false;
    std::vector<Skill*> skills;
    sf::Text total;
protected:
	static SkillState* _instance;
	SkillState(){}
public:
	static SkillState* instance();
    ~SkillState(){}
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

#endif // SKILLSTATE_H
