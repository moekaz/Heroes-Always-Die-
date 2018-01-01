#include "gunBullets.h"
#include <iostream>

gunBullets::gunBullets(float x , float y , int dir , int vel ,std::string textdir)
{
	position = sf::Vector2f(x, y);		//bullet position
	velocity = vel;						//bullet velocity
	direction = dir;					//this is for bullet shooting directionality
	textDir = textdir;
	distance = 1300;						//needs fixing
}

gunBullets::~gunBullets() {}

bool gunBullets::outOfBounds() { return distance <= 0; }

bool gunBullets::Collision(updateable* obj , sf::Vector2u& mySize , sf::Vector2u& objSize , float& size)
{
	//rectangle bind the bullet
	return !(obj->position.x + objSize.x < position.x ||				        //left side collision
			 obj->position.x > position.x + mySize.x  ||						//right side colision
			 obj->position.y + objSize.y < position.y ||					    //top down collision
			 obj->position.y > position.y + mySize.y);                          //bottom up collision					
}

void gunBullets::update(int x , int y , float time , sf::Vector2f& v , sf::Vector2u& size)
{
	position.x += velocity*time*direction; // add to its x value for the moment
	distance -= velocity*time;
}

void gunBullets::render(sf::RenderWindow& window , Camera& camera)
{}