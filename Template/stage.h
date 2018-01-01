#pragma once
#include "renderable.h"
#include "character.h"

//interface for any world obj that we will jump , stand etc.. onto (eg. block or platform)
class stage : public renderable , public updateable
{
public:
	virtual bool Collision(character* , int* , sf::Vector2u& , sf::Vector2u&) = 0;
};