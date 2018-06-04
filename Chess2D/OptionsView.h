#pragma once
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "Game.h"
#include "ColorOptionsButton.h"
#include "LevelOptionsButton.h"
#include "ChessEnums.h"
#include <vector>
class OptionsView : public LayoutView
{
	sf::RenderWindow* mainWindow;
	ResourceManager* resourceManager = ResourceManager::getInstance();
	LayoutView* view;
	Game* game;

	LEVEL_OPTION level = Game::getGameSettings()->getLevel();
	COLOR_OPTION color = Game::getGameSettings()->getColor();
	
	std::vector<ColorOptionsButton* > colorButtons;
	std::vector<LevelOptionsButton* > levelButtons;
	
public:
	OptionsView(int height, int width, sf::Sprite* background) : LayoutView(width, height, background) {};
	~OptionsView();

	void additionalDisplayAction(sf::RenderWindow * window);
	void setColor(COLOR_OPTION color) { this->color = color; }
	void setLevel(LEVEL_OPTION level) { this->level = level; }
	
	void addColorButton(ColorOptionsButton* button) {
		colorButtons.push_back(button);
	}
	void addLevelButton(LevelOptionsButton* button) {
		levelButtons.push_back(button);
	}
};