#include "Rocket.h"

Rocket::Rocket(float x , float y , int dir)
{
	position = sf::Vector2f(x, y);
	velocity = 7;
	range = 200;
	direction = dir;
	textDir = "assets/bullet03.png";
	distance = 1300;
}

Rocket::~Rocket() {}

bool Rocket::outOfBounds()
{
	return distance <= 0;
}

//second collision check for explosion 
bool Rocket::Collision(updateable* obj, sf::Vector2u& mySize, sf::Vector2u& objSize, float& size)
{
	//rectangle bind the bullet
	return !(obj->position.x + objSize.x < position.x ||				        //left side collision
		obj->position.x > position.x + mySize.x ||						//right side colision
		obj->position.y + objSize.y < position.y ||					    //top down collision
		obj->position.y > position.y + mySize.y);                          //bottom up collision);						
}

bool Rocket::CollisionRange(updateable* obj, sf::Vector2u& mySize, sf::Vector2u& objSize, float& size)
{
	return !(position.x + mySize.x / 2 + range  < obj->position.x ||							//left side collision
			 position.x + mySize.x / 2 - range > obj->position.x + objSize.x ||						//right side colision
			 position.y + mySize.y / 2 + range < obj->position.y ||									//top down collision
			 position.y + mySize.y / 2 - range > obj->position.y + objSize.y);                       //bottom up collision				

}

void Rocket::update(int x, int y, float time, sf::Vector2f& v, sf::Vector2u& size)
{
	position.x += velocity * time * direction; // add to its x value for the moment
	distance -= velocity * time;
} 

void Rocket::render(sf::RenderWindow& window, Camera& camera) {}