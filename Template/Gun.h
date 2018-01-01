#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include "weapon.h"
#include "gunBullets.h"
#include "camera.h"

class Gun :public Weapon
{
public:
	Gun(sf::SoundBuffer*);
	~Gun();
	void update(int, int, float, sf::Vector2f&, sf::Vector2u&);
	void addBullet(float, float, int);
	void render(sf::RenderWindow& , Camera&);
	void render(sf::RenderWindow&);
};