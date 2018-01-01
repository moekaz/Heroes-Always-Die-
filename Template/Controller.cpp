#include "controller.h"

Controller::Controller(Model* m, View* v)
{
	model = m;
	view = v;
}

Controller:: ~Controller() {}

void Controller::inputs(float deltaTime)
{
	sf::Event event;

	while (view->window.pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			view->window.close();
		}
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//Menu to game
				if (model->gameState == 0)
				{
					model->gameState = 1;
					model->restart();
					//create gun sound
					model->player.mainWeapon = new Gun(&model->GunShotSound);
					model->player.mainWeapon->sprite.setTexture(view->manager.get_texture("assets/gun01.png", sf::Color::White));
					model->player.healthBar.setTexture(view->manager.get_texture("assets/HealthBar.png", sf::Color::White));
					model->player.sprite.setTexture(view->manager.get_texture("assets/Hat_man5.png", sf::Color(250, 250, 250)), true);
					model->player.sprite.setTextureRect(sf::IntRect(0, 0, 62, 88));
					//inventory
					model->player.inventory.spriteSheet = view->manager.get_texture("assets/item_slot.png", sf::Color::White);
					model->player.inventory.vertex_height = 56;
					model->player.inventory.vertex_width = 56;
					//loading the inventory textures
					model->player.inventory.spriteSheet = view->manager.get_texture("assets/item_slot.png", sf::Color::White);
					model->player.inventory.vertex_height = 56;
					model->player.inventory.vertex_width = 56;
					model->player.inventory.title.setTexture(view->manager.get_texture("assets/inventory.png", sf::Color::White));
					model->player.inventory.throwing.setTexture(view->manager.get_texture("assets/throwing.png", sf::Color::White));
				}
				//End game to menu
				else if (model->gameState == 2)
				{
					model->gameState = 0;
				}
			}
		}
		else if (event.type == sf::Event::KeyReleased)
		{

			if (model->gameState == 1)
			{
				if (event.key.code == sf::Keyboard::R)
				{
					if (model->player.secondaryWeapon == 0) { break; }
					//change weapon
					model->player.mainWeapon->bullets.clear();			//empty the bullets
					Weapon *temp = model->player.mainWeapon;
					model->player.mainWeapon = model->player.secondaryWeapon;
					model->player.secondaryWeapon = temp;
					model->sound.setBuffer(model->DropSound);
					model->sound.play();

					if (model->player.direction == 1)
					{
						model->sizeWeapon = view->manager.get_texture(model->player.mainWeapon->textDirRight, sf::Color::White).getSize();
						model->player.mainWeapon->sprite.setTexture(view->manager.get_texture(model->player.mainWeapon->textDirRight, sf::Color::White));
					}
					else
					{
						model->sizeWeapon = view->manager.get_texture(model->player.mainWeapon->textDirLeft, sf::Color::White).getSize();
						model->player.mainWeapon->sprite.setTexture(view->manager.get_texture(model->player.mainWeapon->textDirLeft, sf::Color::White));
					}
				}
				else if (event.key.code == sf::Keyboard::G)
				{
					//throw grenade
					if (model->player.grenNum > 0)
					{
						model->player.grenades.push_back(Grenade(model->player.position.x, model->player.position.y, model->player.direction));
						model->player.grenades[model->player.grenades.size() - 1].sprite.setTexture
						(view->manager.get_texture("assets/grenade.png", sf::Color::White));
						//throw grenade
						model->player.grenades[model->player.grenades.size() - 1].toss(deltaTime);
						model->player.grenNum--;
					}
				}
				else if (event.key.code == sf::Keyboard::Num0)
				{
					Material* m = new Material();
					switch (rand() % 5)
					{
					case 0:
						m->type = 1;
						m->sprite.setTexture(view->manager.get_texture("Assets/material1.png", sf::Color::White), true);
						break;
					case 1:
						m->type = 2;
						m->sprite.setTexture(view->manager.get_texture("Assets/material2.png", sf::Color::White), true);
						break;
					case 2:
						m->type = 3;
						m->sprite.setTexture(view->manager.get_texture("Assets/material3.png", sf::Color::White), true);
						break;
					case 3:
						m->type = 4;
						m->sprite.setTexture(view->manager.get_texture("Assets/material4.png", sf::Color::White), true);
						break;
					case 4:
						m->type = 5;
						m->sprite.setTexture(view->manager.get_texture("Assets/material5.png", sf::Color::White), true);
						break;
					}
					this->model->player.inventory.addItem(m);
				}
				else if (event.key.code == sf::Keyboard::Num1)
				{
					buttonClick(1);
				}
				else if (event.key.code == sf::Keyboard::Num2)
				{
					buttonClick(2);
				}
				else if (event.key.code == sf::Keyboard::Num3)
				{
					buttonClick(3);
				}
				else if (event.key.code == sf::Keyboard::Num4)
				{
					buttonClick(4);
				}
				else if (event.key.code == sf::Keyboard::Num5)
				{
					buttonClick(5);
				}
				else if (event.key.code == sf::Keyboard::Num6)
				{
					buttonClick(6);
				}
				else if (event.key.code == sf::Keyboard::Num7)
				{
					buttonClick(7);
				}
				else if (event.key.code == sf::Keyboard::Num8)
				{
					buttonClick(8);
				}
				else if (event.key.code == sf::Keyboard::Num9)
				{
					buttonClick(9);
				}
				//crafting menu open
				else if (event.key.code == sf::Keyboard::C)
				{
					if (!this->model->player.InventoryOpen && !this->model->craftOpen)
					{
						this->model->craftable.height = 0;
						this->model->craftable.setCraft(this->model->player.inventory);
						this->model->craftOpen = true;
						model->sound.setBuffer(model->CraftingSound);
						model->sound.play();
					}
					else if (this->model->craftOpen)
					{
						this->model->craftOpen = false;
						model->sound.setBuffer(model->CraftingSound);
						model->sound.play();
					}
				}
				//inventory open
				else if (event.key.code == sf::Keyboard::I)
				{
					if (!this->model->craftOpen && !this->model->player.InventoryOpen)
					{
						this->model->player.inventory.updateSize(this->model->player.inventory.width, this->model->player.inventory.height);
						this->model->player.InventoryOpen = true;
						model->sound.setBuffer(model->InventorySound);
						model->sound.play();
					}
					else if (this->model->player.InventoryOpen)
					{
						this->model->player.InventoryOpen = false;
						this->model->player.inventory.drop = false;
						model->sound.setBuffer(model->InventorySound);
						model->sound.play();
					}
				}
				//dropping open
				else if (event.key.code == sf::Keyboard::Q)
				{
					if (this->model->player.InventoryOpen && !this->model->player.inventory.drop)
						this->model->player.inventory.drop = true;
					else if (this->model->player.InventoryOpen && this->model->player.inventory.drop)
						this->model->player.inventory.drop = false;
				}
				else if (event.key.code == sf::Keyboard::Num9)
				{
					this->model->player.inventory.reduceItem(0);
				}
				else if (event.key.code == sf::Keyboard::P)
				{
					this->model->restart();
				}
			}
		}
	}

	if (model->gameState == 1)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//create bullet and add it to bullet array
			//the bullet will move in the first frame so offset it back by its size
			if (model->player.mainWeapon->type == 104 && model->player.mainWeapon->fireDelay <= 0 && model->player.mainWeapon->numBullets > 0)
			{
				model->player.mainWeapon->numBullets--;
				model->sound.setBuffer(*(model->player.mainWeapon->shotSound));
				model->sound.play();

				for (int i = 0; i < model->enemies.size(); i++)
				{
					model->enemies[i].health += model->player.mainWeapon->damage;
					if (model->enemies[i].health > model->enemies[i].maxHealth) { model->enemies[i].health = model->enemies[i].maxHealth; }
					model->enemies[i].healthBar.setTextureRect(sf::IntRect(0, 0, ((model->sizeEnemHealthBar.x * model->enemies[i].health) / model->enemies[i].maxHealth), model->sizeEnemHealthBar.y));
				}

				if (model->player.health + model->player.mainWeapon->damage > model->player.maxHealth)
				{
					model->player.health = model->player.maxHealth;
				}
				else { model->player.health += model->player.mainWeapon->damage; }

				model->player.healthBar.setTextureRect(sf::IntRect(0, 0, ((model->sizeHealthBar.x * model->player.health) / model->player.maxHealth), model->sizeHealthBar.y));

				model->player.mainWeapon->fireDelay = model->player.mainWeapon->maxDelay;
			}
			else if (model->player.mainWeapon->fireDelay <= 0)
			{
				//create bullet
				if (model->player.direction == 1)
				{
					model->player.mainWeapon->addBullet(model->player.mainWeapon->position.x + model->sizeWeapon.x - model->sizeBullets.x, model->player.mainWeapon->position.y, 1);
				}
				else { model->player.mainWeapon->addBullet(model->player.mainWeapon->position.x, model->player.mainWeapon->position.y, -1); }

				//add textures to it 
				if (model->player.mainWeapon->bullets.size() > 0)
				{
					model->sizeBullets = view->manager.get_texture(model->player.mainWeapon->bullets[model->player.mainWeapon->bullets.size() - 1]->textDir, sf::Color(0, 0, 0)).getSize();
					model->player.mainWeapon->bullets[model->player.mainWeapon->bullets.size() - 1]->sprite.setTexture
					(view->manager.get_texture(model->player.mainWeapon->bullets[model->player.mainWeapon->bullets.size() - 1]->textDir, sf::Color::Black));

					//reset weapon delay
					model->player.mainWeapon->fireDelay = model->player.mainWeapon->maxDelay;    //reset fireDelay
					model->sound.setBuffer(*(model->player.mainWeapon->shotSound));
					model->sound.play();
				}
			}
		}
		//take inputs 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			//JUMP!!!
			model->player.jump(model->dims.width, model->dims.height, deltaTime / 10);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			//change weapon texture
			model->player.mainWeapon->sprite.setTexture(view->manager.get_texture(model->player.mainWeapon->textDirLeft, sf::Color::White));
			model->player.sprite.setTexture(view->manager.get_texture("assets/Hat_man6.png", sf::Color(250, 250, 250)));
			//set velocity
			model->player.setVelocity(deltaTime / 10, -1);
			model->player.direction = -1;
			if (model->player.state == GROUND) { model->player.move = true; }
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			//change weapon texture
			model->player.mainWeapon->sprite.setTexture(view->manager.get_texture(model->player.mainWeapon->textDirRight, sf::Color::White));
			model->player.sprite.setTexture(view->manager.get_texture("assets/Hat_man5.png", sf::Color(250, 250, 250)));
			//set Velocity
			model->player.setVelocity(deltaTime / 10, 1);
			model->player.direction = 1;
			if (model->player.state == GROUND) { model->player.move = true; }
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (this->model->craftOpen)
			{
				this->model->craftable.height -= 10;
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (this->model->craftOpen)
			{
				this->model->craftable.height += 10;
			}
		}
	}
}

void Controller::crafting(std::string weapon)
{
	for (int i = 0; i < model->craftable.craft_list[weapon].size(); i++)
	{
		model->player.inventory.reduceMaterial(model->craftable.craft_list[weapon][i]);
	}


	if (weapon == "Gun")
	{
		cout << "gun " << endl;
		Gun* gun = new Gun(&model->GunShotSound);
		getWeaponImage(gun);
		model->player.inventory.addItem(gun);
	}
	else if (weapon == "RocketLauncher")
	{
		cout << "rocketLauncher" << endl;
		RocketLauncher* rl = new RocketLauncher(&model->LauncherSound);
		getWeaponImage(rl);
		model->player.inventory.addItem(rl);
	}
	else if (weapon == "Sniper")
	{
		cout << "Sniper" << endl;
		Sniper* sp = new Sniper(&model->SniperSound);
		getWeaponImage(sp);
		model->player.inventory.addItem(sp);
	}
	else if (weapon == "HealingStaff")
	{
		cout << "HealingStaff" << endl;
		HealingStaff* hs = new HealingStaff(&model->HealingSound);
		getWeaponImage(hs);
		model->player.inventory.addItem(hs);
	}
	else if (weapon == "Grenade")
	{
		cout << "Grenade" << endl;
		model->player.grenNum++;
	}
	cout << "crafted!!!" << endl;
	model->craftable.setCraft(model->player.inventory);
	model->sound.setBuffer(model->CraftedSound);
	model->sound.play();
}

void Controller::getWeaponImage(Weapon* weapon)
{
	weapon->sprite.setTexture(view->manager.get_texture(weapon->textDirRight, sf::Color::White));
	weapon->sprite.setScale(0.5f, 0.5f);

}

void Controller::buttonClick(int button)
{
	if (model->craftable.craft_position.size() >= button && this->model->craftOpen)
	{
		crafting(model->craftable.craft_position[button - 1]);
	}
	else if (model->player.inventory.materials.size() >= button && this->model->player.InventoryOpen && !this->model->player.inventory.drop)
	{
		changeWeapon(button - 1);
	}
	else if (model->player.inventory.materials.size() >= button && this->model->player.InventoryOpen && this->model->player.inventory.drop)
	{
		//if something got dropped make dropped sound
		if (this->model->player.inventory.reduceItem(button - 1))
		{
			model->sound.setBuffer(model->DropSound);
			model->sound.play();
		}
	}
}

void Controller::changeWeapon(int index)
{
	Item* item = model->player.inventory.materials[index];
	Weapon *temp = dynamic_cast<Weapon*>(item);
	if (temp)
	{
		if (temp->type == model->player.mainWeapon->type)
		{
			upgradeWeapon(model->player.mainWeapon);
			model->player.inventory.materials.erase(model->player.inventory.materials.begin() + index);
		}
		else
		{
			if (model->player.secondaryWeapon != NULL)
			{
				if (temp->type == model->player.secondaryWeapon->type)
				{
					upgradeWeapon(model->player.secondaryWeapon);
					model->player.inventory.materials.erase(model->player.inventory.materials.begin() + index);
				}
				else
				{
					model->player.inventory.materials[index] = model->player.secondaryWeapon;
					model->player.inventory.materials[index]->sprite.setScale(0.5f, 0.5f);
					model->player.secondaryWeapon = temp;
					model->player.secondaryWeapon->sprite.setScale(1.f, 1.f);
				}
			}
			else
			{
				model->player.inventory.materials.erase(model->player.inventory.materials.begin() + index);
				model->player.secondaryWeapon = temp;
				model->player.secondaryWeapon->sprite.setScale(1.f, 1.f);
			}
		}
		model->sound.setBuffer(model->DropSound);
		model->sound.play();
	}
}
 
void Controller::upgradeWeapon(Weapon* weapon)
{
	if (weapon->type == 101)
	{
		weapon->damage += 3;
		weapon->numBullets += 10;
	}
	else if (weapon->type == 102)
	{
		weapon->damage += 10;
		weapon->numBullets += 5;
	}
	else if (weapon->type == 103)
	{
		weapon->numBullets += 2;
	}
	else if (weapon->type == 104)
	{
		weapon->damage += 1;
		weapon->numBullets += 5;
	}
}