#pragma once
#include <SFML\Graphics.hpp>

class ClickEvent
{
	sf::RenderWindow* window;
public:


	void setWindow(sf::RenderWindow* window) {
		this->window = window;
	}

	sf::RenderWindow* getWindow() {
		return window;
	}
	
	ClickEvent();
	~ClickEvent();
};

