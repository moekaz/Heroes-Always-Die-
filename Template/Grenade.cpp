#include "Grenade.h"

Grenade::Grenade(float x , float y , int dir)
{
	position = sf::Vector2f(x, y);
	range = 100;
	acceleration = sf::Vector2f(0, -3.3f);
	gravity = sf::Vector2f(0, 0.02f);
	velocity1 = sf::Vector2f(0, 0);
	direction = dir;
	velocity = 5;
	textDir = "assets/grenade.png";
	damage = 50;
	distance = 1300;
}

Grenade::~Grenade() {}

bool Grenade::outOfBounds() { return distance <= 0; }

bool Grenade::Collision(updateable* obj, sf::Vector2u& mySize, sf::Vector2u& objSize, float& size)
{
	//rectangle bind the bullet
	return !(obj->position.x + objSize.x < position.x ||				        //left side collision
		     obj->position.x > position.x + mySize.x  ||						//right side colision
		     obj->position.y + objSize.y < position.y ||					    //top down collision
		     obj->position.y > position.y + mySize.y);                          //bottom up collision	
}

bool Grenade::CollisionRange(updateable* obj, sf::Vector2u& mySize, sf::Vector2u& objSize, float& size)
{
	return !(position.x + mySize.x / 2 + range  < obj->position.x ||							//left side collision
		position.x + mySize.x / 2 - range > obj->position.x + objSize.x ||						//right side colision
		position.y + mySize.y / 2 + range < obj->position.y ||									//top down collision
		position.y + mySize.y / 2 - range > obj->position.y + objSize.y);                       //bottom up collision				
}

void Grenade::update(int x, int y, float time, sf::Vector2f& v, sf::Vector2u& size)
{
	//not the way to do things jump like trajectory
	velocity1.y += gravity.y * time;
	position.x += velocity * time * direction; // add to its x value for the moment
	position.y += velocity1.y * time;
	distance -= velocity * time;
}

void Grenade::toss(float time) { velocity1.y += acceleration.y; }

void Grenade::render(sf::RenderWindow&, Camera&) {}