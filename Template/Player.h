#pragma once

#include <SFML/Graphics.hpp>
#include "defs.h"
#include "character.h"
#include "gunBullets.h"
#include "camera.h"
#include "inventory.h"
#include "weapon.h"
#include "Gun.h"
#include "RocketLauncher.h"
#include "Grenade.h"
#include "Sniper.h"
#include "HealingStaff.h"

class Player : public character
{
public:
	Player();
	~Player();
	void update(int , int , float ,sf::Vector2f& , sf::Vector2u&);
	void setVelocity(float, float);
	void jump(int, int, float);
	void render(sf::RenderWindow& , Camera& camera);

	Inventory inventory;				//player inventory
	Weapon* mainWeapon;					//our weapon should be a pointer here (main weapon and secondary weapon idea)
	Weapon* secondaryWeapon;
	sf::Sprite healthBar;
	std::vector<Grenade> grenades;
	int grenNum;
	float animFrame;
	int animRect;
	float elapsedTime;
	bool move;
	bool InventoryOpen;
	
};
