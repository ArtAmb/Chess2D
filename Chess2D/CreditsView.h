#pragma once
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
class CreditsView : public LayoutView
{
	sf::RenderWindow* mainWindow;
	

public:
	CreditsView(int height, int width, sf::Sprite* background) : LayoutView(width, height, background) {};
	~CreditsView();

	void additionalDisplayAction(sf::RenderWindow * window);
	

};