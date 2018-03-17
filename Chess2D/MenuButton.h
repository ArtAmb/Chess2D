#pragma once
#include <SFML\Graphics.hpp>


class ButtonAction {
	
public:
	virtual void doAction() = 0;

};

class Button
{
	enum ButtonType { BT_OFF = 0, BT_ON = 1 };
	sf::Sprite SpriteButton;
	sf::IntRect Frames[2];
	ButtonType STATE = BT_OFF;

	ButtonAction* action = nullptr;
public:

	Button();
	void AddFrameON(sf::IntRect);
	void AddFrameOFF(sf::IntRect);
	void SetXY(int x, int y) { SpriteButton.setPosition(static_cast<float>(x), static_cast<float>(y)); }
	void SetON() { STATE = BT_ON; }
	void SetOFF() { STATE = BT_OFF; }
	sf::Sprite RetSprite();
	void SetTexture(sf::Texture*);
	bool contains(sf::Vector2f);
	void setOnClickAction(ButtonAction* action);
	void click();
	~Button();
};