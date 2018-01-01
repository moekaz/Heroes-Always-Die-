#include "Player.h"
#include <iostream>

Player::Player()
{
	position = sf::Vector2f(500 , 200);			//player position
	prevPosition = position;					//prev position
	velocity = sf::Vector2f(0, 0);				//velocity
	movingSpeed = sf::Vector2f(2.5f, 2.5f);		//speed of moving around
	ajump = sf::Vector2f(0.f, -4.f);			//jump acceleration
	move = false;
	onBlock = false;
	canJump = false;							//jump bool
	state = FALL;
	health = 100;								//setting player health
	maxHealth = health;							//setting player maxHealth
	direction = 1;								//player direction
	healthBar.setPosition(20, 20);				//healthbar
	secondaryWeapon = NULL;
	grenNum = 4;								//num of grenades 
	animFrame = 0;								//animation Frame
	animRect = 0;								//animation position on spriteSheet
	elapsedTime = 0;
	InventoryOpen = false;
}

Player::~Player() {}

void Player::setVelocity(float time, float direction) { velocity.x = movingSpeed.x * direction; }

void Player::update(int width , int height , float time , sf::Vector2f& gravity , sf::Vector2u& size)
{
	//setting prevposition
	prevPosition = position;
	
	//adding gravity
	if (this->state != GROUND) { velocity.y += gravity.y * time; }

	//from jumping to falling
	if (velocity.y > 0 && this->state == JUMP) { this->state = FALL; }
	
	//max capping on velocity
	if (velocity.y > 3) { velocity.y = 3; }

	//adding velocity
	position.x += velocity.x * time;
	position.y += velocity.y * time;

	//reset velocity
	velocity.x = 0;

	//add Time for Animation purposes
	elapsedTime += time;
}

void Player::jump(int width, int height, float time)
{
	//JUMP!!
	if (state == GROUND)
	{
		state = JUMP;
		velocity.y = ajump.y;
		canJump = true;
		onBlock = false;
	}
}

void Player::render(sf::RenderWindow& window, Camera& camera)
{
	//move animation
	if (move)
	{
		if (elapsedTime/100 >= animFrame / 4.0)
		{
			animRect++;
			animFrame++;
			if (animRect == 4)
			{
				animFrame = 0;
				animRect = 0;
				move = false;
				elapsedTime = 0;
			}
			//hardcoded playerSize
			sprite.setTextureRect(sf::IntRect(animRect*62 , 0 , 62 , 88));
		}
	}

	//update the inventory position
	if (InventoryOpen)
	{
		inventory.position.x = position.x - inventory.width * inventory.vertex_width - camera.position.x - 25;
		inventory.position.y = position.y - camera.position.y - 75;
		inventory.updateSize(inventory.width, inventory.height);
	}

	//set player position
	sprite.setPosition(position.x - camera.position.x, position.y - camera.position.y);

	//set mainWeapon position
	mainWeapon->sprite.setPosition(mainWeapon->position.x - camera.position.x, mainWeapon->position.y - camera.position.y);

	//player weapon then bullets
	window.draw(healthBar);
	window.draw(sprite);
	mainWeapon->render(window , camera);

	//grenades
	for (int i = 0; i < grenades.size(); i++)
	{ 
		grenades[i].sprite.setPosition(grenades[i].position.x - camera.position.x , grenades[i].position.y - camera.position.y);
		window.draw(grenades[i].sprite);
	}
}

