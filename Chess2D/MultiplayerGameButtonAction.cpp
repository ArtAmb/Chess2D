#include "MultiplayerGameButtonAction.h"
#include "SFML/Graphics.hpp"


void MultiplayerGameButtonAction::prepareBoard()
{
	if (view != nullptr)
		delete view;

	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	sf::Sprite* back = fieldTexture->getSprite(0, 1);

	view = new GameView(fieldTexture->getHeight(), fieldTexture->getWidth(), back);
	view->setChessAI(new ChessAI(BLACK, LEVEL_OPTION::EASY));
}

MultiplayerGameButtonAction::MultiplayerGameButtonAction()
{

}


MultiplayerGameButtonAction::~MultiplayerGameButtonAction()
{
}

void MultiplayerGameButtonAction::doAction(ClickEvent* event)
{
	prepareBoard();
	view->display(event->getWindow());


}
