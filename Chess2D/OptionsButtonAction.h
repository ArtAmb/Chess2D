#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ResourceManager.h"
#include "LayoutView.h"
#include "ResourceKeys.h"
#include "Game.h"
#include "GameSettings.h"

class OptionsView;
class OptionsButtonAction : public ButtonAction
{
	LayoutView* view = nullptr;
	ResourceManager* resourceManager = ResourceManager::getInstance();
	Game* game;
	GameSettings* gameSettings;
	
public:
	
	OptionsButtonAction();
	Button * createDefaultColorButton(COLOR_OPTION color, TextureResource * texture, int logicalRow, OptionsView * view);
	Button * createDefaultLevelButton(LEVEL_OPTION level, TextureResource * texture, int logicalRow, OptionsView * view);
	~OptionsButtonAction();

	void doAction(ClickEvent* event);
};

