#pragma once

#include "updateable.h"
#include "renderable.h"
#include "defs.h"

//Interface for game characters (player , enemies , npcs etc)
class character : public updateable , public renderable
{
public:
	sf::Vector2f movingSpeed;
	STATUS state;
	int health;
	int maxHealth;
	int direction;
	bool canJump;
	sf::Vector2f ajump;
	sf::Vector2f prevPosition;
	sf::Vector2f velocity;
	bool onBlock;
};