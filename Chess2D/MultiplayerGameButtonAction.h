#pragma once
#include "MenuButton.h"
#include "ChessBoard.h"
#include "GameView.h"
#include "Game.h"


class MultiplayerGameButtonAction : public ButtonAction
{
	GameView* view;


	void prepareBoard();
public:
	MultiplayerGameButtonAction();
	~MultiplayerGameButtonAction();

	void doAction(ClickEvent* event);
};

