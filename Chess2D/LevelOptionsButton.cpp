#include "LevelOptionsButton.h"
#include "OptionsView.h"

LevelOptionsButtonAction::LevelOptionsButtonAction(LEVEL_OPTION level, OptionsView* optionsView)
{
	this->level = level;
	this->optionsView = optionsView;
}

LevelOptionsButtonAction::~LevelOptionsButtonAction()
{
}


void LevelOptionsButtonAction::doAction(ClickEvent * event)
{
	Game::getGameSettings()->setLevel(level);
	optionsView->setLevel(level);
}

LevelOptionsButton::LevelOptionsButton(LEVEL_OPTION level, OptionsView* optionsView) : level(level)
{
	action = new LevelOptionsButtonAction(level, optionsView);
};
