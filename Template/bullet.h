#pragma once

#include "updateable.h"
#include "renderable.h"
#include <string>

//interface for every type of projectile we will be using (regbullets , rockets , grenades etc...)
class bullet : public updateable , public renderable 
{
public:
	virtual bool Collision(updateable* , sf::Vector2u& , sf::Vector2u& , float&) = 0;
	virtual bool outOfBounds() = 0;
	std::string textDir;		//texture directory to be able to load different bullets
	float velocity;
	int direction;
	int distance;
};