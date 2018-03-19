#pragma once
#include "MenuButton.h"
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

class GameButtonAction : public ButtonAction
{
	LayoutView* view = nullptr;
	ResourceManager* resourceManager = ResourceManager::getInstance();
public:
	GameButtonAction();
	~GameButtonAction();

	void doAction(ClickEvent* event);
};

