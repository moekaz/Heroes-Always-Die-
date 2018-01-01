#pragma once

#include "updateable.h"

//game camera
class Camera : public updateable 
{
public:
	Camera();
	~Camera();
	void update(int, int, float, sf::Vector2f& , sf::Vector2u&);
	void updateCamera(sf::Vector2f&, sf::Vector2f&, sf::VideoMode&);
};