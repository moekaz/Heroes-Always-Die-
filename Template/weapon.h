#pragma once

#include <SFML/Audio.hpp>
#include "item.h"
#include "renderable.h"
#include "bullet.h"
#include <string>

class Weapon : public Item
{
public:
	virtual void addBullet(float, float, int) = 0;
	virtual void update(int, int, float, sf::Vector2f&, sf::Vector2u&) = 0;
	void setPosition(sf::Vector2f inventoryPosition, int width, int height, int boxwidth, int boxheight, int num)
	{
		int col = num % width;
		int row = num / width;

		position.x = inventoryPosition.x + col * boxwidth;
		position.y = boxheight / 2 + inventoryPosition.y + row * boxheight;
	}

	virtual void render(sf::RenderWindow&, Camera&) = 0;
	int numBullets;
	int fireDelay;						//current delay time
	int maxDelay;						//reset value 
	int damage;							//damage that the weapon casues
	std::string textDirRight;			//texturenames
	std::string textDirLeft;
	std::vector<bullet*> bullets;		//bullet ammo might need to change that to a bullet array and weapon might be an interface
	sf::SoundBuffer* shotSound;
};