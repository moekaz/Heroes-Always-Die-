#include "Material.h"
#include <iostream>
using namespace std;

Material::Material(int type) { this->type = type; }

Material::~Material() {}

bool Material::Collision(character* player, sf::Vector2u& otherSize, sf::Vector2u& mySize)
{
	if (player->position.x > position.x + mySize.x) return false;
	if (player->position.x + otherSize.x < position.x) return false;
	if (player->position.y > position.y + mySize.y) return false;
	if (player->position.y + otherSize.y < position.y) return false;

	return true;
}

void Material::render(sf::RenderWindow& window, Camera& camera) 
{
	sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);
	window.draw(sprite);
}