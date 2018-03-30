#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "MenuButton.h"
#include "LayoutView.h"
#include "Game.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"

#define WIDTH_BACKGROUND 1008
#define HEIGHT_BACKGROUND 720

#define WIDTH_BUTTON 296
#define HEIGHT_BUTTON 50

#define GAME_MODE_HEIGHT_BUTTON 150
#define GAME_MODE_WIDTH_BUTTON 400

#define WIDTH_FIELD 72


int main()
{
	ResourceManager* resourceManager = ResourceManager::getInstance();
	resourceManager->setPathToResource("resources/");

	resourceManager->loadTexture(RESOURCE::TEXTURE::BACKGROUNDS, "backgrounds.png", WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
	resourceManager->loadTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS, "buttons.png", WIDTH_BUTTON, HEIGHT_BUTTON);
	resourceManager->loadTexture(RESOURCE::TEXTURE::GAME_MODE_BUTTONS, "game_mode_buttons.png", GAME_MODE_WIDTH_BUTTON, GAME_MODE_HEIGHT_BUTTON);
	resourceManager->loadTexture(RESOURCE::TEXTURE::FIELDS, "fields.png", WIDTH_FIELD, WIDTH_FIELD);
	
	
	GraphicEngine graphicEngine;
	Game game(graphicEngine.getMainWindow(), &graphicEngine);
	
	game.startGame();

	return 0;
}