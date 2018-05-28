#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
	void fillOneFieldAroundPiece(int deltaRow, int deltaColumn);
	ChessBoardField* getOneFieldAroundPiece(int deltaRow, int deltaColumn);
	bool firstMove = true;
public:
	void fillPossibleMoves();

	void tryToAddCastling();

	King();
	King(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard * board, sf::Sprite * sprite);
	King(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
	~King();
	void disableFirstMove() { firstMove = false; }
	void initFirstMove(bool firstMove) { this->firstMove = firstMove; }
	bool isFirstMoveAvaliable() { return firstMove; }

	void move(ChessBoardField* field);
	std::vector<SimpleChessField> getAttackedFields();
};

