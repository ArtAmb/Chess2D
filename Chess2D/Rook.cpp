#include "Rook.h"
#include "ChessBoard.h"
Rook::Rook()
{
	type = ROOK;
}

Rook::Rook(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	type = ROOK;
}

Rook::Rook(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard) {
	init(col, row, color, board, setOnBoard);
	type = ROOK;
}

Rook::~Rook()
{
}

std::vector<SimpleChessField> Rook::getAttackedFields()
{
	return getAttackedFieldsByRook();
}

void Rook::fillPossibleMoves()
{
	fillPossibleMovesForRook();
}

void Rook::move(ChessBoardField * field)
{
	if (isFirstMoveAvaliable())
		disableFirstMove();

	ChessPiece::move(field);
}