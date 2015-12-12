#ifndef PLAYER_H
#define PLAYER_H

#include "skill.hpp"
#include <map>

class Player
{
private:
	std::string name;

	std::map<SkillEnum, int> skill_lvl;
	std::map<SkillEnum, float> skill_xp;
public:
	void init(){
		//- Init levels
		skill_lvl[SkillEnum::MINING] = 1;
		skill_lvl[SkillEnum::FISHING] = 1;
		//- Init xp
		skill_xp[SkillEnum::MINING] = 0;
		skill_xp[SkillEnum::FISHING] = 0;
	}

	void add_xp(SkillEnum skill){}
};

#endif // PLAYER_H
