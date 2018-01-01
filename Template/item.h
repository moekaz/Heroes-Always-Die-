#pragma once

#include "renderable.h"
#include "camera.h"
#include <string>

#include <iostream>
using namespace std;

//interface for items (anything that can be held in our inventory eg. weapons, crafting items,)
class Item : public renderable
{
public:
	virtual void setPosition(sf::Vector2f, int, int, int, int, int) = 0;
	virtual void render(sf::RenderWindow&, Camera&) = 0;
	void render(sf::RenderWindow& window)
	{
		sprite.setPosition(position);
		window.draw(sprite);
	}

	int type;
};