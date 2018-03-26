#pragma once
#include <SFML\Graphics.hpp>
#include <conio.h>
#include <iostream>

class GraphicEngine
{
	int WIDTH_BACKGROUND = 1008;
	int HEIGHT_BACKGROUND = 720;

	static sf::RenderWindow mainWindow;
	sf::Font font;
public:
	static sf::Texture* loadTexture(std::string fileName);
	static void errorMessage(std::string errorDescription);
	sf::RenderWindow* getMainWindow() { return &mainWindow; }
	GraphicEngine();
	~GraphicEngine();
};

