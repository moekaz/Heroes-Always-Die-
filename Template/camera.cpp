#include "camera.h"

Camera::Camera()
{
	position.x = 0;
	position.y = 0;
}

Camera::~Camera() {}

void Camera::update(int width, int height, float time, sf::Vector2f& player_position , sf::Vector2u& size) {}

void Camera::updateCamera(sf::Vector2f& playerPosition, sf::Vector2f& gameSize, sf::VideoMode& screenSize)
{
	//keep player mid screen by setting the camera to mid screen
	position.x = playerPosition.x - screenSize.width / 2;
	position.y = playerPosition.y - screenSize.height / 2;

	// y position is in last half of the game
	if (playerPosition.y >= gameSize.y - screenSize.height / 2 && playerPosition.y <= gameSize.y)
		position.y = gameSize.y - screenSize.height;
	//y position is in first half of the game
	else if (playerPosition.y <= screenSize.height / 2 && playerPosition.y >= 0)
		position.y = 0;

	//x position in last half of the game
	if (playerPosition.x >= gameSize.x - screenSize.width / 2 && playerPosition.x <= gameSize.x)
		position.x = gameSize.x - screenSize.width;
	//x position in first half of screen in game
	else if (playerPosition.x <= screenSize.width / 2 && playerPosition.x >= 0)
		position.x = 0;
}