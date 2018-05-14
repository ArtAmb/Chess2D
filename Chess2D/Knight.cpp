#include "Knight.h"
#include "ChessBoard.h"
Knight::Knight()
{
	type = KNIGHT;
}

Knight::Knight(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	type = KNIGHT;

}

Knight::Knight(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard) {
	init(col, row, color, board, setOnBoard);
	type = KNIGHT;
}


Knight::~Knight()
{
}

void Knight::fillLPatternMoves(int deltaRow, int deltaColumn) {
	if (board->getField(col + deltaColumn, row + deltaRow) && board->getField(col + deltaColumn, row + deltaRow)->isPossibleToMoveHere(chessColor))
		addToPossibleMoves(board->getField(col + deltaColumn, row + deltaRow));
}

void Knight::fillPossibleMoves() {
	fillLPatternMoves(1, -2);
	fillLPatternMoves(-1, -2);

	fillLPatternMoves(1, 2);
	fillLPatternMoves(-1, 2);

	fillLPatternMoves(-2, 1);
	fillLPatternMoves(-2, -1);

	fillLPatternMoves(2, 1);
	fillLPatternMoves(2, -1);
}
