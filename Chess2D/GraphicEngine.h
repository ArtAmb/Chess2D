#pragma once
#include <SFML\Graphics.hpp>
#include <conio.h>
#include <iostream>

class GraphicEngine
{
	int WIDTH_BACKGROUND = 836;
	int HEIGHT_BACKGROUND = 728;

	static sf::RenderWindow mainWindow;
	sf::Font font;
public:
	sf::Texture* loadTexture(std::string fileName);
	static void errorMessage(std::string errorDescription);
	sf::RenderWindow* getMainWindow() { return &mainWindow; }
	GraphicEngine();
	~GraphicEngine();
};

