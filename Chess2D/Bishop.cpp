#include "Bishop.h"
#include "ChessBoard.h"
Bishop::Bishop()
{
	type = BISHOP;
}

Bishop::Bishop(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	type = BISHOP;
	
}

Bishop::Bishop(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard) {
	init(col, row, color, board, setOnBoard);
	type = BISHOP;
}


Bishop::~Bishop()
{
	
}

void Bishop::fillPossibleMoves()
{
	fillPossibleMovesForBishop();
}

std::vector<SimpleChessField> Bishop::getAttackedFields()
{
	return getAttackedFieldsByBishop();
}
