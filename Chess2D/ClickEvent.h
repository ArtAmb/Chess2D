#pragma once
#include <SFML\Graphics.hpp>
class LayoutView;
class ClickEvent
{
	sf::RenderWindow* window;
	LayoutView* view;

public:

	void setWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* getWindow() {
		return window;
	}
	
	void setView(LayoutView* view);

	LayoutView* getView();
	
	ClickEvent();
	~ClickEvent();
};

