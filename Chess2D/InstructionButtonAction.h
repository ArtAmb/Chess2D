#pragma once
#include "MenuButton.h"
#include "LayoutView.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "ChessBoard.h"
class InstructionButtonAction :	public ButtonAction
{
	LayoutView* view = nullptr;
	ResourceManager* resourceManager = ResourceManager::getInstance();
public:
	InstructionButtonAction();
	~InstructionButtonAction();

	void doAction(ClickEvent* event);
};

