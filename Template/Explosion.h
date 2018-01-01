#pragma once

#include <SFML\Graphics.hpp>
#include "renderable.h"
#include "camera.h"
#include <SFML/Audio.hpp>
#include <iostream>

//create an explosion after rockets and grenades collide with something
class Explosion : public renderable
{
public:
	Explosion(float x = 0 , float y = 0);		//we have to give these values
    //bool Collision();							//collision detection with enemies or is it with rocket??
	void update(float);							//update with delta time
	void render(sf::RenderWindow& , Camera&);

	float animFrame;							//which frame is the animation on 
	float elapsedTime;							// how much time has elapsed 
	int animRectx;								//which rectangle in the animation I am in
	int animRecty;		
	sf::SoundBuffer shotSound;
};
