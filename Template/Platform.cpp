#include "Platform.h"

#include <iostream>
using namespace std;

Platform::Platform(float x, float y)
{
	position = sf::Vector2f(x, y);
}

Platform::~Platform() {}

void Platform::update(int x, int y, float  f, sf::Vector2f& v , sf::Vector2u&) {}

bool Platform::Collision(character* object , int* result , sf::Vector2u& mySize ,sf::Vector2u& objSize)
{
	return object->position.x + objSize.x >= position.x &&
		   object->position.x <= position.x + mySize.x &&
		   object->position.y + objSize.y >= position.y &&
		   object->position.y + objSize.y <= position.y + mySize.y;
}

void Platform::render(sf::RenderWindow& window , Camera& camera) 
{
	this->sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);
	window.draw(sprite); 
}