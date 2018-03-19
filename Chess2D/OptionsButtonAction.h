#pragma once
#include "MenuButton.h"

class OptionsButtonAction : public ButtonAction
{
public:
	OptionsButtonAction();
	~OptionsButtonAction();

	void doAction(ClickEvent* event);
};

