#include "Game.h"

Game::Game()
{
	//initialize model view and controller!!!
	model = new Model();
	view = new View(model);
	controller = new Controller(model, view);

	//set the gameState to the menu screen first
	model->gameState = 0;
}

Game::~Game(){}

void Game::loop()
{
	while (view->window.isOpen())
	{
		deltaTime = clock.restart().asMilliseconds();
		
		controller->inputs(deltaTime);
		if (model->gameState == 1) { model->update(deltaTime / 10, view->camera.position); }
		view->render();
	}
}

