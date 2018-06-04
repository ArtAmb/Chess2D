#pragma once
#include <SFML\Graphics.hpp>
#include "GameSettings.h"

class LayoutView;
class Button;
class ClickEvent
{
	sf::RenderWindow* window;
	//GameSettings* gameSettings;
	LayoutView* view;
	Button* button;

public:

	void setWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* getWindow() {
		return window;
	}
	
	/*void setGameSettings(GameSettings* settings) {
		this->gameSettings = settings;
	}

	GameSettings* getGameSettings() {
		return gameSettings;
	}*/

	void setView(LayoutView* view);

	LayoutView* getView();
	
	Button* getButton();
	void setButton(Button* button);

	ClickEvent();
	~ClickEvent();

	void prepareBoardSettings();
};

