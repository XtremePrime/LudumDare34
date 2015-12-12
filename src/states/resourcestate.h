#ifndef RESOURCESTATE_H
#define RESOURCESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include "state.h"

class ResourceState : public State
{
private:
    bool paused = false;
protected:
	static ResourceState* _instance;
	ResourceState(){}
public:
	static ResourceState* instance();
    ~ResourceState(){}
	void init(Game* game);
	void cleanup();

	void handle_events(Game* game, sf::Event event);
	void update(Game* game, sf::Time deltaTime);
	void render(Game* game);

 	void pause();
 	void resume();

 	template<typename T>
 	void clear_vector(std::vector<T*>& v)
 	{
 		for(int i = 0; i < v.size(); ++i)
 			delete (v[i]);
 		v.clear();
 	}
};

#endif // RESOURCESTATE_H
