#pragma once

#include <SFML/Graphics.hpp>
#include "model.h"
#include "view.h"
#include <string>

class Controller
{
public:
	Controller(Model*, View*);
	~Controller();
	void inputs(float);

	Model* model;
	View* view;

private:
	void buttonClick(int);
	void crafting(std::string);
	void getWeaponImage(Weapon*);
	void changeWeapon(int);
	void upgradeWeapon(Weapon*);
};