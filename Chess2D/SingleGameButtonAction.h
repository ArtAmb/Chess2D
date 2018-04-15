#pragma once
#include "MenuButton.h"
#include "ChessBoard.h"
#include "GameView.h"
#include "Game.h"

class SingleGameButtonAction : public ButtonAction
{
	GameView* view;
	

	void prepareBoard();
public:
	SingleGameButtonAction();
	~SingleGameButtonAction();
	
	void doAction(ClickEvent* event);
};

