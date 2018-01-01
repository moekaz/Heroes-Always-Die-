#include "View.h"

View::View(Model* m)
{
	model = m;
	window.create(model->dims, "Heroes Always Die");
	fps = 60;

	//background pic
	Bak.setTexture(manager.get_texture("assets/bak.png", sf::Color::White));
	Bak.setPosition(0, 0);

	/* load textures and set them to the sprites */

	//loading menu and ending screen
	menuScreen.setTexture(manager.get_texture("assets/MENU.png"));
	menuScreen.setPosition(0, 0);
	endingScreen.setTexture(manager.get_texture("assets/GAMEOVER.png"));
	endingScreen.setPosition(0, 0);

	//load font and set HUD
	if (!font.loadFromFile("assets/arial.ttf")) { std::cout << "Couldn't load font" << std::endl; }
	HUD.setFont(font);
	HUD.setCharacterSize(20);
	HUD.setFillColor(sf::Color::Green);

	//enemyHealthBar
	model->sizeEnemHealthBar = manager.get_texture("assets/EnemHealth.png", sf::Color::White).getSize();

	//playerHelathBar
	model->sizeHealthBar = manager.get_texture("assets/HealthBar.png", sf::Color::White).getSize();
	model->player.healthBar.setTexture(manager.get_texture("assets/HealthBar.png", sf::Color::White));

	//playerSpriteSheet
	model->sizePlayer.x = manager.get_texture("assets/Hat_man5.png", sf::Color(250, 250, 250)).getSize().x / 4;
	model->sizePlayer.y = manager.get_texture("assets/Hat_man5.png", sf::Color(250, 250, 250)).getSize().y;
	model->player.sprite.setTexture(manager.get_texture("assets/Hat_man5.png", sf::Color(250, 250, 250)), true);
	model->player.sprite.setTextureRect(sf::IntRect(0, 0, 62, 88));

	//blocks
	model->sizeBlocks.x = (manager.get_texture("assets/plates.png", sf::Color::White).getSize().x - 2) / 3;
	model->sizeBlocks.y = (manager.get_texture("assets/plates.png", sf::Color::White).getSize().y - 1) / 2;

	//platforms
	model->sizePlatforms.x = (manager.get_texture("assets/plates.png").getSize().x - 2) / 3;
	model->sizePlatforms.y = (manager.get_texture("assets/plates.png").getSize().x - 1) / 5;

	//enemies
	model->sizeEnemies = manager.get_texture("assets/enemy01.png", sf::Color::White).getSize();

	//mainWeapon
	model->sizeWeapon = manager.get_texture("assets/gun01.png", sf::Color::White).getSize();

	//inventory
	model->player.inventory.spriteSheet = manager.get_texture("assets/item_slot.png", sf::Color::White);
	model->player.inventory.vertex_height = 56;
	model->player.inventory.vertex_width = 56;

	//Grendes
	model->sizeGrenade = manager.get_texture("assets/grenade.png", sf::Color::White).getSize();

	//enemyBullets
	model->sizeEnemyBullets = manager.get_texture("assets/bulletEnemy.png", sf::Color::Black).getSize();

	//Boss
	model->sizeBoss = manager.get_texture("assets/BOSS01.png", sf::Color(250, 250, 250)).getSize();
	model->boss.boss_range = 138 * 48;
	model->boss.boss_range_end = 168 * 48 - model->sizeBoss.x;

	//loading the inventory textures
	model->player.inventory.spriteSheet = manager.get_texture("assets/item_slot.png", sf::Color::White);
	model->player.inventory.vertex_height = 56;
	model->player.inventory.vertex_width = 56;
	model->player.inventory.title.setTexture(manager.get_texture("assets/inventory.png", sf::Color::White));
	model->player.inventory.throwing.setTexture(manager.get_texture("assets/throwing.png", sf::Color::White));

	//loading textures for the craftable sprite array
	model->craftable.title.setTexture(manager.get_texture("assets/crafting.png", sf::Color::White), true);
	model->craftable.title.setPosition(0, 0);
	//loading texture for the crafting slot
	model->craftable.slot.setTexture(manager.get_texture("assets/craft_slot.png", sf::Color::White));

	model->sizeMaterial = manager.get_texture("assets/material1.png", sf::Color::White).getSize();

	sf::Sprite tempSprite;
	//loading guns 
	tempSprite.setTexture(manager.get_texture("assets/gun07.png", sf::Color::White), true);
	model->craftable.weapon_list.insert(std::pair<std::string, sf::Sprite>("HealingStaff", tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/gun05.png", sf::Color::White), true);
	model->craftable.weapon_list.insert(std::pair<std::string, sf::Sprite>("Sniper", tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/gun01.png", sf::Color::White), true);
	model->craftable.weapon_list.insert(std::pair<std::string, sf::Sprite>("Gun", tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/gun03.png", sf::Color::White), true);
	model->craftable.weapon_list.insert(std::pair<std::string, sf::Sprite>("RocketLauncher", tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/grenade.png", sf::Color::White), true);
	model->craftable.weapon_list.insert(std::pair<std::string, sf::Sprite>("Grenade", tempSprite));

	//loading material
	tempSprite.setScale(0.5f, 0.5f);
	tempSprite.setTexture(manager.get_texture("assets/material1.png", sf::Color::White), true);
	model->craftable.material_list.insert(std::pair<int, sf::Sprite>(1, tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/material2.png", sf::Color::White), true);
	model->craftable.material_list.insert(std::pair<int, sf::Sprite>(2, tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/material3.png", sf::Color::White), true);
	model->craftable.material_list.insert(std::pair<int, sf::Sprite>(3, tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/material4.png", sf::Color::White), true);
	model->craftable.material_list.insert(std::pair<int, sf::Sprite>(4, tempSprite));
	tempSprite.setTexture(manager.get_texture("assets/material5.png", sf::Color::White), true);
	model->craftable.material_list.insert(std::pair<int, sf::Sprite>(5, tempSprite));

	//load sounds
	if (!model->DropSound.loadFromFile("assets/DropSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->CraftedSound.loadFromFile("assets/CraftedSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->CraftingSound.loadFromFile("assets/CraftingSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->InventorySound.loadFromFile("assets/InventorySound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->ItemSound.loadFromFile("assets/ItemSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->HealingSound.loadFromFile("assets/HealingSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->LauncherSound.loadFromFile("assets/GrenadeLauncher.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->SniperSound.loadFromFile("assets/SniperSound.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->GunShotSound.loadFromFile("assets/laserSound2.wav")) { std::cout << "couldn't load sound file" << std::endl; }
	if (!model->ExplosionSound.loadFromFile("assets/Explosion.wav")) { std::cout << "Couldn't load sound file" << std::endl; }
	if (!model->gameMusic.openFromFile("assets/GameBak.wav")) { std::cout << "couldn't load game music" << std::endl; }
	model->gameMusic.setLoop(true);
	model->gameMusic.play();


	//create world and its platforms 
	std::cout << this->model->stages.size() << std::endl;
	for (int i = 0; i < this->model->stages.size(); i++)
	{
		if (typeid(*this->model->stages[i]).name() == typeid(Platform).name())
		{
			this->model->stages[i]->sprite.setTexture(manager.get_texture("assets/plates.png"), true);
			this->model->stages[i]->sprite.setTextureRect(sf::IntRect(48, 0, 48, 48));
		}
		else if (typeid(*this->model->stages[i]).name() == typeid(Block).name())
		{
			this->model->stages[i]->sprite.setTexture(manager.get_texture("assets/plates.png"), true);
			this->model->stages[i]->sprite.setTextureRect(sf::IntRect(0, 0, 48, 48));
		}
		this->model->stages[i]->sprite.setPosition(this->model->stages[i]->position.x, this->model->stages[i]->position.y);
	}

	//setFrameRate
	window.setFramerateLimit(fps);
}

View::~View()
{}

void View::render()
{
	window.clear();
	
	if (model->gameState == 1)
	{
		//Update Camera
		camera.updateCamera(model->player.position, model->gameSize, model->dims);

		//background
		window.draw(Bak);

		//Platforms
		for (int i = 0; i < this->model->stages.size(); i++)
		{
			//check position before rendering
			if ((model->stages[i]->position.x <= camera.position.x - model->sizeBlocks.x || model->stages[i]->position.x >= camera.position.x + model->dims.width)
				&& (model->stages[i]->position.y <= camera.position.y - model->sizeBlocks.y || model->stages[i]->position.y >= camera.position.y + model->dims.height)) {
			}
			else { this->model->stages[i]->render(window, camera); }
		}

		for (int i = 0; i < model->materials.size(); i++) { model->materials[i]->render(window, camera); }

		//Enemy
		for (int j = 0; j < model->enemies.size(); j++)
		{
			//check position
			if (!((model->enemies[j].position.x >= camera.position.x - 100 && model->enemies[j].position.x <= camera.position.x + model->dims.width + 100) &&
				(model->enemies[j].position.y >= camera.position.y - 100 && model->enemies[j].position.y <= camera.position.y + model->dims.height + 100)))
			{
				continue;
			}

			//health bar
			model->enemies[j].healthBar.setTexture(manager.get_texture("assets/EnemHealth.png", sf::Color::White));
			//enemy text MIGHT NEED WORK
			if (model->enemies[j].direction == 1) { model->enemies[j].sprite.setTexture(manager.get_texture("assets/enemy02.png", sf::Color::White)); }
			else { model->enemies[j].sprite.setTexture(manager.get_texture("assets/enemy01.png", sf::Color::White)); }

			//ENEMYBULLETS TEXT MIGHT NEED WORK
			for (int i = 0; i < model->enemies[j].bullets.size(); i++)
			{
				model->enemies[j].bullets[i]->sprite.setTexture(manager.get_texture("assets/bulletEnemy.png", sf::Color::Black));
			}

			//draw enemy
			model->enemies[j].render(window, camera);
		}

		//Boss
		if (model->boss.direction == 1) { model->boss.sprite.setTexture(manager.get_texture("assets/BOSS02.png", sf::Color(250, 250, 250))); }
		else { model->boss.sprite.setTexture(manager.get_texture("assets/BOSS01.png", sf::Color(250, 250, 250))); }
		model->boss.render(window, camera);

		//Player
		model->player.render(window, camera);

		//HUD
		HUD.setPosition(25, 60);
		HUD.setString("Bullets: " + std::to_string(model->player.mainWeapon->numBullets));
		window.draw(HUD);
		HUD.setPosition(25, 90);
		HUD.setString("Grenades: " + std::to_string(model->player.grenNum));
		window.draw(HUD);
		HUD.setPosition(25, 120);
		HUD.setString("Enemies: " + std::to_string(model->enemies.size()));
		window.draw(HUD);

		//Explosions MIGHT NEED WORK
		for (int i = 0; i < model->explosions.size(); i++)
		{
			//set explosion textures
			model->explosions[i]->sprite.setTexture(manager.get_texture("assets/explosion.png", sf::Color::White));
			model->explosions[i]->render(window, camera);
		}

		//Inventory
		if (model->player.InventoryOpen) { model->player.inventory.render(window); }

		//Crafting menu
		if (model->craftOpen)
		{
			if (model->player.position.y - camera.position.y + model->craftable.height < 30)
				model->craftable.height = camera.position.y - model->player.position.y + 30;
			else if (model->player.position.y - camera.position.y + model->craftable.height + (model->craftable.craft_position.size() * 85) > model->dims.height - 10)
				model->craftable.height = camera.position.y - model->player.position.y - (model->craftable.craft_position.size() * 85) + model->dims.height - 10;
			model->craftable.render(window, sf::Vector2f(model->player.position.x - camera.position.x, model->player.position.y - camera.position.y));
		}
	}
	//render menu 
	else if (model->gameState == 0)
	{
		window.draw(menuScreen);
	}
	//render endgame
	else if (model->gameState == 2)
	{
		window.draw(endingScreen);
	}
	window.display();
}
