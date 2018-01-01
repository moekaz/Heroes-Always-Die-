#ifndef GAME_H
#define GAME_H

#include <SFML\Graphics.hpp>
#include "controller.h"
#include "view.h"
#include "model.h"

class Game
{

public:
	Game();
	~Game();
	void loop();

	sf::Clock clock;
	float deltaTime;
	Controller* controller;
	Model* model;
	View* view;
};
#endif // !GAME_H
