#include "King.h"
#include "ChessBoard.h"
King::King()
{
	type = KING;
}

King::King(CHESS_ROW row, CHESS_COLUMN col, PLAYER_COLOR color, ChessBoard* board, sf::Sprite* sprite)
{
	init(col, row, color, board, sprite);
	board->setKing(this);
	type = KING;
}
King::King(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard) {

	init(col, row, color, board, setOnBoard);
	board->setKing(this);
	type = KING;
}

King::~King()
{
}

void King::move(ChessBoardField * field)
{
	if (isFirstMoveAvaliable())
		disableFirstMove();

	int numberOfPassedFields = (col - field->getColumn());
	
	ChessPiece::move(field);

	if (abs(numberOfPassedFields) == 2) {
		CHESS_BOARD_SIDE boardSide = (numberOfPassedFields < 0 ? KING_SIDE : QUEEN_SIDE);
		Rook* rook = board->getRook(chessColor, boardSide);
		rook->doCastlingOnField(getSimpleField().move(0, boardSide == QUEEN_SIDE ? 1 : -1));
	}
	

	
}

std::vector<SimpleChessField> King::getAttackedFields()
{
	std::vector<SimpleChessField> result;
	std::vector<ChessBoardField* > tmp;


	tmp.push_back(getOneFieldAroundPiece(1, 1));
	tmp.push_back(getOneFieldAroundPiece(-1, -1));
	tmp.push_back(getOneFieldAroundPiece(-1, 1));
	tmp.push_back(getOneFieldAroundPiece(1, -1));
	
	tmp.push_back(getOneFieldAroundPiece(0, 1));
	tmp.push_back(getOneFieldAroundPiece(0, -1));
	tmp.push_back(getOneFieldAroundPiece(1, 0));
	tmp.push_back(getOneFieldAroundPiece(-1, 0));
	

	for (auto field : tmp) {
		if (field != nullptr)
			result.push_back(field->toSimpleField());
	}

	return result;
}

void King::fillOneFieldAroundPiece(int deltaRow, int deltaColumn) {
	if (board->getField(col + deltaColumn, row + deltaRow) && board->getField(col + deltaColumn, row + deltaRow)->isPossibleToMoveHere(chessColor))
		addToPossibleMoves(board->getField(col + deltaColumn, row + deltaRow));
}

ChessBoardField* King::getOneFieldAroundPiece(int deltaRow, int deltaColumn) {
	return board->getField(col + deltaColumn, row + deltaRow);
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

	tryToAddCastling();
}

void King::tryToAddCastling() {
	bool queenSideCastling = board->isCastlingPossible(chessColor, QUEEN_SIDE);
	bool kingSideCastling = board->isCastlingPossible(chessColor, KING_SIDE);

	if (queenSideCastling)
		addToPossibleMoves(board->getField(getSimpleField().move(0, -2)));

	if (kingSideCastling)
		addToPossibleMoves(board->getField(getSimpleField().move(0, 2)));

}