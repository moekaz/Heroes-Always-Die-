#pragma once

#include <SFML/Graphics.hpp>
#include <SFML\Audio.hpp>
#include "Player.h"
#include "Block.h"
#include "Platform.h"
#include "gunBullets.h"
#include "enemy.h"
#include "Explosion.h"
#include "Material.h"
#include "Craftable.h"
#include "boss.h"

//Music by Eric Matyas
//www.soundimage.org

class Model
{
public:
	Model();
	~Model();
	void update(float , sf::Vector2f&);
	void blockCollision(sf::Vector2f&);			
	void platformCollision(sf::Vector2f&); 
	void bulletCollision(float , sf::Vector2f&);
	void enemyDies(int, sf::Vector2f);
	void restart();

	int gameState;
	Boss boss;
	Craftable craftable;				//to store everything which is craftable
	Player player;						//player
	int dataCols, dataRows;				//rows and cols of game map
	bool craftOpen;
	std::vector<Enemy> enemies;			//enemies
	std::vector<stage*> stages;			//blocks and platforms of game
	std::vector<Explosion*> explosions;	//explosions
	std::vector<Material*> materials;	//materials
	sf::VideoMode dims;					//need screen dimensions
	sf::Vector2f gravity;				//game Gravity
	sf::Vector2f gameSize;				//size of entire game map
	sf::Vector2u sizeBlocks;			//sizes of all assets!!!
	sf::Vector2u sizePlatforms;				
	sf::Vector2u sizeBullets;
	sf::Vector2u sizeEnemies;
	sf::Vector2u sizePlayer;
	sf::Vector2u sizeWeapon;
	sf::Vector2u sizeHealthBar;
	sf::Vector2u sizeEnemHealthBar;
	sf::Vector2u sizeGrenade;
	sf::Vector2u sizeEnemyBullets;
	sf::Vector2u sizeMaterial;
	sf::Vector2u sizeBoss;
	sf::SoundBuffer DropSound;			//sound buffers
	sf::SoundBuffer CraftedSound;
	sf::SoundBuffer CraftingSound;
	sf::SoundBuffer InventorySound;
	sf::SoundBuffer HealingSound;
	sf::SoundBuffer SniperSound;
	sf::SoundBuffer ExplosionSound;		
	sf::SoundBuffer LauncherSound;
	sf::SoundBuffer GunShotSound;
	sf::SoundBuffer ItemSound;			//when you pick up an item
	sf::Sound sound;					//give the buffer sound to it
	sf::Music gameMusic;				//game music
};