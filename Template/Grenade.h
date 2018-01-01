#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "bullet.h"

class Grenade : public bullet
{
public:
	Grenade(float x = 0, float y = 0, int dir = 1);
	~Grenade();
	bool Collision(updateable*, sf::Vector2u&, sf::Vector2u&, float& size);
	bool CollisionRange(updateable*, sf::Vector2u&, sf::Vector2u&, float& size);
	bool outOfBounds();
	void update(int, int, float, sf::Vector2f&, sf::Vector2u&);
	void toss(float);
	void render(sf::RenderWindow&, Camera&);

	sf::Vector2f acceleration;
	sf::Vector2f gravity;
	sf::Vector2f velocity1;
	sf::Vector2f pos;
	int damage;
	int range;
};
