#include "InstructionButtonAction.h"



InstructionButtonAction::InstructionButtonAction()
{
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);

	view = new LayoutView(backgroundTexture->getWidth(), backgroundTexture->getHeight(), backgroundTexture->getSprite(1, 0));
}


InstructionButtonAction::~InstructionButtonAction()
{
}

void InstructionButtonAction::doAction(ClickEvent* event)
{
	view->display(event->getWindow());
}
