#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
	
public:
	void fillLPatternMoves(int deltaRow, int deltaColumn);
	void fillPossibleMoves();

	Knight();
	Knight(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	~Knight();
};

