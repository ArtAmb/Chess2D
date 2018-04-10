#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
	
public:
	void fillPossibleMoves();

	Bishop();
	Bishop(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	~Bishop();
};

