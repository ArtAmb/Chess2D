#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ResourceManager.h"
#include "LayoutView.h"
#include "ResourceKeys.h"
#include "CreditsView.h"

class CreditsButtonAction : public ButtonAction
{
	CreditsView* view = nullptr;
	ResourceManager* resourceManager = ResourceManager::getInstance();
public:
	CreditsButtonAction();
	
	~CreditsButtonAction();
	void doAction(ClickEvent* event);
	
};

