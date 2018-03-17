#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "MenuButton.h"
#include "LayoutView.h"
#include "Game.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

#define WIDTH_BACKGROUND 836
#define HEIGHT_BACKGROUND 728

#define WIDTH_BUTTON 296
#define HEIGHT_BUTTON 50

int main()
{
	ResourceManager* resourceManager = ResourceManager::getInstance();
	resourceManager->setPathToResource("resources/");

	resourceManager->loadTexture(RESOURCE::TEXTURE::BACKGROUNDS, "menu.png", WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
	resourceManager->loadTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS, "buttons.png", WIDTH_BUTTON, HEIGHT_BUTTON);
	
	GraphicEngine graphicEngine;
	Game game(graphicEngine.getMainWindow(), &graphicEngine);
	
	game.startGame();

	return 0;
}