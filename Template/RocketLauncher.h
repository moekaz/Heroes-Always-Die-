#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "weapon.h"
#include "Rocket.h"

//static var for bullet name ?????????
class RocketLauncher : public Weapon
{
public:
	RocketLauncher(sf::SoundBuffer*);
	~RocketLauncher();
	void addBullet(float, float, int);
	void update(int, int, float, sf::Vector2f&, sf::Vector2u&);
	void render(sf::RenderWindow&, Camera&);
	void render(sf::RenderWindow&);
};
