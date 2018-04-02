#include "Pawn.h"
#include "ChessBoard.h"

Pawn::Pawn(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
}


Pawn::~Pawn()
{
}

void Pawn::move(ChessBoardField* field) {
	if (firstMoveAvailable) {
		firstMoveAvailable = false;
	}
	if ((row - field->getRow()) % 2 == 0) {
		int deltaRow = (chessColor == WHITE ? 1 : -1);
		oldColumn = col;
		oldRow = CHESS_ROW(row + deltaRow);
		board->addEnPassantPawns(this);
	}
	ChessPiece::move(field);
	board->tryToKillEnPassantPawn(field->toSimpleField());
}

void Pawn::fillPossibleMovesForPawn(int deltaRow)
{
	if (board->getField(col, row + deltaRow) && board->getField(col, row + deltaRow)->isEmpty())
		addToPossibleMoves(board->getField(col, row + deltaRow));

	if (firstMoveAvailable && board->getField(col, row + deltaRow)->isEmpty() && board->getField(col, row + 2 * deltaRow)->isEmpty())
		addToPossibleMoves(board->getField(col, row + 2 * deltaRow));

	if (board->getField(col - 1, row + deltaRow) && !board->getField(col - 1, row + deltaRow)->isEmpty() && !board->getField(col - 1, row + deltaRow)->checkPieceColor(chessColor))
		addToPossibleMoves(board->getField(col - 1, row + deltaRow));
	if (board->getField(col + 1, row + deltaRow) && !board->getField(col + 1, row + deltaRow)->isEmpty() && !board->getField(col + 1, row + deltaRow)->checkPieceColor(chessColor))
		addToPossibleMoves(board->getField(col + 1, row + deltaRow));

	fillPossibleMovesForEnPasant(1, deltaRow);
	fillPossibleMovesForEnPasant(-1, deltaRow);
}

void Pawn::fillPossibleMovesForEnPasant(int deltaColumn, int deltaRow) {
	if (board->getField(col + deltaColumn, row + deltaRow) && !board->getField(col + deltaColumn, row)->isEmpty()) {
		if (dynamic_cast<Pawn*>(board->getField(col + deltaColumn, row)->getPiece()) != NULL)
			if (dynamic_cast<Pawn*>(board->getField(col + deltaColumn, row)->getPiece())->isEnPasantAvailable())
				addToPossibleMoves(board->getField(col + deltaColumn, row + deltaRow));
	}
}

void Pawn::fillPossibleMoves()
{
	if (chessColor == BLACK) {
		fillPossibleMovesForPawn(-1);
	}
	if (chessColor == WHITE) {
		fillPossibleMovesForPawn(1);
	}
}