#include "ChessPiece.h"
#include "ChessBoard.h"


ChessPiece::ChessPiece()
{
}

void ChessPiece::init(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, sf::Sprite *sprite)
{
	this->col = col;
	this->row = row;
	this->chessColor = color;
	this->board = board;
	this->sprite = sprite;

	board->getField(col, row)->setPiece(this);
}


ChessPiece::~ChessPiece()
{
}

void ChessPiece::draw(sf::RenderWindow * window)
{
	window->draw(*sprite);
}

sf::Sprite * ChessPiece::getSprite()
{
	return sprite;
}
