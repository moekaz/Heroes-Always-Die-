#pragma once

#include "Player.h"
#include "stage.h"
#include "camera.h"

class Platform : public stage
{
public:
	Platform(float x = 500 , float y = 500 );
	~Platform();
 
	bool Collision(character* , int* , sf::Vector2u& ,sf::Vector2u&);
	void render(sf::RenderWindow& , Camera&);
	void update(int, int, float, sf::Vector2f& , sf::Vector2u&);
};
