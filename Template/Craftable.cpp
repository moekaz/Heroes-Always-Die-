#include "Craftable.h"

Craftable::Craftable() { height = 0; }

Craftable::~Craftable() {}

void Craftable::setCraft(Inventory& inv)
{
	craft_position.clear();
	std::map<std::string, std::vector<int>>::iterator it;  //for the craft list
	std::vector<int>::iterator innerit;                    //for each weapon inside craft list
	std::vector<Item*>::iterator materialit;           //for each materials
	for (it = craft_list.begin(); it != craft_list.end(); it++)
	{
		std::vector<int> materials = it->second;
		bool canCraft = true;
		for (innerit = materials.begin(); innerit != materials.end(); innerit++)
		{
			bool hasMaterial = false;
			for (materialit = inv.materials.begin(); materialit != inv.materials.end(); materialit++)
			{
				Item* mat = *materialit;
				if (typeid(*mat).name() == typeid(Material).name())
					if (*innerit == mat->type)
					{
						hasMaterial = true;
						break;
					}
			}
			if (hasMaterial == false)
			{
				canCraft = false;
				break;
			}
		}
		if (canCraft)
		{
			craft_position.push_back(it->first);
		}
	}
}

void Craftable::render(sf::RenderWindow& window, sf::Vector2f player_position)
{
	sf::Vector2f startingPosition = sf::Vector2f(player_position.x - 130, player_position.y + height);

	title.setPosition(startingPosition.x, startingPosition.y - 30);
	window.draw(title);
	for (int i = 0; i < craft_position.size(); i++)
	{
		weapon_list[craft_position[i]].setPosition(startingPosition.x + 10, startingPosition.y + i * 85 + 10);

		slot.setPosition(startingPosition.x, startingPosition.y + i * 85);
		window.draw(slot);

		window.draw(weapon_list[craft_position[i]]);
		for (int j = 0; j < craft_list[craft_position[i]].size(); j++)
		{
			material_list[craft_list[craft_position[i]][j]].setPosition(startingPosition.x + 10 + (j * 30), startingPosition.y + i * 85 + 30 + 10);
			window.draw(material_list[craft_list[craft_position[i]][j]]);
		}
	}
}