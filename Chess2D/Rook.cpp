#include "Rook.h"
#include "ChessBoard.h"
Rook::Rook()
{
}

Rook::Rook(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	
}


Rook::~Rook()
{
}

void Rook::fillPossibleMoves()
{
	fillPossibleMovesForRook();
}