#include "enemy.h"

Enemy::Enemy(sf::Vector2f position)
{
	this->position = position;
	prevPosition = position;
	this->velocity = sf::Vector2f(0, 0);
	ajump = sf::Vector2f(0, -3.3f);
	state = FALL;
	health = 50;								//setting enemy health
	maxHealth = health;							//setting enemy maxhealth
	timer = 60;									//for state machine
	randomGenerator = 0;
	direction = -1;
	damage = 10;
	onBlock = false;
	drop = rand() % 6 + 1;
}

Enemy::~Enemy() {} 

void Enemy::update(int width, int height, float time, sf::Vector2f& gravity , sf::Vector2u& size)
{
	//set prevPosition
	prevPosition = position;

	//AI!!!!!!!!
	if (timer == 0)
	{
		//state generation
		randomGenerator = rand() % 4;		
		if (randomGenerator == 0) { shoot(size); }
		if (randomGenerator == 1) { moveForward(time); }
		if (randomGenerator == 2) { moveBackward(time); }
		if (randomGenerator == 3) { jump(width , height , time); }

		timer = 60;		//reset timer
	} else { timer--; }	//decrement timer 

	//adding gravity
	if (this->state != GROUND) { velocity.y += gravity.y * time; }

	//from jumping to falling
	if (velocity.y > 0 && this->state == JUMP) { this->state = FALL; }

	//max capping on velocity
	if (velocity.y > 3) { velocity.y = 3; }
	
	//adding velocity   deltaTime updating not working well
	position.x += velocity.x * time;
	position.y += velocity.y * time;

	//reset velocity
	velocity.x = 0;
}

void Enemy::shoot(sf::Vector2u& size)
{
	//create a bullet to shoot
	if (direction == 1){ bullets.push_back(new gunBullets(position.x + size.x , position.y + size.y / 2 , direction)); } //a little bit of offset
	else { bullets.push_back(new gunBullets(position.x - 20 , position.y + size.y / 2 , direction)); }	//estimation of size of the bullet!!
}

void Enemy::moveBackward(float time)
{
	direction = 1;
	velocity.x += time * 10;				//needs work!!
}

void Enemy::moveForward(float time)
{
	direction = -1;
	velocity.x -= time * 10;				//needs work!!
	canJump = true;
}

void Enemy::jump(int i, int j, float time)
{
	//JUMP!!
	if (this->state == GROUND)
	{
		velocity.y += ajump.y;
		canJump = true;
		this->state = JUMP;
		this->onBlock = false;
	}
}

void Enemy::render(sf::RenderWindow& window, Camera& camera)
{
	//set positions
	sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);
	healthBar.setPosition(position.x + 10 - camera.position.x, position.y - 20 - camera.position.y);

	//draw
	window.draw(healthBar);
	window.draw(sprite);

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->sprite.setPosition(bullets[i]->position.x - camera.position.x, bullets[i]->position.y - camera.position.y);
		window.draw(bullets[i]->sprite);
	}
}
