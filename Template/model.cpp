#include "model.h"
#include <iostream>
#include <fstream>

//0 = menu
//1 = game
//2 = ending
Model::Model()
{
	dims.width = 1300;
	dims.height = 700;
	gravity = sf::Vector2f(0.f, 0.03f);		
	gameState = 2;				//Menu screen

	std::ifstream enemyHndl;
	enemyHndl.open("assets/enemyData.txt");
	//create variable for to store the size
	int numOfEnemies;
	int enemyTempx;
	int enemyTempy;

	boss = Boss(sf::Vector2f(148 * 48, 18 * 48 - 440));

	enemyHndl >> numOfEnemies;
	for (int i = 0; i < numOfEnemies; i++)
	{
		enemyHndl >> enemyTempx;
		enemyHndl >> enemyTempy;
		Enemy tempEnemy = Enemy(sf::Vector2f(enemyTempx * 48, enemyTempy * 48));
		enemies.push_back(tempEnemy);
	}

	std::ifstream dataHndl;
	dataHndl.open("assets/craftData.txt");
	//create every needed temp variable
	int numOfWeapon;
	int numOfMaterial;
	int currentMaterial;
	std::string weaponName;

	dataHndl >> numOfWeapon;
	for (int i = 0; i < numOfWeapon; i++)
	{
		dataHndl >> numOfMaterial;
		dataHndl >> weaponName;
		std::vector<int> materialList;
		std::cout << weaponName << ":" << numOfMaterial << std::endl;
		for (int j = 0; j < numOfMaterial; j++)
		{
			dataHndl >> currentMaterial;
			materialList.push_back(currentMaterial);
		}
		craftable.craft_list.insert(std::pair<std::string, std::vector<int>>(weaponName, materialList));
	}

	//read text file and create world
	std::ifstream fileHndl;
	fileHndl.open("assets/gameData.txt");
	fileHndl >> dataCols;
	fileHndl >> dataRows;
	int tempData;

	for (int i = 0; i < dataRows; i++)
	{
		for (int j = 0; j < dataCols; j++)
		{
			fileHndl >> tempData;

			std::cout << tempData;

			if (tempData == 2)
			{
				Platform* p = new Platform(j * 48, i * 48);
				stages.push_back(p);
			}
			else if (tempData == 3)
			{
				Block* b = new Block(j * 48 , i * 48);
				stages.push_back(b);
			}
		}
		std::cout << std::endl;
	}

	gameSize = sf::Vector2f(dataCols * 48, dataRows * 48);
	craftOpen = false;
}

Model::~Model() {}

void Model::update(float time , sf::Vector2f& cameraPos)
{
	//FUNCTION BREAKDOWN (platform CHECK , block CHECK , bullet check)

	//block collision
	blockCollision(cameraPos);

	//platform collision
	platformCollision(cameraPos);

	//bullet collision
	bulletCollision(time , cameraPos);

	//enemy updating after collision detection
	for (int i = 0; i < enemies.size(); i++)
	{
		//check position
		if (!((enemies[i].position.x >= cameraPos.x - 100 && enemies[i].position.x <= cameraPos.x + dims.width + 100) &&
			(enemies[i].position.y >= cameraPos.y - 100 && enemies[i].position.y <= cameraPos.y + dims.height + 100)))
		{
			enemies[i].bullets.clear(); 
			continue;
		}

		enemies[i].update(gameSize.x, gameSize.y, time, gravity, sizeEnemies);
	}

	/* update boss */
	if (!(boss.position.x > cameraPos.x + dims.width || boss.position.x + sizeBoss.x < cameraPos.x ||
		boss.position.y > cameraPos.y + dims.height || boss.position.y + sizeBoss.y < cameraPos.y))
	{
		boss.update(gameSize.x, gameSize.y, time, gravity, sizeEnemies);
	}
	
	//update player 
	player.update(gameSize.x , gameSize.y , time , gravity , sizePlayer); 

	//update player's weapon
	player.mainWeapon->update(player.direction , sizeWeapon.x , time , player.position , sizePlayer);

	for (int i = 0; i < materials.size(); i++)
	{
		//check position
		if (!((materials[i]->position.x >= cameraPos.x  && materials[i]->position.x <= cameraPos.x + dims.width) &&
			(materials[i]->position.y >= cameraPos.y  && materials[i]->position.y <= cameraPos.y + dims.height)))
			{ continue; }

		//check material pickup collision
		if (materials[i]->Collision(&player, sizePlayer, sizeMaterial))
		{
			// add material to the inventory
			if (player.inventory.addItem(materials[i]))
			{
				materials.erase(materials.begin() + i);
				sound.setBuffer(ItemSound);
				sound.play();
			}
		}
	}

	if (enemies.size() == 0)
	{
		//endgame
		gameState = 2;
	}
}

//FUNCTION TO DROP THE MATERIAL AFTER THE ENEMY DIES
void Model::enemyDies(int dropping, sf::Vector2f position)
{
	if (dropping <= 5)
	{
		Material* material = new Material();
		material->type = dropping;
		material->sprite = craftable.material_list[dropping];
		material->sprite.setScale(1.f, 1.f);
		material->position = position;
		materials.push_back(material);
	}
	else { std::cout << "not dropping anything" << std::endl; }
}

void Model::blockCollision(sf::Vector2f& cameraPos)
{
	int result = 0;
	bool Coll = false;

	/* player block collision */
	for (int i = 0; i < stages.size(); i++)
	{
		//check position 
		if (!(stages[i]->position.x >= player.position.x - sizeBlocks.x && stages[i]->position.x <= player.position.x + sizePlayer.x + sizeBlocks.x &&
			stages[i]->position.y >= player.position.y - sizeBlocks.y && stages[i]->position.y <= player.position.y + sizePlayer.y + sizeBlocks.y))
			{ continue; }

		if (typeid(*stages[i]).name() == typeid(Block).name())
		{
			result = 0;
			//check if player collides with the blocks
			if ((stages[i])->Collision(&player, &result, sizeBlocks, sizePlayer))
			{
				if (result == 3)
				{
					//bottom
					player.position.y = player.prevPosition.y;
					player.velocity.y = 0;
					player.state = FALL;
				}
				else if (result == 2)
				{
					//side 
					player.velocity.x = 0;
					player.position.x = player.prevPosition.x;	
				}
				else if ((player.state == FALL) && (result == 1))
				{
					//topdown
					player.position.y = player.prevPosition.y;
					player.velocity.y = 0;
					player.state = GROUND;
					player.onBlock = true;
				}
				Coll = true;
			}
		}
	}
	if (!Coll) { player.onBlock = false; }
	if (!player.onBlock && player.state == GROUND) { player.state = FALL; }

	/* Enemy Block Collision Detection*/
	Coll = false;
	for (int j = 0; j < enemies.size(); j++)
	{
		//check position
		if (!((enemies[j].position.x >= cameraPos.x - 100 && enemies[j].position.x <= cameraPos.x + dims.width + 100) &&
			(enemies[j].position.y >= cameraPos.y - 100 && enemies[j].position.y <= cameraPos.y + dims.height + 100)))
			{ continue; }

		for (int i = 0; i < stages.size(); i++)
		{
			//check position 
			if (!(stages[i]->position.x >= enemies[j].position.x - sizeBlocks.x  && stages[i]->position.x <= enemies[j].position.x + sizeEnemies.x + sizeBlocks.x &&
				  stages[i]->position.y >= enemies[j].position.y - sizeBlocks.y  && stages[i]->position.y <= enemies[j].position.y + sizeEnemies.y + sizeBlocks.y ))
				  { continue; }
		
			if (typeid(*stages[i]).name() == typeid(Block).name())
			{
				result = 0;
				//check if enemy collides with the blocks
				if ((stages[i])->Collision(&enemies[j], &result, sizeBlocks, sizeEnemies))
				{
					if (result == 3)
					{
						//bottom
						enemies[j].position.y = enemies[j].prevPosition.y;
						enemies[j].velocity.y = 0;
						enemies[j].state = FALL;
					}
					else if (result == 2)
					{
						//side 
						enemies[j].velocity.x = 0;
						enemies[j].position.x = enemies[j].prevPosition.x;		//shaking needs fixing
					}
					else if ((enemies[j].state == FALL) && (result == 1))
					{
						//topdown
						enemies[j].position.y = enemies[j].prevPosition.y;
						enemies[j].velocity.y = 0;
						enemies[j].state = GROUND;
						enemies[j].onBlock = true;
					}
					Coll = true;
				}
			}
		}
		if (!Coll) { enemies[j].onBlock = false; }
		if (!enemies[j].onBlock && enemies[j].state == GROUND) { enemies[j].state = FALL; }
	}
}

void Model::platformCollision (sf::Vector2f& cameraPos)
{
	int result = 0;
	bool Coll = false;

	/* player platform collision */
	if (!player.onBlock && (player.state != JUMP))
	{
		for (int i = 0; i < stages.size(); i++)
		{
			//check position 
			if (!(stages[i]->position.x >= player.position.x - sizeBlocks.x  && stages[i]->position.x <= player.position.x + sizePlayer.x + sizeBlocks.x &&
				stages[i]->position.y >= player.position.y - sizeBlocks.y  && stages[i]->position.y <= player.position.y + sizePlayer.y + sizeBlocks.y))
				{ continue; }

				if (typeid(*stages[i]).name() == typeid(Platform).name())
				{
					if (stages[i]->Collision(&player, &result, sizePlatforms, sizePlayer))
					{
						player.position.y = stages[i]->position.y - sizePlayer.y;
						player.state = GROUND;
						player.velocity.y = 0;
						Coll = true;
					}
				}
				if (Coll) { break; } //We are colliding with one platform a frame so no need to check the rest
			}
		if (!Coll && player.state == GROUND) { player.state = FALL; }
	}

	Coll = false;

	/* enemy platform collision */
	for (int j = 0; j < enemies.size(); j++)
	{
		//check position
		if (!((enemies[j].position.x >= cameraPos.x - 100 && enemies[j].position.x <= cameraPos.x + dims.width + 100) &&
			(enemies[j].position.y >= cameraPos.y - 100 && enemies[j].position.y <= cameraPos.y + dims.height)))
			{ continue; }

		if (!enemies[j].onBlock && (enemies[j].state != JUMP))
		{
			for (int i = 0; i < stages.size(); i++)
			{
				//check position 
				if (!(stages[i]->position.x >= enemies[j].position.x - sizeBlocks.x  && stages[i]->position.x <= enemies[j].position.x + sizeEnemies.x + sizeBlocks.x &&
					stages[i]->position.y >= enemies[j].position.y - sizeBlocks.y && stages[i]->position.y <= enemies[j].position.y + sizeEnemies.y + sizeBlocks.y))
					{ continue; }

					if (typeid(*stages[i]).name() == typeid(Platform).name())
					{
						if (stages[i]->Collision(&enemies[j], &result, sizePlatforms, sizeEnemies))
						{
							enemies[j].position.y = stages[i]->position.y - sizeEnemies.y;
							enemies[j].state = GROUND;
							enemies[j].velocity.y = 0;
							Coll = true;
							break;
						}
					}
				}
			
			if (!Coll && enemies[j].state == GROUND) { enemies[j].state = FALL; }
		}
	}
}

//CHANGE THESE STUFF SUCH THAT IT WILL IT CHECKS THE POSITION OF THE THING ITS COLLIDING WITH AND NOT THE ENTIRE WINDOW
void Model::bulletCollision(float time, sf::Vector2f& cameraPos)
{
	//can use grenades explosion sound for rocket launcher since both have the same explosion sound
	bool Coll = false;

	/* player bullets platforms , enemies collision  */
	for (int i = 0; i < player.mainWeapon->bullets.size(); i++)
	{
		//bullet out of bounds check
		if (player.mainWeapon->bullets[i]->outOfBounds()) 
		{ 
			player.mainWeapon->bullets.erase(player.mainWeapon->bullets.begin() + i); 
			i--;  
			continue;
		}

		/* player bullets and blocks*/
		for (int j = 0; j < stages.size(); j++)
		{
			//check position
			if (!((stages[j]->position.x >= player.mainWeapon->bullets[i]->position.x - sizeBlocks.x && stages[j]->position.x <= player.mainWeapon->bullets[i]->position.x + sizeBullets.x + sizeBlocks.x) &&
				(stages[j]->position.y >= player.mainWeapon->bullets[i]->position.y - sizeBlocks.y && stages[j]->position.y <= player.mainWeapon->bullets[i]->position.y + sizeBullets.y + sizeBlocks.y)))
				{ continue; }

			if (typeid(*stages[j]).name() == typeid(Block).name())
			{
				if (player.mainWeapon->bullets[i]->Collision(stages[j], sizeBullets, sizeBlocks, gameSize.x))
				{
					Coll = true;
					//create a new explosion check also for grenade
					RocketLauncher* launcher = dynamic_cast<RocketLauncher*>(player.mainWeapon);
					if (launcher)
					{
						explosions.push_back(new Explosion(player.mainWeapon->bullets[i]->position.x, player.mainWeapon->bullets[i]->position.y - 30));

						//play explosion sound
						sound.setBuffer(ExplosionSound);
						sound.play();
					}

					player.mainWeapon->bullets.erase(player.mainWeapon->bullets.begin() + i);
					break;
				}
			}
		}
		if (Coll) { continue; }
	
		/* player bullets with enemy */
		for (int k = 0; k < enemies.size(); k++)
		{
			//CHECK POSITION FIX
			//check position
			if (abs(enemies[k].position.x - player.mainWeapon->bullets[i]->position.x) > sizeEnemies.x &&
			    abs(enemies[k].position.y - player.mainWeapon->bullets[i]->position.y) > sizeEnemies.y)
				{ continue; }

			if (player.mainWeapon->bullets[i]->Collision(&enemies[k], sizeBullets, sizeEnemies, gameSize.x))
			{
				// adjust health erase bullet check health and set health bar 
				RocketLauncher* launcher = dynamic_cast<RocketLauncher*>(player.mainWeapon);

				if (launcher)
				{
					explosions.push_back(new Explosion(player.mainWeapon->bullets[i]->position.x, player.mainWeapon->bullets[i]->position.y - 30));
					//play explosion sound
					sound.setBuffer(ExplosionSound);
					sound.play();

					//rangeCheck here
					Rocket* rock = dynamic_cast<Rocket*>(launcher->bullets[i]);
					if (rock)
					{
						for (int m = 0; m < enemies.size(); m++)
						{
							//start a for loop and check 
							if (rock->CollisionRange(&enemies[m], sizeBullets, sizeEnemies, gameSize.x))
							{
								enemies[m].health -= player.mainWeapon->damage;
								if (enemies[m].health <= 0)
								{
									//kill enemy
									enemyDies(enemies[m].drop, enemies[m].position);
									enemies.erase(enemies.begin() + m);
									m--;
									continue;
								}
								//set health bar
								enemies[m].healthBar.setTextureRect(sf::IntRect(0, 0, ((sizeEnemHealthBar.x * enemies[m].health) / enemies[m].maxHealth), sizeEnemHealthBar.y));
							}
						}
						//delete bullet
						player.mainWeapon->bullets.erase(player.mainWeapon->bullets.begin() + i);
						break;
					}
				}
				else
				{
					enemies[k].health -= player.mainWeapon->damage;

					//check health
					if (enemies[k].health <= 0)
					{
						//kill enemy
						enemyDies(enemies[k].drop, enemies[k].position);
						enemies.erase(enemies.begin() + k);
						player.mainWeapon->bullets.erase(player.mainWeapon->bullets.begin() + i);
						break;
					}
					if (enemies[k].health > enemies[k].maxHealth) { enemies[k].health = enemies[k].maxHealth; }
					enemies[k].healthBar.setTextureRect(sf::IntRect(0, 0, ((sizeEnemHealthBar.x * enemies[k].health) / enemies[k].maxHealth), sizeEnemHealthBar.y)); //set health bar
					player.mainWeapon->bullets.erase(player.mainWeapon->bullets.begin() + i);
					break;
				}
			}
		}
	}

	
	/* player grenades and platforms */
	for (int i = 0; i < player.grenades.size(); i++)
	{
		bool Coll = false;
		if (player.grenades[i].outOfBounds()) { player.grenades.erase(player.grenades.begin() + i); continue; }

		for (int j = 0; j < stages.size(); j++)
		{
			//check position
			if (!((stages[j]->position.x >= player.grenades[i].position.x - sizeBlocks.x && stages[j]->position.x <= player.grenades[i].position.x + sizeGrenade.x + sizeBlocks.x) &&
				(stages[j]->position.y >= player.grenades[i].position.y - sizeBlocks.y && stages[j]->position.y <= player.grenades[i].position.y + sizeGrenade.y + sizeBlocks.y)))
				{ continue; }

			//hits a block
			if (player.grenades[i].Collision(stages[j], sizeGrenade, sizeBlocks, gameSize.x))
			{
				//and create explosion
				explosions.push_back(new Explosion(player.grenades[i].position.x, player.grenades[i].position.y - 30));
				//play explosion sound
				sound.setBuffer(ExplosionSound);
				sound.play();
				player.grenades.erase(player.grenades.begin() + i);
				Coll = true;
				break;
			}
		}
		if (Coll) { continue; }
		
		/* player grenades and enemies */
		for (int k = 0; k < enemies.size(); k++)
		{
			//CHECK POSITION FIX
			//check position
			//check position
			if (abs(enemies[k].position.x - player.grenades[i].position.x) > sizeEnemies.x &&
				abs(enemies[k].position.y - player.grenades[i].position.y) > sizeEnemies.y)
				{ continue; }

			if (player.grenades[i].Collision(&enemies[k], sizeGrenade, sizeEnemies, gameSize.x))
			{
				explosions.push_back(new Explosion(player.grenades[i].position.x, player.grenades[i].position.y - 30));
				//play explosion sound
				sound.setBuffer(ExplosionSound);
				sound.play();

				//range collision second for loop on enemies
				for (int m = 0; m < enemies.size(); m++)
				{
					//start a for loop and check 
					if (player.grenades[i].CollisionRange(&enemies[m], sizeGrenade, sizeEnemies, gameSize.x))
					{
						enemies[m].health -= player.grenades[i].damage;

						if (enemies[m].health <= 0)
						{
							//kill enemy
							enemyDies(enemies[m].drop, enemies[m].position);
							enemies.erase(enemies.begin() + m);
							m--;
							continue;
						}
						//set health bar
						enemies[m].healthBar.setTextureRect(sf::IntRect(0, 0, ((sizeEnemHealthBar.x * enemies[m].health) / enemies[m].maxHealth), sizeEnemHealthBar.y));
					}
				}
				//delete grenade
				player.grenades.erase(player.grenades.begin() + i);
				break;
			}
		}
	}

	/* enemy bullets and platforms */
	for (int k = 0; k < enemies.size(); k++)
	{
		//check position
		if (!((enemies[k].position.x >= cameraPos.x - 100 && enemies[k].position.x <= cameraPos.x + dims.width + 100) &&
			(enemies[k].position.y >= cameraPos.y - 100 && enemies[k].position.y <= cameraPos.y + dims.height + 100)))
			{ continue; }

		for (int i = 0; i < enemies[k].bullets.size(); i++)
		{
			Coll = false;
			//bullet out of bounds check
			if (enemies[k].bullets[i]->outOfBounds()) { enemies[k].bullets.erase(enemies[k].bullets.begin() + i); continue; }

			//block collision with enemy bullets check their position before actually collision detecting
			for (int j = 0; j < stages.size(); j++)
			{
				//check position
				if (!((stages[j]->position.x >= enemies[k].bullets[i]->position.x - sizeBlocks.x && stages[j]->position.x <= enemies[k].bullets[i]->position.x + sizeBullets.x + sizeBlocks.x) &&
					(stages[j]->position.y >= enemies[k].bullets[i]->position.y - sizeBlocks.y && stages[j]->position.y <= enemies[k].bullets[i]->position.y + sizeGrenade.y + sizeBlocks.y)))
					{ continue; }

				if (typeid(*stages[j]).name() == typeid(Block).name())
				{
					if (enemies[k].bullets[i]->Collision(stages[j], sizeEnemyBullets, sizeBlocks, gameSize.x))
					{
						Coll = true;
						enemies[k].bullets.erase(enemies[k].bullets.begin() + i);
						break;
					}
				}
			}
			if (Coll) { continue; }	//if bullet collides go to next bullet

			/* enemy bullets with player */
			if (enemies[k].bullets[i]->Collision(&player, sizeEnemyBullets, sizePlayer, gameSize.x))
			{

				// adjust health erase bullet check health and set health bar 
				player.health -= enemies[k].damage;	   //inflict enemy's damage on player
				//GAME OVERRRRRR
				if (player.health <= 0) 
				{ 
					gameState = 2;
					// do stuff
				} 		

				if (player.health > player.maxHealth) { player.health = player.maxHealth; }
				player.healthBar.setTextureRect(sf::IntRect(0, 0, ((sizeHealthBar.x * player.health) / player.maxHealth), sizeHealthBar.y)); //set health bar
				enemies[k].bullets.erase(enemies[k].bullets.begin() + i);
			}
			else { enemies[k].bullets[i]->update(1, 1, time, sf::Vector2f(0, 0), sf::Vector2u(0, 0)); }
		}
	}


	/* friendly Fire between enemies */
	bool coll = false;
	for (int i = 0; i < enemies.size(); i++)
	{
		//check position
		
		if (!((enemies[i].position.x >= cameraPos.x - 100 && enemies[i].position.x <= cameraPos.x + dims.width + 100) &&
			(enemies[i].position.y >= cameraPos.y - 100 && enemies[i].position.y <= cameraPos.y + dims.height + 100)))
			{ continue; }

		for (int j = 0; j < enemies.size(); j++)
		{
			//check if i am myself
			if (i == j) { continue; }

			//check position
			if (!((enemies[j].position.x >= cameraPos.x - 100 && enemies[j].position.x <= cameraPos.x + dims.width + 100) &&
				(enemies[j].position.y >= cameraPos.y - 100 && enemies[j].position.y <= cameraPos.y + dims.height + 100)))
			    { continue; }

			for (int k = 0; k < enemies[i].bullets.size(); k++)
			{
				/* enemy bullets with enemy */
				if (enemies[i].bullets[k]->Collision(&enemies[j], sizeEnemyBullets, sizeEnemies, gameSize.x))
				{
					enemies[i].bullets.erase(enemies[i].bullets.begin() + k);
					enemies[j].health -= enemies[i].damage;
					if (enemies[j].health <= 0)
					{
						enemyDies(enemies[j].drop, enemies[j].position);
						enemies.erase(enemies.begin() + j);
						coll = true;
						break;
						// do stuff
					}
					//set health bar
					enemies[j].healthBar.setTextureRect(sf::IntRect(0, 0, ((sizeEnemHealthBar.x * enemies[j].health) / enemies[j].maxHealth), sizeEnemHealthBar.y));
				}
			}
			if (coll) { break; }
		}
	}

	/* update bullets*/
	for (int i = 0; i < player.mainWeapon->bullets.size(); i++)
	{
		player.mainWeapon->bullets[i]->update(1,1,time,sf::Vector2f(0,0) , sf::Vector2u(0,0));
	}
	/* update grenades */
	for (int i = 0; i < player.grenades.size(); i++)
	{
		player.grenades[i].update(1, 1, time, sf::Vector2f(0, 0), sf::Vector2u(0, 0));
	}
	/* check explosions */
	for (int i = 0; i < explosions.size(); i++)
	{
		if (explosions[i]->animFrame == 15) { explosions.erase(explosions.begin() + i); }
		else { explosions[i]->update(time); }
	}
}

void Model::restart()
{
	//create a new player
	player = Player();

	//clear the vectors
	//player.inventory.materials.clear();
	enemies.clear();
	explosions.clear();
	materials.clear();

	//restart the player information
	/*
	player.position = sf::Vector2f(500, 200);
	player.health = player.maxHealth;

	player.mainWeapon = new Gun(&GunShotSound);
	player.secondaryWeapon = NULL;
	player.grenNum = 4;

	player.state = FALL;
	player.InventoryOpen = false;
	*/
	craftOpen = false;

	//restart the enemies information
	std::ifstream enemyHndl;
	enemyHndl.open("assets/enemyData.txt");
	//create variable for to store the size
	int numOfEnemies;
	int enemyTempx;
	int enemyTempy;

	enemyHndl >> numOfEnemies;
	for (int i = 0; i < numOfEnemies; i++)
	{
		enemyHndl >> enemyTempx;
		enemyHndl >> enemyTempy;
		Enemy tempEnemy = Enemy(sf::Vector2f(enemyTempx * 48, enemyTempy * 48));
		enemies.push_back(tempEnemy);
	}
}