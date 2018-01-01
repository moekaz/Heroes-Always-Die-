#pragma once

#include <SFML\Graphics.hpp>
#include "weapon.h"
#include "camera.h"

class HealingStaff : public Weapon
{
public:
	HealingStaff(sf::SoundBuffer*);
	~HealingStaff();
	void update(int, int, float, sf::Vector2f&, sf::Vector2u&);
	void addBullet(float, float, int);
	void render(sf::RenderWindow&, Camera&);
};
