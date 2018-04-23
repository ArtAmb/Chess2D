#pragma once
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "Game.h"

class OptionsView : public LayoutView
{
	sf::RenderWindow* mainWindow;
	ResourceManager* resourceManager = ResourceManager::getInstance();
	LayoutView* view;
	Game* game;
	

public:
	OptionsView(int height, int width, sf::Sprite* background) : LayoutView(width, height, background) {};
	~OptionsView();

	void additionalDisplayAction(sf::RenderWindow * window);
	

};