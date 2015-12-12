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

	int clicks;
	float total_xp = 0;
	int total_lvl = 0;
public:
	Player(){init();}
	void init();

	void calculate_total();
	bool check_levelup(SkillEnum);
	void levelup(SkillEnum);
	float get_xp_at_lvl(int);

	void update(sf::Time dt);

	void add_xp(SkillEnum skill, float xp){skill_xp[skill] += xp;}
	float get_total_xp(){ return this->total_xp; }
	int get_total_lvl() { return this->total_lvl; }
	float get_xp(SkillEnum sk){ return this->skill_xp[sk]; }
	int get_lvl(SkillEnum sk){ return this->skill_lvl[sk]; }
	void set_xp(SkillEnum sk, float xp){ this->skill_xp[sk] = xp; }
	void set_lvl(SkillEnum sk, int lvl){ this->skill_lvl[sk] = lvl; }

};

#endif // PLAYER_H
