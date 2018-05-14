#pragma once
#include "ChessPiece.h"
#include "SimpleChessField.h"

class Pawn : public ChessPiece
{
	bool firstMoveAvailable = true;
	bool enPasantAvailable = false;
	void fillPossibleMovesForPawn(int deltaRow);
	void fillPossibleMovesForEnPasant(int deltaColumn, int deltaRow);
	CHESS_COLUMN oldColumn;
	CHESS_ROW oldRow;
public:
	void move(ChessBoardField* field);
	void fillPossibleMoves();
	bool isFirstMoveAvailable() { return firstMoveAvailable; }
	bool isEnPasantAvailable() { return enPasantAvailable; }
	void disableEnPasant() { enPasantAvailable = false; }
	void enableEnPasant() { enPasantAvailable = true; }
	void initFirstMove(bool firstMoveAvailable) { this->firstMoveAvailable = firstMoveAvailable; }
	SimpleChessField getOldField() { return SimpleChessField(oldRow, oldColumn); }

public:
	Pawn(CHESS_ROW, CHESS_COLUMN, PLAYER_COLOR, ChessBoard*, sf::Sprite*);
	Pawn(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~Pawn();
};

