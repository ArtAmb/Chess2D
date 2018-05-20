#include "ChessPiece.h"
#include "ChessBoard.h"
#include <iostream>

ChessPiece::ChessPiece()
{
}

void ChessPiece::init(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, sf::Sprite *sprite)
{
	this->col = col;
	this->row = row;
	this->chessColor = color;
	this->board = board;
	this->sprite = sprite;

	board->getField(col, row)->setPiece(this);
}

void ChessPiece::init(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard *board, bool setOnBoard)
{
	this->col = col;
	this->row = row;
	this->chessColor = color;
	this->board = board;
	this->alive = setOnBoard;

	if(setOnBoard)
		board->getField(col, row)->setPiece(this);
}


ChessPiece::~ChessPiece()
{
	if (sprite != nullptr)
		delete sprite;
}

void ChessPiece::draw(sf::RenderWindow * window)
{
	window->draw(*sprite);
}

sf::Sprite * ChessPiece::getSprite()
{
	return sprite;
}

PLAYER_COLOR ChessPiece::getColor()
{
	return chessColor;
}

void ChessPiece::reset()
{
	resetPossibleMoves();
}

void ChessPiece::die()
{
	reset();
	board->getField(col, row)->empty();
	alive = false;
}

std::vector<SimpleChessField> ChessPiece::getPossibleMovesIncludingKing()
{
	if (!isBeingProcessed()) {
		resetPossibleMoves();
		fillPossibleMoves();
	}
	return possibleMoves;
}

std::vector<SimpleChessField> ChessPiece::getPossibleMoves() {
	resetPossibleMoves();
	tryToFillPossibleMoves();

	return possibleMoves;
}

std::string ChessPiece::getTypeName()
{
	
	CHESS_PIECES pieceType = getType();
	std::string pieceTypeName;

	switch (pieceType)
	{
	case 0:
		pieceTypeName = "P";
		break;
	case 1:
		pieceTypeName = "S";
		break;
	case 2:
		pieceTypeName = "W";
		break;
	case 3:
		pieceTypeName = "G";
		break;
	case 4:
		pieceTypeName = "H";
		break;
	case 5:
		pieceTypeName = "K";
		break;

	}
	return pieceTypeName;
}

std::string ChessPiece::getRowName()
{	
	int row = getRow() + 1;
	std::string rowName = std::to_string(row);
	return rowName;
}

std::string ChessPiece::getColumnName()
{

	CHESS_COLUMN pieceColumn = getCol();
	std::string pieceColumnName;

	switch (pieceColumn)
	{
	case 0:
		pieceColumnName = "A";
		break;
	case 1:
		pieceColumnName = "B";
		break;
	case 2:
		pieceColumnName = "C";
		break;
	case 3:
		pieceColumnName = "D";
		break;
	case 4:
		pieceColumnName = "E";
		break;
	case 5:
		pieceColumnName = "F";
		break;
	case 6:
		pieceColumnName = "G";
		break;
	case 7:
		pieceColumnName = "H";
		break;

	}

	return pieceColumnName;
}

void ChessPiece::printf()
{
	std::cout << getType() << "(" << getRow() << "," << getCol() << ")" << std::endl;
}

void ChessPiece::highlightPossibleMoves()
{
	tryToFillPossibleMoves();
	for (int i = 0; i < possibleMoves.size(); ++i) {
		highlightField(possibleMoves[i]);
	}
}

bool ChessPiece::checkNextMove(SimpleChessField field)
{
	tryToFillPossibleMoves();
	for (int i = 0; i < possibleMoves.size(); ++i) {
		if (possibleMoves[i] == field)
			return true;
	}
	return false;
}

bool ChessPiece::tryToMove(SimpleChessField simpleField) {
	ChessBoardField* field = board->getField(simpleField.getColumn(), simpleField.getRow());
	return tryToMove(field);
}

bool ChessPiece::tryToMove(ChessBoardField * field) {
	if (checkNextMove(field->toSimpleField())) {
		move(field);

		if (dynamic_cast<Pawn*>(this) != nullptr && (row == CHESS_ROW::R_1 || row == CHESS_ROW::R_8)) {
			board->setPawnBeingPromoted(dynamic_cast<Pawn*>(this));
			board->activatePromotionButtons(this->getColor());
			return false;
		}

		return true;
	}
	return false;
}

SimpleChessField ChessPiece::getSimpleField()
{
	if (isBeingProcessed())
		return getNewField();

	return SimpleChessField(row, col);
}

void ChessPiece::move(ChessBoardField* field)
{
	if (field->getPiece() != NULL) {
		field->getPiece()->die();
	}
	board->getField(col, row)->empty();
	col = field->getColumn();
	row = field->getRow();
	field->setPiece(this);
}

void ChessPiece::fillPossibleMovesFieldSeries(int deltaRow, int deltaColumn) {
	for (int i = 1; ; i++) {
		if (board->getField(col + i * deltaColumn, row + i * deltaRow) && board->getField(col + i * deltaColumn, row + i * deltaRow)->isPossibleToMoveHere(chessColor)) {
			addToPossibleMoves(board->getField(col + i * deltaColumn, row + i * deltaRow));
			if (board->getField(col + i * deltaColumn, row + i * deltaRow)->getPiece() != NULL && !board->getField(col + i * deltaColumn, row + i * deltaRow)->checkPieceColor(chessColor))
				break;
		}
		else break;
	}
}

void ChessPiece::fillPossibleMovesForRook() {
	fillPossibleMovesFieldSeries(1, 0);
	fillPossibleMovesFieldSeries(-1, 0);
	fillPossibleMovesFieldSeries(0, 1);
	fillPossibleMovesFieldSeries(0, -1);
}

void ChessPiece::fillPossibleMovesForBishop() {
	fillPossibleMovesFieldSeries(1, 1);
	fillPossibleMovesFieldSeries(-1, -1);
	fillPossibleMovesFieldSeries(-1, 1);
	fillPossibleMovesFieldSeries(1, -1);
}

void ChessPiece::addToPossibleMoves(ChessBoardField* field)
{
	if (field == NULL)
		return;
	possibleMoves.push_back(field->toSimpleField());
}

void ChessPiece::highlightField(SimpleChessField field)
{
	ChessBoardField* chessBoardField = board->getField(field);
	if (chessBoardField->getPiece() != NULL)
		chessBoardField->inDanger();
	else
		chessBoardField->highlight();
}

void ChessPiece::tryToFillPossibleMoves()
{
	resetPossibleMoves();
	if (!isAlive())
		return;
	fillPossibleMoves();
	for (int i = 0; i < possibleMoves.size(); ) {
		ChessBoardField* field = board->getField(possibleMoves[i]);
		ChessBoardField* myField = board->getField(col, row);
		ChessPiece* tmpPiece = field->getPiece();

		startProcessing();
		setAlive(false);
		myField->setPiece(NULL);
		if (tmpPiece != NULL)
			tmpPiece->setAlive(false);
		field->setPiece(this);
		setNewField(field->getRow(), field->getColumn());
		if (board->checkIfKingIsInCheck(getColor())) {
			possibleMoves.erase(possibleMoves.begin() + i);
			stopProcesing(field, tmpPiece);
			continue;
		}
		stopProcesing(field, tmpPiece);
		++i;
	}
}

void ChessPiece::stopProcesing(ChessBoardField* field, ChessPiece* tmpPiece)
{
	field->setPiece(tmpPiece);
	if (tmpPiece != NULL)
		tmpPiece->setAlive(true);
	setAlive(true);
	ChessBoardField* myField = board->getField(col, row);
	myField->setPiece(this);
	stopProcessing();
}

void ChessPiece::resetPossibleMoves()
{
	possibleMoves.clear();
}

