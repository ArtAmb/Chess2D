#pragma once
#include <SFML\Graphics.hpp>
#include "LayoutView.h"

class Game
{
	sf::RenderWindow* mainWindow;
	LayoutView* menuView;


public:
	Game(sf::RenderWindow* mainWindow, GraphicEngine* engine);
	void startGame();
	~Game();
};

