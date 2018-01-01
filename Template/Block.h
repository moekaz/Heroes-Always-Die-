#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "stage.h"
#include "Camera.h"

#define UP_COLLISION 1
#define DOWN_COLLISION 2
#define LEFT_COLLISION 3
#define RIGHT_COLLISION 4

class Block : public stage
{
public:
	Block(float x = 500 , float y = 500);
	~Block();
	bool Collision(character* , int* , sf::Vector2u& , sf::Vector2u&);
	void render(sf::RenderWindow& , Camera&);
	void update(int , int , float , sf::Vector2f& , sf::Vector2u&);
};