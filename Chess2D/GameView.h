#pragma once
#include "LayoutView.h"
#include "ChessBoard.h"

class GameView : public LayoutView
{
	ChessBoard* board = new ChessBoard(); 
public:
	GameView(int height, int width, sf::Sprite* background) : LayoutView(width, height, background) {};
	~GameView();
	
	void additionalDisplayAction(sf::RenderWindow* window);
};

