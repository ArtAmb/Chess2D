#pragma once
#include <SFML\Graphics.hpp>
#include "LayoutView.h"
#include "PositionTextureConverter.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"


class Game
{
	int WIDTH_BUTTON = 296;
	int HEIGHT_BUTTON = 50;
	sf::RenderWindow* mainWindow;
	LayoutView* menuView;
	ResourceManager* resourceManager = ResourceManager::getInstance();

public:
	Game(sf::RenderWindow* mainWindow, GraphicEngine* engine);
	void startGame();
	Button* createDefaultButton(TextureResource* texture, int logicalRow, LayoutView* view);
	~Game();
};

