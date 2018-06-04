#include "ColorOptionsButton.h"
#include "OptionsView.h"

ColorOptionsButtonAction::ColorOptionsButtonAction(COLOR_OPTION color, OptionsView* optionsView) : color(color), optionsView(optionsView) {};

void ColorOptionsButtonAction::doAction(ClickEvent * event)
{
	Game::getGameSettings()->setColor(color);
	optionsView->setColor(color);
}

ColorOptionsButton::ColorOptionsButton(COLOR_OPTION color, OptionsView* optionsView) : color(color)
{
	action = new ColorOptionsButtonAction(color, optionsView);
};
