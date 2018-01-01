#pragma once

#include "character.h"
#include "defs.h"
#include "camera.h"
#include "bullet.h"
#include "gunBullets.h"
#include <iostream>


class Enemy : public character {

public:

	Enemy(sf::Vector2f position = sf::Vector2f(0, 0));
	~Enemy();
	void update(int, int, float, sf::Vector2f& , sf::Vector2u&);
	void render(sf::RenderWindow&, Camera&);
	void shoot(sf::Vector2u&);
	void moveForward(float);
	void moveBackward(float);
	void jump(int, int, float);

	sf::Sprite healthBar;    //might render a health bar for each enemy above them !!!
	int timer;				 // to move between behavior
	int randomGenerator;
	std::vector<bullet*> bullets;
	int damage;
	int drop;
};