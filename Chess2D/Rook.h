#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
	
public:
	void fillPossibleMoves();

	Rook();
	Rook(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	~Rook();
};

