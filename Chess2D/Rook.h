#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
	bool firstMove = true;

public:
	void fillPossibleMoves();

	void move(ChessBoardField * field);

	Rook();
	Rook(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	Rook(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~Rook();

	void disableFirstMove() { firstMove = false; }
	void initFirstMove(bool firstMove) { this->firstMove = firstMove; }
	bool isFirstMoveAvaliable() { return firstMove; }

	
};

