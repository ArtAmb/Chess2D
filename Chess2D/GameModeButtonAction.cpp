#include "GameModeButtonAction.h"
#include "SingleGameButtonAction.h"
#include "MultiplayerGameButtonAction.h"



GameModeButtonAction::GameModeButtonAction()
{
	TextureResource* buttonsTextures = resourceManager->getTexture(RESOURCE::TEXTURE::GAME_MODE_BUTTONS);
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	
	view = new LayoutView(backgroundTexture->getWidth(), backgroundTexture->getHeight(), backgroundTexture->getSprite(0,0));

	view->setHeightGap(50);
	view->setTopPadding(150);

	Button* buttonSingle = new Button();
	buttonSingle->SetTexture(buttonsTextures->getTexture());
	buttonSingle->AddFrameOFF(buttonsTextures->getConverter()->getElementRect(0, 0));
	buttonSingle->AddFrameON(buttonsTextures->getConverter()->getElementRect(0, 1));
	buttonSingle->setOnClickAction(new SingleGameButtonAction());
	view->addButton(buttonSingle); // TODO refactor

	Button* button = new Button();
	button->SetTexture(buttonsTextures->getTexture());
	button->AddFrameOFF(buttonsTextures->getConverter()->getElementRect(1, 0));
	button->AddFrameON(buttonsTextures->getConverter()->getElementRect(1, 1));
	button->setOnClickAction(new MultiplayerGameButtonAction());
	view->addButton(button); // TODO refactor

	view->prepareView();
}


GameModeButtonAction::~GameModeButtonAction() {
	if (view != nullptr)
		delete view;
}

void GameModeButtonAction::doAction(ClickEvent* event) {
	view->display(event->getWindow());
}
