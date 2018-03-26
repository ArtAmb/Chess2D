#pragma once
#include <SFML\Graphics.hpp>
#include "MenuButton.h"
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "ChessBoard.h"

class GameButtonAction : public ButtonAction
{
	LayoutView* view = nullptr;
	ChessBoard* chessBoard;
	ResourceManager* resourceManager = ResourceManager::getInstance();
	
public:
	GameButtonAction();
	~GameButtonAction();

	void doAction(ClickEvent* event);
};

