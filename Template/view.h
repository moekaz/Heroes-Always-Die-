#pragma once

#include <SFML/Graphics.hpp>
#include "model.h"
#include "Manager.h"
#include <iostream>

class View
{
public:
	View(Model*);
	~View();
	void render();

	Camera camera;
	Model* model;
	Manager manager;
	sf::RenderWindow window;
	float fps;
	sf::Font font;
	sf::Text HUD;
	sf::Sprite Bak;
	sf::Sprite menuScreen;
	sf::Sprite endingScreen;
};