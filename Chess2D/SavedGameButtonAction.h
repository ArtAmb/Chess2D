#pragma once
#include "MenuButton.h"

class SavedGameButtonAction : public ButtonAction
{
public:
	SavedGameButtonAction();
	~SavedGameButtonAction();

	void doAction(ClickEvent* event);
};

