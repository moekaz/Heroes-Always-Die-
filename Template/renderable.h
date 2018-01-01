#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"
#include "camera.h"

class renderable : public virtual entity
{
public:
	virtual void render(sf::RenderWindow&, Camera&) = 0;
	sf::Sprite sprite;
};