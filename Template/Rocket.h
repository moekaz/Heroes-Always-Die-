#pragma once

#include "bullet.h"
#include "updateable.h"
#include "Camera.h"

class Rocket : public bullet
{
public:
	Rocket(float x = 0, float y = 0 , int dir = 1);
	~Rocket();
	bool Collision(updateable*, sf::Vector2u&, sf::Vector2u&, float&);
	bool CollisionRange(updateable* , sf::Vector2u&, sf::Vector2u& , float&);
	bool outOfBounds();
	void update(int , int , float , sf::Vector2f& , sf::Vector2u&);
	void render(sf::RenderWindow&, Camera&);

	int range;		//range of explosion
};
