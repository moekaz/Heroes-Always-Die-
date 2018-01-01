#pragma once

#include <SFML/Graphics.hpp>
#include "bullet.h"
#include <string>

class gunBullets : public bullet
{
public:
	gunBullets(float x = 0 , float y = 0 , int dir = 1 , int vel = 10 , std::string textdir = "assets/bullet02.png");
	~gunBullets();
	bool Collision(updateable* , sf::Vector2u& , sf::Vector2u& , float& size);
	bool outOfBounds();
	void update(int , int , float , sf::Vector2f& , sf::Vector2u&);
	void render(sf::RenderWindow& , Camera&);
};
