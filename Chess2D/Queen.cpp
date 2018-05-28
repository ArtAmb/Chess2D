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

std::vector<SimpleChessField> Queen::getAttackedFields() {
	std::vector<SimpleChessField> result;
	auto bishopAttackedFields = getAttackedFieldsByBishop();
	auto rookAttackedFields = getAttackedFieldsByRook();

	result.insert(result.end(), bishopAttackedFields.begin(), bishopAttackedFields.end());
	result.insert(result.end(), rookAttackedFields.begin(), rookAttackedFields.end());

	return result;
}

void Queen::fillPossibleMoves()
{
	fillPossibleMovesForRook();
	fillPossibleMovesForBishop();
}