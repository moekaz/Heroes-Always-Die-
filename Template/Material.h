#pragma once

#include "item.h"
#include "character.h"

class Material : public Item
{
public:
	Material(int type = 1);
	~Material();

	//void setPosition(sf::Vector2f, int, int, int, int, int);
	void setPosition(sf::Vector2f inventoryPosition, int width, int height, int boxwidth, int boxheight, int num)
	{
		int col = num % width;
		int row = num / width;

		position.x = inventoryPosition.x + col * boxwidth;
		position.y = inventoryPosition.y + row * boxheight;
	}

	bool Collision(character*, sf::Vector2u&, sf::Vector2u&);

	void render(sf::RenderWindow&, Camera&);
};