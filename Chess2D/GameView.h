#pragma once
#include "LayoutView.h"
#include "ChessBoard.h"
#include "ChessAI.h"

class GameView : public LayoutView
{
	ChessBoard* board = new ChessBoard(); 
	FieldSelector* fieldSelector = new FieldSelector();
	ChessAI* chessAI = nullptr;
	
	
public:
	GameView(int height, int width, sf::Sprite* background) : LayoutView(width, height, background) {};
	~GameView();
	
	void additionalDisplayAction(sf::RenderWindow* window);
	void initDisplaying();
	void additionalEventCheck(sf::RenderWindow* window);
	void checkStatus(sf::RenderWindow * window);
	void highlightSelectedPromotionPawnButton();
	void setChessAI(ChessAI* chessAI) { this->chessAI = chessAI; }
};

