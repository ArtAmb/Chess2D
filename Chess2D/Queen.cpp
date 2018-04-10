#include "Queen.h"
#include "ChessBoard.h"
Queen::Queen()
{
}

Queen::Queen(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	
}


Queen::~Queen()
{
}

void Queen::fillPossibleMoves()
{
	fillPossibleMovesForRook();
	fillPossibleMovesForBishop();
}