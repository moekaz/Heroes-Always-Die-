#include "Gun.h"

Gun::Gun(sf::SoundBuffer* buff)
{
	type = 101;
	position = sf::Vector2f(0 , 0);
	fireDelay = 0;						//delay between shots
	maxDelay = 60;						//max delay reset value
	damage = 10;						//damage caused by weapon
	textDirRight = "assets/gun01.png";
	textDirLeft = "assets/gun02.png";
	numBullets = 40;
	//if (!shotSound.loadFromFile("assets/laserSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	shotSound = buff;
}

Gun::~Gun() {}

void Gun::update(int direction, int xSize, float time, sf::Vector2f& pos, sf::Vector2u& playerSize)
{
	//decrement fireDelay
	//reset it if it is 0 do we need to use time for that???
	if (fireDelay != 0) { fireDelay -= time; }

	if (direction == 1) { position.x = pos.x; }
	else { position.x = pos.x + playerSize.x - xSize; }
	position.y = pos.y + (playerSize.y / 2) + 10;
}

void Gun::addBullet(float x, float y, int dir) { 
	if (numBullets > 0)
	{
		numBullets--;
		bullets.push_back(new gunBullets(x, y, dir));
	}
}

void Gun::render(sf::RenderWindow& window, Camera& camera)
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

void Gun::render(sf::RenderWindow& window)
{
	//draw in inventory menu
}

