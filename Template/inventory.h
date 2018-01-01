#pragma once

#include "Material.h"
#include "weapon.h"
#include "entity.h"
#include "camera.h"
#include "item.h"

class Inventory : public entity
{

public:
	Inventory();
	~Inventory();
	bool addItem(Item*);
	bool reduceItem(int);
	bool reduceMaterial(int);
	void updateSize(int, int);
	void render(sf::RenderWindow& window);	//render in inventory menu

	int vertex_width, vertex_height;
	int width, height;
	sf::VertexArray vertexArray;
	sf::Texture spriteSheet;
	sf::Sprite title;
	sf::Sprite throwing;

	std::vector<Item*> materials;									//inventory is just a vector of items
																	//std::vector											//and can only hold 2 weapons(debateable)

	bool drop;
};