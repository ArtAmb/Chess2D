#include "GameButtonAction.h"



GameButtonAction::GameButtonAction()
{
	TextureResource* buttonsTextures = resourceManager->getTexture(RESOURCE::TEXTURE::GAME_MODE_BUTTONS);
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	view = new LayoutView(backgroundTexture->getConverter()->getElementHeight(), backgroundTexture->getConverter()->getElementWidth(), backgroundTexture->getSprite(0,0));


}


GameButtonAction::~GameButtonAction()
{
	if (view != nullptr)
		delete view;
}

void GameButtonAction::doAction(ClickEvent* event)
{
	view->draw(event->getWindow());

	
}
