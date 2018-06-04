#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ChessEnums.h"


class OptionsView;
class ColorOptionsButtonAction : public ButtonAction
{
	COLOR_OPTION color;
	OptionsView* optionsView = nullptr;
public:
	ColorOptionsButtonAction(COLOR_OPTION color, OptionsView* optionsView);
	~ColorOptionsButtonAction() {};

	void doAction(ClickEvent* event);
};

class ColorOptionsButton : public Button {

	COLOR_OPTION color;
public:
	ColorOptionsButton(COLOR_OPTION color, OptionsView* optionsView);
	
	COLOR_OPTION getColor() {
		return color;
	}
};