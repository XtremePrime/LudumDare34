#ifndef SKILL_H
#define SKILL_H

#include <map>
#include <vector>
#include "resource.hpp"
#include "button.hpp"

enum class SkillEnum{
	NA, MINING, FISHING, WOODCUTTING
};

class Skill
{
private:
	std::string name;
	sf::Texture txr;
	sf::Sprite sprite;
	sf::Text text;
	sf::Font font;
	Button button;
	const int size = 64;
	int x, y;
	SkillEnum type;
public:
    Skill(SkillEnum type, std::string name="N/A", std::string filename="null.png", int x=0, int y=0)
    {
        init(type, name, filename, x, y);
    }

	void init(SkillEnum type, std::string name="N/A", std::string filename="null.png", int x=0, int y=0)
	{
		this->type = type;

		this->name = name;
		txr.loadFromFile("res/skills/"+filename);
		sprite.setTexture(txr);
		this->x = x;
		this->y = y;
		sprite.setScale(size / sprite.getLocalBounds().width, size / sprite.getLocalBounds().height);
		sprite.setPosition(sf::Vector2f(x, y));


        font.loadFromFile("res/fonts/runescape_uf.ttf");
        text.setFont(font);
        text.setString(name);
        text.setCharacterSize(15);
        text.setColor(sf::Color::White);

    	sf::FloatRect fr = text.getLocalBounds();
		text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		text.setPosition(sf::Vector2f(x+64/2, y+64+10));

		button.init(x, y, size, size);
	}

	void render(sf::RenderWindow* window)
	{
		window->draw(this->sprite);
		window->draw(this->text);
	}

	SkillEnum get_type(){ return this->type; }
	bool clicked(sf::Vector2f c){ return this->button.clicked(c); }
	std::string get_name(){ return this->name; }
	sf::Texture& get_texture(){ return this->txr; }
	sf::Sprite& get_sprite() { return this->sprite; }
	Button& get_button(){ return this->button; }
};

#endif // SKILL_H
