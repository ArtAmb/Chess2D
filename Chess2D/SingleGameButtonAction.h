#pragma once
#include "MenuButton.h"
#include "ChessBoard.h"

class SingleGameButtonAction : public ButtonAction
{
public:
	SingleGameButtonAction();
	~SingleGameButtonAction();

	void doAction(ClickEvent* event);
};

