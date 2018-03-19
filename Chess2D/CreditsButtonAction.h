#pragma once
#include "MenuButton.h"
class CreditsButtonAction : public ButtonAction
{
public:
	CreditsButtonAction();
	~CreditsButtonAction();
	void doAction(ClickEvent* event);
};

