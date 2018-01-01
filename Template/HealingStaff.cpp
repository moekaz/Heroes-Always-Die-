#include "HealingStaff.h"

HealingStaff::HealingStaff(sf::SoundBuffer* buff)
{
	type = 104;
	position = sf::Vector2f(0, 0);
	fireDelay = 0;
	maxDelay = 100;
	damage = 10;
	textDirRight = "assets/gun07.png";
	textDirLeft = "assets/gun08.png";
	numBullets = 5;
	shotSound = buff;
}

HealingStaff::~HealingStaff() {}

void HealingStaff::update(int direction, int xSize, float time, sf::Vector2f& pos, sf::Vector2u& playerSize)
{
	if (fireDelay != 0) { fireDelay -= time;  }

	if (direction == 1) { position.x = pos.x; }
	else { position.x = pos.x + playerSize.x - xSize;  }
	position.y = pos.y + (playerSize.y / 2) + 10;
}

void HealingStaff::addBullet(float x, float y, int dir)
{
	//no need to add bullet
}

void HealingStaff::render(sf::RenderWindow& window, Camera& camera)
{
	window.draw(sprite);
}