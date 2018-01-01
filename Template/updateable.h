#pragma once
#include <SFML/Graphics.hpp>
#include "entity.h"

class updateable : public virtual entity
{
public:
	virtual void update(int , int , float, sf::Vector2f& , sf::Vector2u&) = 0;
};
