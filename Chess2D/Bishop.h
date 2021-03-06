#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
	
public:
	void fillPossibleMoves();
	std::vector<SimpleChessField> getAttackedFields();

	Bishop();
	Bishop(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	Bishop(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~Bishop();
};

