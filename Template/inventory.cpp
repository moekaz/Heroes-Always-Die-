#include "inventory.h"

Inventory::Inventory() {
	vertexArray.setPrimitiveType(sf::Quads);
	this->width = 3;
	this->height = 3;
	position = sf::Vector2f(300, 300);
	drop = false;
}

Inventory::~Inventory() {}

bool Inventory::addItem(Item* item)
{
	if (materials.size() + 1 > this->width * this->height) return false;
	materials.push_back(item);
	return true;
}

bool Inventory::reduceItem(int index)
{
	if (index < 0 || index > materials.size()) return false;
	materials.erase(materials.begin() + index);
	return true;
}

bool Inventory::reduceMaterial(int type)
{
	for (int i = 0; i < materials.size(); i++)
	{
		Item* items = materials[i];
		if (typeid(*items).name() == typeid(Material).name())
		{
			if (items->type == type)
			{
				materials.erase(materials.begin() + i);
				return true;
			}
		}
	}
	return false;
}

void Inventory::updateSize(int w, int h)
{
	this->width = w;
	this->height = h;

	title.setPosition(position.x + this->width * vertex_width, position.y);

	vertexArray.resize(this->width * this->height * 4);

	//top left corner
	sf::Vertex* current_quad = &this->vertexArray[0];
	current_quad[0].position = sf::Vector2f(position.x + 0, position.y + 0);
	current_quad[0].texCoords = sf::Vector2f(0, 0);
	current_quad[1].position = sf::Vector2f(position.x + vertex_width, position.y + 0);
	current_quad[1].texCoords = sf::Vector2f(vertex_width, 0);
	current_quad[2].position = sf::Vector2f(position.x + vertex_width, position.y + vertex_height);
	current_quad[2].texCoords = sf::Vector2f(vertex_width, vertex_height);
	current_quad[3].position = sf::Vector2f(position.x + 0, position.y + vertex_height);
	current_quad[3].texCoords = sf::Vector2f(0, vertex_height);

	//top right corner
	current_quad = &this->vertexArray[(width - 1) * 4];
	current_quad[0].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + 0);
	current_quad[0].texCoords = sf::Vector2f(2 * (vertex_width + 1), 0);
	current_quad[1].position = sf::Vector2f(position.x + vertex_width * width, position.y + 0);
	current_quad[1].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, 0);
	current_quad[2].position = sf::Vector2f(position.x + vertex_width * width, position.y + vertex_height);
	current_quad[2].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, vertex_height);
	current_quad[3].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + vertex_height);
	current_quad[3].texCoords = sf::Vector2f(2 * (vertex_width + 1), vertex_height);

	//bottom right corner
	current_quad = &this->vertexArray[(height * width - 1) * 4];
	current_quad[0].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + vertex_height * (height - 1));
	current_quad[0].texCoords = sf::Vector2f(2 * (vertex_width + 1), 2 * (vertex_height + 1));
	current_quad[1].position = sf::Vector2f(position.x + vertex_width * width, position.y + vertex_height * (height - 1));
	current_quad[1].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, 2 * (vertex_height + 1));
	current_quad[2].position = sf::Vector2f(position.x + vertex_width * width, position.y + vertex_height * height);
	current_quad[2].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, 2 * (vertex_height + 1) + vertex_height);
	current_quad[3].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + vertex_height * height);
	current_quad[3].texCoords = sf::Vector2f(2 * (vertex_width + 1), 2 * (vertex_height + 1) + vertex_height);

	//bottom left corner
	current_quad = &this->vertexArray[((height - 1) * width) * 4];
	current_quad[0].position = sf::Vector2f(position.x + 0, position.y + vertex_height * (height - 1));
	current_quad[0].texCoords = sf::Vector2f(0, 2 * (vertex_height + 1));
	current_quad[1].position = sf::Vector2f(position.x + vertex_width, position.y + vertex_height * (height - 1));
	current_quad[1].texCoords = sf::Vector2f(vertex_width, 2 * (vertex_height + 1));
	current_quad[2].position = sf::Vector2f(position.x + vertex_width, position.y + vertex_height * height);
	current_quad[2].texCoords = sf::Vector2f(vertex_width, 2 * (vertex_height + 1) + vertex_height);
	current_quad[3].position = sf::Vector2f(position.x + 0, position.y + vertex_height * height);
	current_quad[3].texCoords = sf::Vector2f(0, 2 * (vertex_height + 1) + vertex_height);


	//top line
	for (int i = 1; i < width - 1; i++)
	{
		current_quad = &this->vertexArray[i * 4];
		current_quad[0].position = sf::Vector2f(position.x + vertex_width * i, position.y + 0);
		current_quad[0].texCoords = sf::Vector2f(1 * (vertex_width + 1), 0);
		current_quad[1].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + 0);
		current_quad[1].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, 0);
		current_quad[2].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + vertex_height);
		current_quad[2].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, vertex_height);
		current_quad[3].position = sf::Vector2f(position.x + vertex_width * i, position.y + vertex_height);
		current_quad[3].texCoords = sf::Vector2f(1 * (vertex_width + 1), vertex_height);
	}

	//bottom
	for (int i = 1; i < width - 1; i++)
	{
		current_quad = &this->vertexArray[(i + (height - 1) * width) * 4];
		current_quad[0].position = sf::Vector2f(position.x + vertex_width * i, position.y + vertex_height * (height - 1));
		current_quad[0].texCoords = sf::Vector2f(1 * (vertex_width + 1), 2 * (vertex_height + 1));
		current_quad[1].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + vertex_height * (height - 1));
		current_quad[1].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, 2 * (vertex_height + 1));
		current_quad[2].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + vertex_height * height);
		current_quad[2].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, 2 * (vertex_height + 1) + vertex_height);
		current_quad[3].position = sf::Vector2f(position.x + vertex_width * i, position.y + vertex_height * height);
		current_quad[3].texCoords = sf::Vector2f(1 * (vertex_width + 1), 2 * (vertex_height + 1) + vertex_height);
	}

	//left
	for (int i = 1; i < height - 1; i++)
	{
		current_quad = &this->vertexArray[(i * width) * 4];
		current_quad[0].position = sf::Vector2f(position.x + 0, position.y + vertex_height * i);
		current_quad[0].texCoords = sf::Vector2f(0, 1 * (vertex_height + 1));
		current_quad[1].position = sf::Vector2f(position.x + vertex_width, position.y + vertex_height * i);
		current_quad[1].texCoords = sf::Vector2f(vertex_width, 1 * (vertex_height + 1));
		current_quad[2].position = sf::Vector2f(position.x + vertex_width, position.y + vertex_height * (i + 1));
		current_quad[2].texCoords = sf::Vector2f(vertex_width, 1 * (vertex_height + 1) + vertex_height);
		current_quad[3].position = sf::Vector2f(position.x + 0, position.y + vertex_height * (i + 1));
		current_quad[3].texCoords = sf::Vector2f(0, 1 * (vertex_height + 1) + vertex_height);
	}


	//right
	for (int i = 1; i < height - 1; i++)
	{
		current_quad = &this->vertexArray[(width - 1 + i * width) * 4];
		current_quad[0].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + vertex_height * i);
		current_quad[0].texCoords = sf::Vector2f(2 * (vertex_width + 1), 1 * (vertex_height + 1));
		current_quad[1].position = sf::Vector2f(position.x + vertex_width * width, position.y + vertex_height * i);
		current_quad[1].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, 1 * (vertex_height + 1));
		current_quad[2].position = sf::Vector2f(position.x + vertex_width * width, position.y + vertex_height * (i + 1));
		current_quad[2].texCoords = sf::Vector2f(2 * (vertex_width + 1) + vertex_width, 1 * (vertex_height + 1) + vertex_height);
		current_quad[3].position = sf::Vector2f(position.x + vertex_width * (width - 1), position.y + vertex_height * (i + 1));
		current_quad[3].texCoords = sf::Vector2f(2 * (vertex_width + 1), 1 * (vertex_height + 1) + vertex_height);
	}

	//center
	for (int i = 1; i < width - 1; i++)
	{
		for (int j = 1; j < height - 1; j++)
		{
			current_quad = &this->vertexArray[(i + j * width) * 4];
			current_quad[0].position = sf::Vector2f(position.x + vertex_width * i, position.y + vertex_height * j);
			current_quad[0].texCoords = sf::Vector2f(1 * (vertex_width + 1), 1 * (vertex_height + 1));
			current_quad[1].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + vertex_height * j);
			current_quad[1].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, 1 * (vertex_height + 1));
			current_quad[2].position = sf::Vector2f(position.x + vertex_width * (i + 1), position.y + vertex_height * (j + 1));
			current_quad[2].texCoords = sf::Vector2f(1 * (vertex_width + 1) + vertex_width, 1 * (vertex_height + 1) + vertex_height);
			current_quad[3].position = sf::Vector2f(position.x + vertex_width * i, position.y + vertex_height * (j + 1));
			current_quad[3].texCoords = sf::Vector2f(1 * (vertex_width + 1), 1 * (vertex_height + 1) + vertex_height);
		}
	}
	/**/
}

void Inventory::render(sf::RenderWindow& window) {
	window.draw(vertexArray, &spriteSheet);

	for (int i = 0; i < materials.size(); i++)
	{
		materials[i]->setPosition(position, width, height, vertex_width, vertex_height, i);
		materials[i]->render(window);
	}

	window.draw(title);

	if (drop)
	{
		throwing.setPosition(position.x, position.y - 20);
		window.draw(throwing);
	}
}