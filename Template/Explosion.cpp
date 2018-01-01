#include "Explosion.h"

Explosion::Explosion(float x  , float y)
{
	position = sf::Vector2f(x, y);
	animFrame = 0;
	elapsedTime = 0;
	animRectx = 0;
	animRecty = 0;
}

void Explosion::update(float time)
{
	elapsedTime += time;
}

void Explosion::render(sf::RenderWindow& window , Camera& camera)
{
	//check animation frame and all of that then render
	//might not want that to be camera affected
	if (elapsedTime/100 >= animFrame / 4)
	{
		//move the animation
		//check for moving a row
		if (animRectx == 4) { animRectx = 0;  animRecty++; }
		sprite.setTextureRect(sf::IntRect(animRectx * 64, animRecty * 64, 64, 64));
		animRectx++;
		animFrame++;
	}

	sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);
	window.draw(sprite);
}

