#include "Block.h"
#include <iostream>

Block::Block(float x , float y)
{
	position = sf::Vector2f(x , y);
}

Block::~Block() {}

bool Block::Collision(character* obj , int* result , sf::Vector2u& mySize , sf::Vector2u& objSize)
{
	if (!(obj->position.x + objSize.x < position.x ||				        //left side collision
		  obj->position.x > position.x + mySize.x  ||					    //right side colision
		  obj->position.y + objSize.y < position.y ||					    //top down collision
		  obj->position.y > position.y + mySize.y))                         //bottom up collision
	{
			if (obj->prevPosition.y + objSize.y <= position.y) { *result = 1; return true; }	//top Collision
			else if ((obj->prevPosition.x >= position.x + mySize.x) || (obj->prevPosition.x + objSize.x <= position.x)) { *result = 2; return true; } //side Collision
			else { *result = 3; return true; }	//bottom collision
	}
	return false;
}

void Block::update(int i , int j , float f , sf::Vector2f& v , sf::Vector2u&) {}

void Block::render(sf::RenderWindow& window , Camera& camera)
{
	this->sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);
	window.draw(sprite);
}