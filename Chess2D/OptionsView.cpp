#include "OptionsView.h"

OptionsView::~OptionsView()
{

}

void OptionsView::additionalDisplayAction(sf::RenderWindow* window)
{
	for(auto& button : colorButtons) {
		if(button->getColor() == color)
			button->SetON();
	}

	for (auto& button : levelButtons) {
		if (button->getLevel() == level)
			button->SetON();
	}
}

