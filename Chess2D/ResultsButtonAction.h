#pragma once
#include "MenuButton.h"
class ResultsButtonAction :	public ButtonAction
{
public:
	ResultsButtonAction();
	~ResultsButtonAction();

	void doAction(ClickEvent* event);
};

