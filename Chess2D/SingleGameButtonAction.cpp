#include "SingleGameButtonAction.h"
#include "SFML/Graphics.hpp"

void SingleGameButtonAction::prepareBoard(GameSettings* gameSettings)
{
	if (view != nullptr)
		delete view;

	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	sf::Sprite* back = fieldTexture->getSprite(0, 1);

	view = new GameView(fieldTexture->getHeight(), fieldTexture->getWidth(), back);

	PLAYER_COLOR color = BLACK;

	switch (gameSettings->getColor()) {
	case WHITE_O:
		color = BLACK;
		break;
	case BLACK_O:
		color = WHITE;
		break;
	case RANDOM_O:
		color = (rand() % 2 ? WHITE : BLACK);
		break;
	}
	

	view->setChessAI(new ChessAI(color, gameSettings->getLevel()));
}

SingleGameButtonAction::SingleGameButtonAction()
{

}


SingleGameButtonAction::~SingleGameButtonAction()
{
}

void SingleGameButtonAction::doAction(ClickEvent* event)
{
	prepareBoard(Game::getGameSettings());
	view->display(event->getWindow());
	
}
