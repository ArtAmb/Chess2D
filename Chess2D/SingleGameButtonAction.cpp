#include "SingleGameButtonAction.h"
#include "SFML/Graphics.hpp"


void SingleGameButtonAction::prepareBoard()
{
	if (view != nullptr)
		delete view;

	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	sf::Sprite* back = fieldTexture->getSprite(0, 1);

	view = new GameView(fieldTexture->getHeight(), fieldTexture->getWidth(), back);
}

SingleGameButtonAction::SingleGameButtonAction()
{

}


SingleGameButtonAction::~SingleGameButtonAction()
{
}

void SingleGameButtonAction::doAction(ClickEvent* event)
{
	prepareBoard();
	view->display(event->getWindow());
	
	
}
