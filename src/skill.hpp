#ifndef SKILL_H
#define SKILL_H

#include <map>
#include <vector>
#include "resource.hpp"

enum class SkillEnum{
	MINING, FISHING
};

class Skill
{
private:
	std::string name;
	sf::Texture txr;
	sf::Sprite sprite;
	const int size = 32;
	int x, y;
public:
    Skill(std::string name="N/A", std::string filename="null.png", int x=0, int y=0)
    {
        init(name, filename, x, y);
    }

	void init(std::string name="N/A", std::string filename="null.png", int x=0, int y=0)
	{
		this->name = name;
		txr.loadFromFile("res/skills/"+filename);
		sprite.setTexture(txr);
		this->x = x;
		this->y = y;
		sprite.setPosition(sf::Vector2f(x, y));
	}

	void render(sf::RenderWindow* window)
	{
		window->draw(this->sprite);
	}

	std::string get_name(){ return this->name; }
	sf::Texture& get_texture(){ return this->txr; }
	sf::Sprite& get_sprite() { return this->sprite; }
};

#endif // SKILL_H
