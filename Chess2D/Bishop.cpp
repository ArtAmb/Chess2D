#include "Bishop.h"
#include "ChessBoard.h"
Bishop::Bishop()
{
}

Bishop::Bishop(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	
}


Bishop::~Bishop()
{
}

void Bishop::fillPossibleMoves()
{
	fillPossibleMovesForBishop();
}