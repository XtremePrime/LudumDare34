#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <string>
#include "button.hpp"
#include <sstream>

struct Source
{
	sf::Texture txr;
	sf::Sprite sprite;

	void init(std::string filename){
		txr.loadFromFile("res/sources/"+filename);
		sprite.setTexture(txr);
		sprite.scale(4.0, 4.0);
	}

	void render(sf::RenderWindow* window){
		window->draw(sprite);
	}
};

class Resource
{
private:
	std::string name;
	sf::Texture txr;
	sf::Sprite sprite;
	float xp;
	// std::string xp_str;
	sf::Text name_text;
	sf::Text given_xp_text;
	sf::Font font;
	Button button;
	const int size = 32;
	Source src;
public:
	Resource(){}
	Resource(std::string name="N/A", float xp=1.0, std::string filename="null.png", std::string src_filename="null.png", int x=0, int y=0)
	{
		init(name, xp, filename, src_filename, x, y);
	}

	void init(std::string name="N/A", float xp=1.0, std::string filename="null.png", std::string src_filename="null.png", int x=0, int y=0)
	{
		this->name = name;
		this->xp = xp;
		txr.loadFromFile("res/resources/"+filename);
		sprite.setTexture(txr);
		sprite.setPosition(sf::Vector2f(x, y));

		src.init(src_filename);

		std::stringstream ss;
		ss << xp << "xp";
        font.loadFromFile("res/fonts/orange kid.ttf");
        name_text.setFont(font);
        name_text.setString(name);
        name_text.setCharacterSize(15);
        name_text.setColor(sf::Color::White);
        given_xp_text.setFont(font);
        given_xp_text.setString(ss.str());
        given_xp_text.setCharacterSize(15);
        given_xp_text.setColor(sf::Color::Yellow);

    	sf::FloatRect fr = name_text.getLocalBounds();
		name_text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
		name_text.setPosition(sf::Vector2f(x+16, y+16));
    	sf::FloatRect fr2 = given_xp_text.getLocalBounds();
		given_xp_text.setOrigin(fr2.left + fr2.width/2.0f, fr2.top  + fr2.height/2.0f);
		given_xp_text.setPosition(sf::Vector2f(x+16, y+32));
		sf::FloatRect fr3 = src.sprite.getLocalBounds();
		src.sprite.setOrigin(fr3.left + fr3.width/2.0f, fr3.top  + fr3.height/2.0f);
		src.sprite.setPosition(sf::Vector2f(430/2, 320/2));

		button.init(x, y, size, size);
	}

	void render(sf::RenderWindow* window)
	{
		window->draw(this->sprite);
		window->draw(this->name_text);
		window->draw(this->given_xp_text);
	}

	Source& get_source(){ return this->src; }
	bool clicked(sf::Vector2f c){ return this->button.clicked(c); }
	std::string get_name(){ return this->name; }
	float get_xp(){ return this->xp; }
	sf::Texture& get_texture(){ return this->txr; }
	sf::Sprite& get_sprite() { return this->sprite; }
};

#endif // RESOURCE_H
