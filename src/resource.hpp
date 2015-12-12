#ifndef RESOURCE_H
#define RESOURCE_H

#include <SFML/Graphics.hpp>
#include <string>

class Resource
{
private:
	std::string name;
	sf::Texture txr;
	sf::Sprite sprite;
	long double xp;
public:
	void init(std::string name="N/A", float xp=1.0, std::string filename="null.png", int x=0, int y=0)
	{
		this->name = name;
		this->xp = xp;
		txr.loadFromFile("res/resources/"+filename);
		sprite.setTexture(txr);
		sprite.setPosition(sf::Vector2f(x, y));
	}

	void render(sf::RenderWindow* window)
	{
		window->draw(this->sprite);
	}

	std::string get_name(){ return this->name; }
	float get_xp(){ return this->xp; }
	sf::Texture& get_texture(){ return this->txr; }
	sf::Sprite& get_sprite() { return this->sprite; }
};

#endif // RESOURCE_H
