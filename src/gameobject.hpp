#include <string>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject
{
public:
	//- Level objects
	std::string level_name = "devtest";

	//- Options objects
	int width = 860, height = 640;
	bool has_music = true;
	bool has_sfx = true;
	float volume = 1.0;
	std::string username = "Player";
};

#endif // GAMEOBJECT_H
