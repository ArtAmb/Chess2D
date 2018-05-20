#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
#include "PositionTextureConverter.h"
#include "SimpleChessField.h"
#include <cmath>

void ChessBoardField::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

void ChessBoardField::setTexture(sf::Texture * sprite)
{
	this->texture = sprite;
}

bool ChessBoardField::isEmpty()
{
	return chessPiece == nullptr;
}

void ChessBoardField::empty()
{
	chessPiece = nullptr;
}

ChessPiece * ChessBoardField::getPiece()
{
	return chessPiece;
}

bool ChessBoardField::contains(sf::Vector2f point)
{
	return sprite->getGlobalBounds().contains(point);
}

void ChessBoardField::setPiece(ChessPiece* piece)
{
	this->chessPiece = piece;
	if (sprite != nullptr) {
		if (chessPiece != nullptr)
			chessPiece->setXY((int)sprite->getPosition().x, (int)sprite->getPosition().y);
	}
}

ChessBoardField::~ChessBoardField()
{
	if (sprite != nullptr)
		delete sprite;

	//if (chessPiece != nullptr)
	//	delete chessPiece;
}

void ChessBoardField::setXY(int x, int y)
{
	sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
	if (chessPiece != nullptr)
		chessPiece->setXY(x, y);
}

void ChessBoardField::draw(sf::RenderWindow * mainWindow)
{
	mainWindow->draw(*sprite);
	if (chessPiece != nullptr)
		mainWindow->draw(*chessPiece->getSprite());
}


ChessBoardField* ChessBoard::getField(SimpleChessField field)
{
	return getField(field.getColumn(), field.getRow());
}

ChessBoardField* ChessBoard::getField(int col, int row)
{
	if (col < 0 || col >= BOARD_SIZE || row < 0 || row >= BOARD_SIZE)
		return NULL;
	return &board[row][col];
}

ChessBoardField* ChessBoard::getField(CHESS_COLUMN c, CHESS_ROW r)
{
	return &board[r][c];
}

ChessPiece * ChessBoard::getMyChessPiece(ChessPiece * chessPieceFromTemporaryBoard)
{
	return getField(chessPieceFromTemporaryBoard->getSimpleField())->getPiece();
}

ChessBoard * ChessBoard::toTemporaryBoard()
{
	return new ChessBoard(this);
}

bool ChessBoard::isPawnBeingPromoted()
{
	return getPawnBeingPromoted() != nullptr;
}

std::string pawnTypeToChar(CHESS_PIECES type) {
	switch (type) {
	case PAWN: {
		return "P";
	}

	case KNIGHT:
	{
		return "H";
	}
	case ROOK:
	{
		return "R";
	}
	case BISHOP:
	{
		return "B";
	}
	case QUEEN:
	{
		return "Q";
	}
	case KING:
	{
		return "K";
	}
	}
}

void ChessBoard::printfBoard(std::string comment)
{
	std::cout << "==============" << comment << "==============" << std::endl;
	for (int i = 0; i < 8; ++i) {

		for (int j = 0; j < 8; ++j) {
			if (board[i][j].getPiece() == nullptr) {
				std::cout << ".";
			}
			else {
				if (board[i][j].getPiece()->getColor() == BLACK)
					std::cout << pawnTypeToChar(board[i][j].getPiece()->getType());
				else
					std::cout << board[i][j].getPiece()->getType();
			}

		}
		std::cout << std::endl;

	}
	std::cout << "=============================================" << std::endl;
	std::cout << "=============================================" << std::endl;
}




sf::IntRect ChessBoard::getWhiteFieldSprite()
{
	return fieldTexture->getConverter()->getElementRect(2, 1);
}

sf::IntRect ChessBoard::getBlackFieldSprite()
{
	return fieldTexture->getConverter()->getElementRect(2, 0);
}

void ChessBoard::checkKing(King * king)
{
}

ChessBoard::ChessBoard()
{
	chessBoardType = REAL;
	fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);
	transformationButtonTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::TRANSFORMATION_PAWN_BUTTON);
	TRANSFORMATION_BUTTON_FIELD = transformationButtonTexture->getConverter()->getElementWidth();

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			pawnTransformationButtons[i][j] = new PawnTransformationButton(transformationButtonTexture->getTexture());

	prepareBoard();

	for (int i = 0; i < 8; ++i)
	{
		pieces[WHITE][i] = new Pawn(R_2, (CHESS_COLUMN)i, WHITE, this, fieldTexture->getSprite(0, 0));
	}

	for (int i = 0; i < 8; ++i)
	{
		pieces[BLACK][i] = new Pawn(R_7, (CHESS_COLUMN)i, BLACK, this, fieldTexture->getSprite(1, 0));
	}



	pieces[WHITE][8] = new Bishop(R_1, C_C, WHITE, this, fieldTexture->getSprite(0, 1));
	pieces[WHITE][9] = new Bishop(R_1, C_F, WHITE, this, fieldTexture->getSprite(0, 1));

	pieces[BLACK][8] = new Bishop(R_8, C_C, BLACK, this, fieldTexture->getSprite(1, 1));
	pieces[BLACK][9] = new Bishop(R_8, C_F, BLACK, this, fieldTexture->getSprite(1, 1));

	pieces[WHITE][10] = new Rook(R_1, C_A, WHITE, this, fieldTexture->getSprite(0, 2));
	pieces[WHITE][11] = new Rook(R_1, C_H, WHITE, this, fieldTexture->getSprite(0, 2));

	pieces[BLACK][10] = new Rook(R_8, C_A, BLACK, this, fieldTexture->getSprite(1, 2));
	pieces[BLACK][11] = new Rook(R_8, C_H, BLACK, this, fieldTexture->getSprite(1, 2));

	pieces[WHITE][12] = new Knight(R_1, C_B, WHITE, this, fieldTexture->getSprite(0, 3));
	pieces[WHITE][13] = new Knight(R_1, C_G, WHITE, this, fieldTexture->getSprite(0, 3));

	pieces[BLACK][12] = new Knight(R_8, C_B, BLACK, this, fieldTexture->getSprite(1, 3));
	pieces[BLACK][13] = new Knight(R_8, C_G, BLACK, this, fieldTexture->getSprite(1, 3));

	pieces[WHITE][14] = new Queen(R_1, C_D, WHITE, this, fieldTexture->getSprite(0, 4));
	pieces[BLACK][14] = new Queen(R_8, C_D, BLACK, this, fieldTexture->getSprite(1, 4));

	pieces[WHITE][15] = new King(R_1, C_E, WHITE, this, fieldTexture->getSprite(0, 5));
	pieces[BLACK][15] = new King(R_8, C_E, BLACK, this, fieldTexture->getSprite(1, 5));

	initCastlings();
}

ChessBoard::ChessBoard(ChessBoard* chessBoard) {
	chessBoardType = TEMPORARY;
	for (int i = 0; i < BOARD_SIZE; ++i)
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j] = ChessBoardField((CHESS_ROW)i, (CHESS_COLUMN)j);
		}

	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 16; ++i)
		{
			auto piece = chessBoard->pieces[j][i];
			pieces[j][i] = createChessPiece(piece);
		}

	currPlayer = chessBoard->currPlayer;
	//checkedKing = chessBoard->checkedKing != nullptr ? kings[chessBoard->checkedKing->getColor()] : nullptr;

	initEnPasantPawns(chessBoard->enPassantPawns);
	pawnBeingPromoted = chessBoard->pawnBeingPromoted != nullptr ? static_cast<Pawn*>(getMyChessPiece(chessBoard->pawnBeingPromoted)) : nullptr;
	state = chessBoard->state;
	initCastlings();
}

void ChessBoard::initEnPasantPawns(std::vector<Pawn*> pawns) {
	for (auto pawn : pawns) {
		if (pawn != nullptr)
			enPassantPawns.push_back(static_cast<Pawn*>(getMyChessPiece(pawn)));
	}

}

void ChessBoard::initCastlings() {
	disableCastlings();

	rooks[BLACK][QUEEN_SIDE] = static_cast<Rook*>(getField(C_A, R_8)->getPiece());
	rooks[BLACK][KING_SIDE] = static_cast<Rook*>(getField(C_H, R_8)->getPiece());
	rooks[WHITE][QUEEN_SIDE] = static_cast<Rook*>(getField(C_A, R_1)->getPiece());
	rooks[WHITE][KING_SIDE] = static_cast<Rook*>(getField(C_H, R_1)->getPiece());
}

ChessPiece* ChessBoard::createChessPiece(ChessPiece* piece) {
	ChessPiece* result = nullptr;

	switch (piece->getType()) {
	case PAWN: {
		Pawn * pawn = new Pawn(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		Pawn* piecePawn = static_cast<Pawn*>(piece);
		pawn->initFirstMove(piecePawn->isFirstMoveAvailable());
		piecePawn->isEnPasantAvailable() ? pawn->enableEnPasant() : pawn->disableEnPasant();
		pawn->setOldField(piecePawn->getOldField());

		result = pawn;
		break;
	}

	case KNIGHT:
	{
		result = new Knight(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		break;
	}
	case ROOK:
	{
		result = new Rook(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		break;
	}
	case BISHOP:
	{
		result = new Bishop(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		break;
	}
	case QUEEN:
	{
		result = new Queen(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		break;
	}
	case KING:
	{
		result = new King(piece->getCol(), piece->getRow(), piece->getColor(), this, piece->isAlive());
		break;
	}
	default:
		GraphicEngine::errorMessage("Nie mozna stworzyc pionka! Typ nie rozpoznany");
	}


	piece->isBeingProcessed() ? result->startProcessing() : result->stopProcessing();

	return result;
}

void ChessBoard::prepareBoard() {
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j] = ChessBoardField((CHESS_ROW)i, (CHESS_COLUMN)j);
			board[i][j].setTexture(fieldTexture->getTexture());

			board[i][j].setNormal(i % 2 == j % 2 ? getWhiteFieldSprite() : getBlackFieldSprite());
			board[i][j].setSelected(fieldTexture->getConverter()->getElementRect(2, 2));
			board[i][j].setHighlighted(fieldTexture->getConverter()->getElementRect(2, 3));
			board[i][j].setInDanger(fieldTexture->getConverter()->getElementRect(2, 4));
			board[i][j].prepareSprite();

			board[i][j].setXY(72 + j * 72, 72 + i * 72);
			// TODO dobrze by bylo to wpakowac do jakiegos konstruktora i jakies dto dla spritow zbudowac
		}
	}

	for (int i = 0; i < 4; ++i) {
		pawnTransformationButtons[WHITE][i]->setXY(5 * 72 - TRANSFORMATION_BUTTON_FIELD * 2 + i * TRANSFORMATION_BUTTON_FIELD, 4);
		pawnTransformationButtons[BLACK][i]->setXY(5 * 72 - TRANSFORMATION_BUTTON_FIELD * 2 + i * TRANSFORMATION_BUTTON_FIELD, 25 + (BOARD_SIZE + 1) * 72);
	}

	pawnTransformationButtons[WHITE][PAWN_PROMOTION::PROM_QUEEN]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 0), transformationButtonTexture->getConverter()->getElementRect(1, 0), WHITE, PROM_QUEEN);
	pawnTransformationButtons[BLACK][PAWN_PROMOTION::PROM_QUEEN]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 0), transformationButtonTexture->getConverter()->getElementRect(1, 0), BLACK, PROM_QUEEN);

	pawnTransformationButtons[WHITE][PAWN_PROMOTION::PROM_KNIGHT]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 1), transformationButtonTexture->getConverter()->getElementRect(1, 1), WHITE, PROM_KNIGHT);
	pawnTransformationButtons[BLACK][PAWN_PROMOTION::PROM_KNIGHT]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 1), transformationButtonTexture->getConverter()->getElementRect(1, 1), BLACK, PROM_KNIGHT);

	pawnTransformationButtons[WHITE][PAWN_PROMOTION::PROM_BISHOP]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 2), transformationButtonTexture->getConverter()->getElementRect(1, 2), WHITE, PROM_BISHOP);
	pawnTransformationButtons[BLACK][PAWN_PROMOTION::PROM_BISHOP]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 2), transformationButtonTexture->getConverter()->getElementRect(1, 2), BLACK, PROM_BISHOP);

	pawnTransformationButtons[WHITE][PAWN_PROMOTION::PROM_ROOK]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 3), transformationButtonTexture->getConverter()->getElementRect(1, 3), WHITE, PROM_ROOK);
	pawnTransformationButtons[BLACK][PAWN_PROMOTION::PROM_ROOK]->setFrames(transformationButtonTexture->getConverter()->getElementRect(0, 3), transformationButtonTexture->getConverter()->getElementRect(1, 3), BLACK, PROM_ROOK);

}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 2; ++i)
		for (ChessPiece* piece : pieces[i]) {
			if (piece != nullptr)
				delete piece;
		}

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			delete pawnTransformationButtons[i][j];
}

void ChessBoard::draw(sf::RenderWindow* window) {

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].draw(window);
		}
	}

	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			pawnTransformationButtons[i][j]->draw(window);
}
void ChessBoard::tryToKillEnPassantPawn(SimpleChessField field)
{
	if (enPassantPawns.size() == 0)
		return;

	for (int i = 0; i < enPassantPawns.size(); ++i)
	{
		if (enPassantPawns[i]->isEnPasantAvailable() && enPassantPawns[i]->getOldField() == field)
		{
			enPassantPawns[i]->die();

		}
	}
}

void ChessBoard::promotePawnTo(PAWN_PROMOTION* pawnPromotion)
{
	promotePawnTo(*pawnPromotion);
}
void ChessBoard::promotePawnTo(PAWN_PROMOTION pawnPromotion)
{
	if (chessBoardType == REAL)
		realPromotePawnTo(pawnPromotion);
	else
		simulatePromotePawnTo(pawnPromotion);
}

void ChessBoard::makeMoveAndUpdateCurrentPlayer(ChessAIMove chessAIMove) {
	updateCurrentPlayer(chessAIMove.getPiece()->tryToMove(chessAIMove.getField()));
	if (isPawnBeingPromoted())
		promotePawnTo(chessAIMove.getPawnPromotionType());
}

void ChessBoard::realPromotePawnTo(PAWN_PROMOTION pawnPromotion) {

	if (pawnBeingPromoted == nullptr)
		return;
	PLAYER_COLOR pawnColor = pawnBeingPromoted->getColor();

	ChessPiece * newPawn = nullptr;
	switch (pawnPromotion) {
	case PROM_KNIGHT:
		newPawn = new Knight(pawnBeingPromoted->getRow(), pawnBeingPromoted->getCol(), pawnColor, this, fieldTexture->getSprite(pawnColor, 3));
		break;
	case PROM_ROOK:
		newPawn = new Rook(pawnBeingPromoted->getRow(), pawnBeingPromoted->getCol(), pawnColor, this, fieldTexture->getSprite(pawnColor, 2));
		break;
	case PROM_BISHOP:
		newPawn = new Bishop(pawnBeingPromoted->getRow(), pawnBeingPromoted->getCol(), pawnColor, this, fieldTexture->getSprite(pawnColor, 1));
		break;
	case PROM_QUEEN:
		newPawn = new Queen(pawnBeingPromoted->getRow(), pawnBeingPromoted->getCol(), pawnColor, this, fieldTexture->getSprite(pawnColor, 4));
		break;
	}

	newPawn->getSprite()->setPosition(pawnBeingPromoted->getSprite()->getPosition());

	for (int i = 0; i < 16; ++i)
		if (pieces[pawnBeingPromoted->getColor()][i] == pawnBeingPromoted) {
			pieces[pawnBeingPromoted->getColor()][i] = newPawn;
			delete pawnBeingPromoted;
			break;
		}


	pawnBeingPromoted = nullptr;
	deactivatePromotionButtons();
	updateCurrentPlayer(true);
}

void ChessBoard::simulatePromotePawnTo(PAWN_PROMOTION pawnPromotion)
{
	if (pawnBeingPromoted == nullptr)
		return;
	PLAYER_COLOR pawnColor = pawnBeingPromoted->getColor();

	ChessPiece * newPawn = nullptr;
	switch (pawnPromotion) {
	case PROM_KNIGHT:
		newPawn = createChessPiece(pawnBeingPromoted);
		break;
	case PROM_ROOK:
		newPawn = createChessPiece(pawnBeingPromoted);
		break;
	case PROM_BISHOP:
		newPawn = createChessPiece(pawnBeingPromoted);
		break;
	case PROM_QUEEN:
		newPawn = createChessPiece(pawnBeingPromoted);
		break;
	}

	for (int i = 0; i < 16; ++i)
		if (pieces[pawnBeingPromoted->getColor()][i] == pawnBeingPromoted) {
			pieces[pawnBeingPromoted->getColor()][i] = newPawn;
			delete pawnBeingPromoted;
			break;
		}

	pawnBeingPromoted = nullptr;
	updateCurrentPlayer(true);
}

void ChessBoard::activatePromotionButtons(PLAYER_COLOR color)
{
	if (chessBoardType != REAL)
		return;

	for (int j = 0; j < 4; ++j)
		pawnTransformationButtons[color][j]->setActive(true);
}

void ChessBoard::deactivatePromotionButtons() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j)
			pawnTransformationButtons[i][j]->setActive(false);
}

void ChessBoard::setKing(King * king)
{
	kings[king->getColor()] = king;
}

void ChessBoard::addEnPassantPawns(Pawn * pawn)
{
	enPassantPawns.push_back(pawn);
}
void ChessBoard::unlightAllFields()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].stopHighlighting();
		}
	}

}

void ChessBoard::highlightFields(FieldSelector fieldSelector)
{
	ChessBoardField* field = &board[fieldSelector.getRow()][fieldSelector.getColumn()];

	if (fieldSelector.getSavedPiece() != NULL)
	{
		fieldSelector.getSavedPiece()->highlightPossibleMoves();
	}
	field->selected();
}
bool ChessBoard::checkIfKingIsInCheck(PLAYER_COLOR color)
{
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 16; ++i)
		{
			if (!pieces[j][i]->isAlive())
				continue;
			std::vector<SimpleChessField> posibleMoves = pieces[j][i]->getPossibleMovesIncludingKing();
			for (auto field : posibleMoves)
			{
				if (field == kings[color]->getSimpleField())
				{
					checkKing(kings[color]);
					return true;
				}
			}

		}

	return false;
}

void ChessBoard::updateCurrentPlayer(bool isChangeNeeded)
{
	if (isChangeNeeded) {
		currPlayer = (currPlayer == WHITE ? BLACK : WHITE);
		disableEnPassantPawns();
		updateCastlings();
		endGame(checkIfGameEnd());
		saveMovement();
	}

}

void ChessBoard::updateCastlings() {
	disableCastlings();
	updateCastlingsFor(currPlayer);
}

void ChessBoard::disableCastlings() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			castling[i][j] = false;
}

void ChessBoard::updateCastlingsFor(PLAYER_COLOR color) {
	if (!kings[color]->isFirstMoveAvaliable())
		return;
	std::vector<SimpleChessField> enemyMoves;

	ChessPiece** enemyPieces = getPieces(color == WHITE ? BLACK : WHITE);
	for (int i = 0; i < 16; ++i) {
		std::vector<SimpleChessField> tmp = enemyPieces[i]->getPossibleMoves();
		enemyMoves.insert(enemyMoves.end(), tmp.begin(), tmp.end());
	}

	bool isKingChecked = isFieldInVector(kings[color]->getSimpleField(), enemyMoves);

	if (isKingChecked)
		return;

	updateCastlingsFor(color, KING_SIDE, enemyMoves);
	updateCastlingsFor(color, QUEEN_SIDE, enemyMoves);
}

void ChessBoard::updateCastlingsFor(PLAYER_COLOR color, CHESS_BOARD_SIDE boardSide, std::vector<SimpleChessField> enemyMoves) {
	if (!rooks[color][boardSide]->isAlive() || !rooks[color][boardSide]->isFirstMoveAvaliable())
		return;

	int direction = (boardSide == QUEEN_SIDE ? -1 : 1);


	SimpleChessField kingField = kings[color]->getSimpleField();

	std::vector<SimpleChessField> fieldsThatKingGoingToPass;
	fieldsThatKingGoingToPass.push_back(kingField.move(0, 1 * direction));
	fieldsThatKingGoingToPass.push_back(kingField.move(0, 2 * direction));

	CHESS_COLUMN rookCol = rooks[color][boardSide]->getCol();

	int numberOfFieldsBetweenKingAndRook = abs(rookCol - kingField.getColumn());
	for (int i = 1; i < numberOfFieldsBetweenKingAndRook; ++i) {
		if (!getField(kingField.move(0, i * direction))->isEmpty())
			return;
	}

	for (auto field : fieldsThatKingGoingToPass) {
		if (isFieldInVector(field, enemyMoves))
			return;
	}

	castling[color][boardSide] = true;
}

bool ChessBoard::isFieldInVector(SimpleChessField field, std::vector<SimpleChessField> vector)
{
	for (int i = 0; i < vector.size(); ++i)
	{
		if (vector[i] == field)
			return true;
	}
	return false;
}

CHESS_GAME_STATE ChessBoard::checkIfGameEnd()
{
	std::vector<SimpleChessField> whiteMoves;
	std::vector<SimpleChessField> blackMoves;
	std::vector<ChessPiece*> aliveBlackPiecesWithoutKing;
	std::vector<ChessPiece*> aliveWhitePiecesWithoutKing;
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 16; ++i)
		{
			if (pieces[j][i]->getColor() == WHITE)
			{
				if (pieces[j][i]->isAlive() && pieces[j][i]->getType() != KING)
					aliveWhitePiecesWithoutKing.push_back(pieces[j][i]);

				std::vector<SimpleChessField> tmp = pieces[j][i]->getPossibleMoves();
				whiteMoves.insert(whiteMoves.end(), tmp.begin(), tmp.end());
			}
			else
			{
				if (pieces[j][i]->isAlive() && pieces[j][i]->getType() != KING)
					aliveBlackPiecesWithoutKing.push_back(pieces[j][i]);

				std::vector<SimpleChessField> tmp = pieces[j][i]->getPossibleMoves();
				blackMoves.insert(blackMoves.end(), tmp.begin(), tmp.end());
			}
		}

	return checkIfGameEnd(EndGameDTO(aliveWhitePiecesWithoutKing, whiteMoves), EndGameDTO(aliveBlackPiecesWithoutKing, blackMoves));
}

CHESS_GAME_STATE ChessBoard::checkIfGameEnd(EndGameDTO white, EndGameDTO black) {
	std::vector<ChessPiece* > aliveWhitePiecesWithoutKing;
	std::vector<SimpleChessField> whiteMoves;
	std::vector<ChessPiece* > aliveBlackPiecesWithoutKing;
	std::vector<SimpleChessField> blackMoves;

	bool isWhiteKingChecked = isFieldInVector(kings[WHITE]->getSimpleField(), blackMoves);
	bool isBlackKingChecked = isFieldInVector(kings[BLACK]->getSimpleField(), whiteMoves);

	if (isWhiteKingChecked && whiteMoves.empty())
		return WINNER_BLACK;
	if (isBlackKingChecked && blackMoves.empty())
		return WINNER_WHITE;

	if (!isWhiteKingChecked && whiteMoves.empty())
		return STALEMATE;
	if (!isBlackKingChecked && blackMoves.empty())
		return STALEMATE;
	if ((checkIfIsOneLightPiece(aliveWhitePiecesWithoutKing) || (checkIfTwoKnights(aliveWhitePiecesWithoutKing) || aliveWhitePiecesWithoutKing.empty()))
		&& (checkIfIsOneLightPiece(aliveBlackPiecesWithoutKing) || checkIfTwoKnights(aliveBlackPiecesWithoutKing) || aliveBlackPiecesWithoutKing.empty()))
		return STALEMATE;


	return CONTINIUE;
}


bool ChessBoard::checkIfIsOneLightPiece(std::vector<ChessPiece*> pieces) {
	return (pieces.size() == 1 && isLight(pieces[0]->getType()));
}

bool ChessBoard::checkIfTwoKnights(std::vector<ChessPiece*> pieces) {
	return (pieces.size() == 2 && pieces[0]->getType() == KNIGHT && pieces[1]->getType() == KNIGHT);
}

int ChessBoard::countHeavyPieces(std::vector<ChessPiece*> pieces) {
	int counter = 0;
	for (auto piece : pieces) {
		if (isHeavy(piece->getType()))
			++counter;
	}

	return counter;
}

int ChessBoard::countLightPieces(std::vector<ChessPiece*> pieces) {
	int counter = 0;
	for (auto piece : pieces) {
		if (isLight(piece->getType()))
			++counter;
	}

	return counter;
}

bool ChessBoard::isHeavy(CHESS_PIECES type) {
	return type == QUEEN || type == ROOK;
}

bool ChessBoard::isLight(CHESS_PIECES type) {
	return type == KNIGHT || type == BISHOP;
}

std::string ChessBoard::endGame(CHESS_GAME_STATE gameState)
{

	std::string status;
	state = gameState;
	switch (gameState)
	{
	case CONTINIUE:
	{
		if (getCurrPlayer() == WHITE)
			status = "RUCH: BIALE";
		else
			status = "RUCH: CZARNE";
		break;
	}
	case WINNER_BLACK:
		status = "MAT! ZWYCIEZCA: CZARNE";
		break;

	case WINNER_WHITE:
		status = "MAT! ZWYCIEZCA: BIALE";
		break;

	case STALEMATE:
		status = "PAT";
		break;

	default:
		break;
	}

	std::cout << status << std::endl;
	return status;

}
CHESS_GAME_STATE ChessBoard::getGameState()
{
	return state;
}
PLAYER_COLOR ChessBoard::getCurrPlayer()
{
	return currPlayer;
}


void ChessBoard::disableEnPassantPawns()
{
	if (enPassantPawns.size() == 0)
		return;

	for (int i = 0; i < enPassantPawns.size(); )
	{
		if (!enPassantPawns[i]->isEnPasantAvailable())
		{
			enPassantPawns[i]->enableEnPasant();
		}
		else
		{
			enPassantPawns[i]->disableEnPasant();
			enPassantPawns.erase(enPassantPawns.begin() + i);
			continue;
		}
		++i;
	}

}
void ChessBoardField::setHighlighted(sf::IntRect rect) {
	frames[HIGHLIGHTED] = rect;
}
void ChessBoardField::setInDanger(sf::IntRect rect) {
	frames[IN_DANGER] = rect;
}
void ChessBoardField::setSelected(sf::IntRect rect)
{
	frames[SELECTED] = rect;
}
void ChessBoardField::setNormal(sf::IntRect rect)
{
	frames[NORMAL] = rect;
}
void ChessBoardField::highlight()
{
	currState = HIGHLIGHTED;
	setSpriteRect();
}
void ChessBoardField::selected()
{
	currState = SELECTED;
	setSpriteRect();
}
void ChessBoardField::stopHighlighting()
{
	currState = NORMAL;
	setSpriteRect();
}

void ChessBoardField::setSpriteRect() {
	sprite->setTextureRect(frames[currState]);
}

void ChessBoardField::inDanger()
{
	currState = IN_DANGER;
	setSpriteRect();
}
bool ChessBoardField::isPossibleToMoveHere(PLAYER_COLOR color)
{
	return isEmpty() || !checkPieceColor(color);
}

bool ChessBoardField::checkPieceColor(PLAYER_COLOR chessColor)
{
	if (isEmpty())
		return false;

	return getPiece()->getColor() == chessColor;
}
void ChessBoardField::prepareSprite()
{
	sprite = new sf::Sprite(*texture);
	stopHighlighting();
}
void ChessBoard::selectField(FieldSelector* fieldSelector)
{
	if (pawnBeingPromoted != nullptr) {
		return;
	}
	ChessBoardField* field = getField(fieldSelector->getColumn(), fieldSelector->getRow());

	if (fieldSelector->isSelected())
	{
		updateCurrentPlayer(fieldSelector->getSavedPiece()->tryToMove(field));
		fieldSelector->unselect();
		return;
	}

	if (!fieldSelector->isSelected())
	{
		if (field->getPiece() != NULL && field->getPiece()->getColor() == currPlayer) {
			fieldSelector->select(field->getPiece());
			return;
		}
		if (field->getPiece() == NULL) {
			return;
		}
	}

}
void ChessBoard::saveMovement() {

	/*

	std::cout << "[" << getPiece()->getTypeName() << "(" << piece->getRowName() << "," << piece->getColumnName() << ") -> " << "(" << field->getRowName() << "," << field->getColumnName() << ")" << "]" << std::endl;
	std::fstream plik;

	plik.open("resources/movements.txt", std::ios::out | std::ios::app);
	if (plik.good() == true)
	{
		plik << "[" << piece->getTypeName() << "(" << piece->getRowName() << "," << piece->getColumnName() << ") -> " << "(" << field.getRowName() << "," << field.getColumnName() << ")" << "]" << std::endl;

		plik.close();
	}*/
}