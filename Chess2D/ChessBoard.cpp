#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "King.h"
#include "PositionTextureConverter.h"
#include "SimpleChessField.h"

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

	if (chessPiece != nullptr)
		delete chessPiece;
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
	prepareBoard();

	for (int i = 0; i < 8; ++i)
	{
		pieces[WHITE][i] = new Pawn(R_2, (CHESS_COLUMN)i, WHITE, this, fieldTexture->getSprite(0, 0));
	}

	for (int i = 0; i < 8; ++i)
	{
		pieces[BLACK][i] = new Pawn(R_7, (CHESS_COLUMN)i, BLACK, this, fieldTexture->getSprite(1, 0));
	}

	pieces[WHITE][8] = new Pawn(R_1, C_C, WHITE, this, fieldTexture->getSprite(0, 1));
	pieces[WHITE][9] = new Pawn(R_1, C_F, WHITE, this, fieldTexture->getSprite(0, 1));

	pieces[BLACK][8] = new Pawn(R_8, C_C, BLACK, this, fieldTexture->getSprite(1, 1));
	pieces[BLACK][9] = new Pawn(R_8, C_F, BLACK, this, fieldTexture->getSprite(1, 1));

	pieces[WHITE][10] = new Pawn(R_1, C_A, WHITE, this, fieldTexture->getSprite(0, 2));
	pieces[WHITE][11] = new Pawn(R_1, C_H, WHITE, this, fieldTexture->getSprite(0, 2));

	pieces[BLACK][10] = new Pawn(R_8, C_A, BLACK, this, fieldTexture->getSprite(1, 2));
	pieces[BLACK][11] = new Pawn(R_8, C_H, BLACK, this, fieldTexture->getSprite(1, 2));

	pieces[WHITE][12] = new Pawn(R_1, C_B, WHITE, this, fieldTexture->getSprite(0, 3));
	pieces[WHITE][13] = new Pawn(R_1, C_G, WHITE, this, fieldTexture->getSprite(0, 3));

	pieces[BLACK][12] = new Pawn(R_8, C_B, BLACK, this, fieldTexture->getSprite(1, 3));
	pieces[BLACK][13] = new Pawn(R_8, C_G, BLACK, this, fieldTexture->getSprite(1, 3));

	pieces[WHITE][14] = new Pawn(R_1, C_D, WHITE, this, fieldTexture->getSprite(0, 4));
	pieces[BLACK][14] = new Pawn(R_8, C_D, BLACK, this, fieldTexture->getSprite(1, 4));

	pieces[WHITE][15] = new King(R_1, C_E, WHITE, this, fieldTexture->getSprite(0, 5));
	pieces[BLACK][15] = new King(R_8, C_E, BLACK, this, fieldTexture->getSprite(1, 5));


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
}

ChessBoard::~ChessBoard()
{
	for (int i = 0; i < 2; ++i)
		for (ChessPiece* piece : pieces[i]) {
			if (piece != nullptr)
				delete piece;
		}
}

void ChessBoard::draw(sf::RenderWindow* window) {

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].draw(window);
		}
	}

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
		endGame(checkIfGameEnd());
	}

}

bool isFieldInVector(SimpleChessField field, std::vector<SimpleChessField> vector)
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
	for (int j = 0; j < 2; ++j)
		for (int i = 0; i < 16; ++i)
		{
			if (pieces[j][i]->getColor() == WHITE)
			{
				std::vector<SimpleChessField> tmp = pieces[j][i]->getPossibleMoves();
				whiteMoves.insert(whiteMoves.end(), tmp.begin(), tmp.end());
			}
			else
			{
				std::vector<SimpleChessField> tmp = pieces[j][i]->getPossibleMoves();
				blackMoves.insert(blackMoves.end(), tmp.begin(), tmp.end());
			}
		}

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

	return CONTINIUE;
}

void ChessBoard::endGame(CHESS_GAME_STATE gameState)
{
	state = gameState;
	switch (gameState)
	{
	case WINNER_BLACK:

		std::cout << "CHECKMATE!!! WINNER: BLACK" << std::endl;
		break;

	case WINNER_WHITE:

		std::cout << "CHECKMATE!!! WINNER: WHITE" << std::endl;
		break;

	case STALEMATE:

		std::cout << "STALEMATE!" << std::endl;
		break;

	default:

		break;
	}
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
