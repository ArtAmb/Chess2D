#include "Queen.h"
#include "ChessBoard.h"
Queen::Queen()
{
	type = QUEEN;
}

Queen::Queen(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	type = QUEEN;
}

Queen::Queen(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard) {
	init(col, row, color, board, setOnBoard);
	type = QUEEN;
}


Queen::~Queen()
{
}

void Queen::fillPossibleMoves()
{
	fillPossibleMovesForRook();
	fillPossibleMovesForBishop();
}