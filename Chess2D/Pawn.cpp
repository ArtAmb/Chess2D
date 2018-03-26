#include "Pawn.h"



Pawn::Pawn(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
}


Pawn::~Pawn()
{
}
