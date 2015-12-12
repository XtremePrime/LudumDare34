#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "gameobject.hpp"

class State;
class Game
{
private:
	sf::RenderWindow window;
	const int GAME_WIDTH = 860, GAME_HEIGHT = 640;
	const float SCALE = 4.0;
	bool is_running = true;
	sf::Clock clock;
	std::vector<State*> state_stack;
	sf::Image icon;
	GameObject gameobject;
	sf::ContextSettings settings;
	sf::View view;

	void init();
	void update(sf::Time);
	void handle_events(sf::Event);
	void render(sf::RenderWindow&);
public:
	void change_state(State* state);
	void push_state(State* state);
	void pop_state();

	void run();
	void quit();

	sf::RenderWindow* get_window() { return &window; }
	GameObject* get_gameobject() { return &gameobject; }
	std::vector<State*> get_state_stack() { return state_stack; }
	int get_width() { return this->GAME_WIDTH; }
	int get_height() { return this->GAME_HEIGHT; }
	float get_scale(){ return this->SCALE; }
};

#endif // GAME_H
