#pragma once
#include "MenuButton.h"

class QuitButtonAction : public ButtonAction
{
public:
	QuitButtonAction();
	~QuitButtonAction();

	void doAction(ClickEvent* event);
};

