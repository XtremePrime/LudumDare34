#include <string>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "player.h"
#include "skill.hpp"

class GameObject
{
public:
	Resource* resource;
	Skill* skill;
	Player player;
	SkillEnum chosen_skill = SkillEnum::NA;
	std::string background_name = "fishing.png";


	//- Options objects
	int width = 860, height = 640;
	bool has_music = true;
	bool has_sfx = true;
	float volume = 1.0;
	std::string username = "Player";

	Player& get_player(){ return this->player; }
};

#endif // GAMEOBJECT_H
