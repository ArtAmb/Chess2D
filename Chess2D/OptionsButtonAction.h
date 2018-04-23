#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ResourceManager.h"
#include "LayoutView.h"
#include "ResourceKeys.h"
#include "OptionsView.h"
#include "Game.h"
#include "GameSettings.h"

class OptionsButtonAction : public ButtonAction
{
	LayoutView* view = nullptr;
	ResourceManager* resourceManager = ResourceManager::getInstance();
	Game* game;
	GameSettings* gameSettings;
	
public:
	
	//OptionsButtonAction(COLOR_OPTION color, LEVEL_OPTION level);
	OptionsButtonAction();
	~OptionsButtonAction();

	void doAction(ClickEvent* event);
};

