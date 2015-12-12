#ifndef BUTTON_H
#define BUTTON_H

#include <sstream>

class Button
{
private:
	int x, y, w, h;
	sf::FloatRect rect;
public:
	Button(){}
	Button(int xx, int yy, int ww, int hh)
	{
		init(xx, yy, ww, hh);
	}

	void init(int xx, int yy, int ww, int hh)
	{
		this->x = xx;
		this->y = yy;
		this->w = ww;
		this->h = hh;
	}

	bool clicked(sf::Vector2f c)
	{
		// std::cout << c.x << "," << c.y << "," << x << "," << y << "," << w << "," << h << "\n";
		if( (c.x >= x && c.x <= (x+w)) && (c.y >= y && c.y <= (y+h)) )
			return true;
		return false;
	}

	const std::string debug(){
	    std::stringstream ss;
	    ss << x << "," << y << "," << w << "," << h;
		return ss.str();
	}
};

#endif // BUTTON_H
