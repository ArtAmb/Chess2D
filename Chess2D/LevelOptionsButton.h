#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "ChessEnums.h"

class LevelOptionsButton : public ButtonAction
{
	LEVEL_OPTION level;
	

public:
	LevelOptionsButton(LEVEL_OPTION level);
	~LevelOptionsButton();

	void doAction(ClickEvent* event);
};

