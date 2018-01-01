#pragma once

#include "enemy.h"
#include "camera.h"

class Boss : public Enemy {

public:
	Boss(sf::Vector2f = sf::Vector2f(0, 0));
	~Boss();
	void update(int, int, float, sf::Vector2f&, sf::Vector2u&);
	void moveForward(float);
	void moveBackward(float);

	float boss_range;
	float boss_range_end;
};