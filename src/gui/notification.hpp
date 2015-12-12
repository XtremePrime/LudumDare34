#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Notification
{
private:
	sf::Text text;
	sf::Font font;
	int x, y;
	sf::Clock timer;
	bool dead;
	int anim_style;
public:
	Notification(){}
	Notification(std::string msg, int x, int y, int size, sf::Color col, int anim_style=0){
		init(msg, x, y, size, col, anim_style);
	}

	void init(std::string msg, int x, int y, int size, sf::Color col, int anim_style=0)
	{
		this->x = x;
		this->y = y;
		this->dead = false;
		this->anim_style = anim_style;

		font.loadFromFile("res/fonts/runescape_uf.ttf");
		text.setFont(font);
		text.setCharacterSize(size);
		text.setColor(col);
		text.setString(msg);

		{
			sf::FloatRect fr = text.getLocalBounds();
			text.setOrigin(fr.left + fr.width/2.0f, fr.top  + fr.height/2.0f);
			text.setPosition(sf::Vector2f(x, y));
		}

		timer.restart();
	}

	void update(sf::Time deltaTime)
	{
		if(timer.getElapsedTime().asSeconds() >= 1.0){
			dead = true;
			return;
		}

		if(anim_style == 0){
			this->y -= 5 * deltaTime.asSeconds();
			text.setPosition(sf::Vector2f(x, y));
		}
		/*switch(anim_style)
		{
			case 0:
			{
				this->y -= 5 * deltaTime.asSeconds();
			}
			break;
			case 1:
			{
				//...
			}
			break;
		}*/
		
		
	}

	void render(sf::RenderWindow* window)
	{
		if(!dead)
		{
			window->draw(this->text);
		}
	}

	bool is_dead(){ return this->dead; }
};

#endif // NOTIFICATION_H