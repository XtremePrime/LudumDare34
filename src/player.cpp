#include "player.h"

void Player::init()
{
	this->name = "Xx_ProSkiller_xX";
	this->clicks = 0;
	this->total_xp = 0;

	//- Init levels
	skill_lvl[SkillEnum::MINING] = 1;
	skill_lvl[SkillEnum::FISHING] = 1;
	skill_lvl[SkillEnum::WOODCUTTING] = 1;
	//- Init xp
	skill_xp[SkillEnum::MINING] = 0;
	skill_xp[SkillEnum::FISHING] = 0;
	skill_xp[SkillEnum::WOODCUTTING] = 0;
}

void Player::update(sf::Time dt)
{
}

void Player::calculate_total(){

	float xp = 0, lvl;
	#define add(a) xp += skill_xp[a]
	#define add2(b) lvl += skill_lvl[b]

	//- Calculate XP
	add(SkillEnum::MINING);
	add(SkillEnum::FISHING);
	add(SkillEnum::WOODCUTTING);
	//- Calculate LVL
	add2(SkillEnum::MINING);
	add2(SkillEnum::FISHING);
	add2(SkillEnum::FISHING);

	#undef add2
	#undef add

	this->total_xp = xp;
	this->total_lvl = lvl;
}


float Player::get_xp_at_lvl(int lvl)
{
	float a = 0;
	//- http://rsdo.net/rsdonline/guides/exp_formula.gif
	for(int i = 1; i < lvl; ++i)
	{
		a += floor( i + 300*pow(2, (i/7.f)) );
	}
	return floor(a/4);
}

bool Player::check_levelup(SkillEnum skill)
{
	if(skill_lvl[skill] >= 99) return false;
	if(skill_xp[skill] >= get_xp_at_lvl(skill_lvl[skill]+1))
		return true;
	return false;
}

void Player::levelup(SkillEnum skill)
{
	skill_lvl[skill]++;
	// std::cout << "Congratulations, you just advanced a " << name << " level.\n";
	// std::cout << "Your " << name << " level is now " << skill_lvl[skill] << ".\n";
}
