#include "CreditsButtonAction.h"



CreditsButtonAction::CreditsButtonAction()
{
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	
	view = new CreditsView(backgroundTexture->getWidth(), backgroundTexture->getHeight(), backgroundTexture->getSprite(1, 1));
}


CreditsButtonAction::~CreditsButtonAction()
{
}

void CreditsButtonAction::doAction(ClickEvent* event)
{

	view->display(event->getWindow());
}
