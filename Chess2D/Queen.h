#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{
	
public:
	void fillPossibleMoves();

	Queen();
	Queen(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	Queen(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~Queen();
};

