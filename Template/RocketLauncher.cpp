#include "RocketLauncher.h"

RocketLauncher::RocketLauncher(sf::SoundBuffer* buff) 
{
	type = 102;
	fireDelay = 0;
	maxDelay = 250;
	damage = 100;
	textDirLeft = "assets/gun03.png";
	textDirRight = "assets/gun04.png";
	numBullets = 10;
	shotSound = buff;
}

RocketLauncher::~RocketLauncher() {}

void RocketLauncher::addBullet(float x , float y , int dir)
{
	if (numBullets > 0)
	{
		numBullets--;
		bullets.push_back(new Rocket(x, y, dir));
	}
}

void RocketLauncher::update(int direction , int xSize, float time , sf::Vector2f& pos, sf::Vector2u& playerSize)
{
	//decrement fireDelay
	if (fireDelay != 0) { fireDelay -= time; }

	if (direction == 1) { position.x = pos.x; }
	else { position.x = pos.x + playerSize.x - xSize; }
	position.y = pos.y + (playerSize.y / 2) + 10;
}

void RocketLauncher::render(sf::RenderWindow& window , Camera& camera)
{
	//draw gun 
	window.draw(sprite);
	//draw bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->sprite.setPosition(bullets[i]->position.x - camera.position.x, bullets[i]->position.y - camera.position.y);
		window.draw(bullets[i]->sprite);
	}
}

void RocketLauncher::render(sf::RenderWindow& window){}