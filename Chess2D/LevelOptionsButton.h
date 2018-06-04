#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ChessEnums.h"

class OptionsView;
class LevelOptionsButtonAction : public ButtonAction
{
	LEVEL_OPTION level;
	OptionsView* optionsView = nullptr;

public:
	LevelOptionsButtonAction(LEVEL_OPTION level, OptionsView* optionsView);
	~LevelOptionsButtonAction();
	
	void doAction(ClickEvent* event);
};

class LevelOptionsButton : public Button {

	LEVEL_OPTION level;
public:
	LevelOptionsButton(LEVEL_OPTION level, OptionsView* optionsView);

	LEVEL_OPTION getLevel() {
		return level;
	}
};

