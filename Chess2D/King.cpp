#include "King.h"
#include "ChessBoard.h"
King::King()
{
}

King::King(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	board->setKing(this);
}


King::~King()
{
}

void King::fillOneFieldAroundPiece(int deltaRow, int deltaColumn) {
	if (board->getField(col + deltaColumn, row + deltaRow) && board->getField(col + deltaColumn, row + deltaRow)->isPossibleToMoveHere(chessColor))
		addToPossibleMoves(board->getField(col + deltaColumn, row + deltaRow));
}


void King::fillPossibleMoves() {
	fillOneFieldAroundPiece(1, 1);
	fillOneFieldAroundPiece(-1, -1);
	fillOneFieldAroundPiece(-1, 1);
	fillOneFieldAroundPiece(1, -1);

	fillOneFieldAroundPiece(0, 1);
	fillOneFieldAroundPiece(0, -1);
	fillOneFieldAroundPiece(1, 0);
	fillOneFieldAroundPiece(-1, 0);
}