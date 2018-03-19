#include "MenuButton.h"

Button::Button()
{
}


Button::~Button()
{
	if (action != nullptr)
		delete action;
}

void Button::AddFrameON(sf::IntRect Frame)
{
	Frames[BT_ON] = Frame;

}
void Button::AddFrameOFF(sf::IntRect Frame)
{
	Frames[BT_OFF] = Frame;
}

sf::Sprite Button::RetSprite()
{
	SpriteButton.setTextureRect(Frames[STATE]);
	return SpriteButton;
}


void Button::SetTexture(sf::Texture* Tex)
{
	SpriteButton.setTexture(*Tex);
}

bool Button::contains(sf::Vector2f point)
{
	return SpriteButton.getGlobalBounds().contains(point);
}

void Button::setOnClickAction(ButtonAction* action)
{
	this->action = action;
}

void Button::click(ClickEvent* event)
{
	if (action == nullptr)
		return;

	action->doAction(event);
	delete event;
}

