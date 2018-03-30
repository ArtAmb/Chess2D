#include "GameView.h"

GameView::~GameView()
{
	if (board != nullptr)
		delete board;
}

void GameView::additionalDisplayAction(sf::RenderWindow * window)
{
	board->draw(window);
}
