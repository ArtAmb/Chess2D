#pragma once
#include <vector>
#include "MenuButton.h"
#include "GraphicEngine.h"
#include <SFML\Graphics.hpp>

class LayoutView
{
	std::vector<Button*> buttons;
	sf::Sprite* background;
	int height, width;
	int heightComponentsGap = 10;
public:

	void addButton(Button* button);
	void draw(sf::RenderWindow* window);
	void setTexture(sf::Sprite* background);
	LayoutView(int height, int width, sf::Sprite* background);
	void prepareView();
	void setHeightGap(int);
	void display(sf::RenderWindow* window);
	~LayoutView();
};

