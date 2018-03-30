#pragma once
#include <vector>
#include "MenuButton.h"
#include "GraphicEngine.h"
#include <SFML\Graphics.hpp>

class LayoutView
{
protected:

	std::vector<Button*> buttons;
	sf::Sprite* background;
	int height, width;
	int heightComponentsGap = 10;
	int topPadding = 150;
	sf::Keyboard::Key endKey = sf::Keyboard::Escape;
	bool displaying = true;

	sf::Event happening;
	sf::Vector2f mousePosition;
	
	virtual void finishDisplaying();
	virtual void additionalDisplayAction(sf::RenderWindow* window);
	virtual void additionalEventCheck(sf::RenderWindow* window);
	void checkButtons(sf::RenderWindow* window);
public:

	LayoutView(int height, int width, sf::Sprite* background);
	void setEndKey(sf::Keyboard::Key key);
	void setTopPadding(int padding);
	void addButton(Button* button);
	void draw(sf::RenderWindow* window);
	void setTexture(sf::Sprite* background);
	void prepareView();
	void setHeightGap(int);
	void display(sf::RenderWindow* window);
	void setDisplaying(bool);
	bool isDisplaying() { return displaying; };
	~LayoutView();
};

