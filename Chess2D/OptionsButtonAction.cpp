#include "OptionsButtonAction.h"
#include "LevelOptionsButton.h"



OptionsButtonAction::OptionsButtonAction()
{
	//this->mainWindow = mainWindow;
	TextureResource* buttonsTexture = resourceManager->getTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS);
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	

	view = new OptionsView(backgroundTexture->getWidth(), backgroundTexture->getHeight(), backgroundTexture->getSprite(1, 1));

	int i = 5;
	Button* colorModeButton = game->createDefaultButton(buttonsTexture, i, view);

	++i;
	Button* randomColorButton = game->createDefaultButton(buttonsTexture, i, view);
	++i;
	Button* whiteColorButton = game->createDefaultButton(buttonsTexture, i, view);	
	++i;
	Button* blackColorButton = game->createDefaultButton(buttonsTexture, i, view);	
	++i;
	Button* levelModeButton = game->createDefaultButton(buttonsTexture, i, view);	
	++i;
	Button* easyLevelButton = game->createDefaultButton(buttonsTexture, i, view);
	easyLevelButton->setOnClickAction(new LevelOptionsButton(LEVEL_OPTION::EASY));
	++i;
	Button* normalLevelButton = game->createDefaultButton(buttonsTexture, i, view);
	normalLevelButton->setOnClickAction(new LevelOptionsButton(LEVEL_OPTION::NORMAL));
	++i;
	Button* hardLevelButton = game->createDefaultButton(buttonsTexture, i, view);
	hardLevelButton->setOnClickAction(new LevelOptionsButton(LEVEL_OPTION::HARD));
	
	view->prepareView();
}


OptionsButtonAction::~OptionsButtonAction()
{
}

void OptionsButtonAction::doAction(ClickEvent* event)
{
	view->display(event->getWindow());
}
