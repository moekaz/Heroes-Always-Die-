#pragma once

#include "Entity.h"
#include "inventory.h"
#include "Material.h"
#include "weapon.h"

class Craftable : public entity
{

public:
	Craftable();
	~Craftable();

	sf::Sprite title;
	sf::Sprite slot;

	float height;

	std::map<std::string, sf::Sprite> weapon_list;
	std::map<int, sf::Sprite> material_list;

	std::map<std::string, std::vector<int>> craft_list;

	//to store the position of the sprite for the thing player can craft
	std::vector<std::string> craft_position;

	void setCraft(Inventory&);

	void render(sf::RenderWindow&, sf::Vector2f);
};