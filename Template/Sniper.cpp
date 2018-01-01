#include "Sniper.h"

Sniper::Sniper(sf::SoundBuffer* buff)
{
	type = 103;
	position = sf::Vector2f(0, 0);
	fireDelay = 0;								//delay between shots
	maxDelay = 200;							//max delay reset value
	damage = 70;								//damage caused by weapon
	textDirRight = "assets/gun05.png";
	textDirLeft = "assets/gun06.png";
	numBullets = 5;								//bullet number for sniper
	//if (!shotSound.loadFromFile("assets/SniperSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }	//get Snipersound
	shotSound = buff;
}

Sniper::~Sniper() {}

void Sniper::update(int direction, int xSize, float time, sf::Vector2f& pos, sf::Vector2u& playerSize)
{
	//decrement fireDelay
	if (fireDelay != 0) { fireDelay -= time; }

	//set weapon position
	if (direction == 1) { position.x = pos.x; }
	else { position.x = pos.x + playerSize.x - xSize; }
	position.y = pos.y + (playerSize.y / 2) + 10;
}

void Sniper::addBullet(float x, float y, int dir) 
{
	//shoot bullet
	if (numBullets > 0)
	{
		numBullets--;
		bullets.push_back(new gunBullets(x, y, dir, 25 , "assets/bullet05.png"));
	}
}

void Sniper::render(sf::RenderWindow& window, Camera& camera)
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

void Sniper::render(sf::RenderWindow& window){ /*draw in inventory menu*/ }