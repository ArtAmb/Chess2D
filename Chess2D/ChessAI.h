#pragma once

#include "ChessBoard.h"

class ChessAIMove {
	ChessPiece* piece = nullptr;
	CHESS_ROW row;
	CHESS_COLUMN column;
	public:
	ChessAIMove() {}
	ChessAIMove(ChessPiece* piece, SimpleChessField field) : piece(piece), row(field.getRow()), column(field.getColumn()) {};
	SimpleChessField getField() { return SimpleChessField(row, column); }
	ChessPiece* getPiece() { return piece; }
};

class ChessAIPositionEstimation {
	double estimation;
public:
	double getEstimation() { return estimation; }
};

class ChessAI
{
	PLAYER_COLOR color;
	LEVEL_OPTION level;
	bool thinking = false;
public:
	ChessAI(PLAYER_COLOR color, LEVEL_OPTION level) : color(color), level(level) {};
	~ChessAI();

	ChessAIPositionEstimation estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board);
	ChessAIMove calculateNextMove(ChessBoard*);
	PLAYER_COLOR getColor() { return color; }
	
	bool isThinking() { return thinking; }
	void startThinking() { thinking = true; }
	void stopThinking() { thinking = false; }
};

