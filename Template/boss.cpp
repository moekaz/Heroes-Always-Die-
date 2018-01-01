#include "boss.h"

Boss::Boss(sf::Vector2f position) {
	this->position = position;
	maxHealth = 1000;
	health = maxHealth;
	timer = 30;
	randomGenerator = 0;
	direction = -1;
	damage = 20;
}

Boss::~Boss() {}

void Boss::update(int width, int height, float time, sf::Vector2f& gravity, sf::Vector2u& size) 
{
	prevPosition = position;

	if (timer == 0)
	{
		randomGenerator = rand() % 10;
		if (randomGenerator <= 7) { shoot(size); }
		else if (randomGenerator == 8) { moveForward(time); }
		else if (randomGenerator == 9) { moveBackward(time); }

		timer = 30;
	}
	else { timer--; }
	
	position.x += velocity.x * time;
	
	velocity.x = 0;
}

void Boss::moveForward(float time)
{
	if (position.x > boss_range)
	{
		direction = 1;
		velocity.x += time * 10;
	}
}

void Boss::moveBackward(float time)
{
	if (position.x < boss_range_end)
	{
		direction = -1;
		velocity.x -= time * 10;
	}
}