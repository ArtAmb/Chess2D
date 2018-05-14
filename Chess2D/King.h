#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
	void fillOneFieldAroundPiece(int deltaRow, int deltaColumn);
public:
	void fillPossibleMoves();

	King();
	King(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	King(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~King();
};

