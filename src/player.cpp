#include "player.h"

void Player::init()
{
	this->name = "Xx_ProSkiller_xX";
	this->clicks = 0;
	this->total_xp = 0;

	//- Init levels
	skill_lvl[SkillEnum::MINING] = 1;
	skill_lvl[SkillEnum::FISHING] = 1;
	//- Init xp
	skill_xp[SkillEnum::MINING] = 0;
	skill_xp[SkillEnum::FISHING] = 0;
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
	//- Calculate LVL
	add2(SkillEnum::MINING);
	add2(SkillEnum::FISHING);

	#undef add2
	#undef add

	this->total_xp = xp;
	this->total_lvl = lvl;
}
