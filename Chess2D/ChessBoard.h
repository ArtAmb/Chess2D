#pragma once
#include <SFML\Graphics.hpp>
#include "PositionTextureConverter.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "GraphicEngine.h"
#include "ChessPiece.h"
#include "King.h"
#include "Rook.h"
#include "Pawn.h"
#include "FieldSelector.h"
#include "ChessAiMove.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <unordered_map>

class ChessBoardField {
private:
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;
	ChessPiece* chessPiece = nullptr;
	int height, width;
	enum FieldState { NORMAL, SELECTED, HIGHLIGHTED, IN_DANGER };
	FieldState currState = NORMAL;
	sf::IntRect frames[4];
	CHESS_ROW row;
	CHESS_COLUMN column;

public:
	ChessBoardField() {}
	~ChessBoardField();
	ChessBoardField(CHESS_ROW x, CHESS_COLUMN y) {
		this->row = x;
		this->column = y;
	}
	void setXY(int x, int y);
	void draw(sf::RenderWindow* mainWindow);
	void setSprite(sf::Sprite* sprite);
	void setTexture(sf::Texture* sprite);
	bool isEmpty();
	void empty();

	bool contains(sf::Vector2f);

	ChessPiece* getPiece();
	void setPiece(ChessPiece* piece);
	SimpleChessField toSimpleField() { return SimpleChessField(row, column); }

	void setHighlighted(sf::IntRect);
	void setInDanger(sf::IntRect);
	void setSelected(sf::IntRect);
	void setNormal(sf::IntRect);

	void highlight();
	void selected();
	void stopHighlighting();
	void setSpriteRect();
	void inDanger();

	bool isPossibleToMoveHere(PLAYER_COLOR color);
	bool checkPieceColor(PLAYER_COLOR chessColor);

	void prepareSprite();
	CHESS_ROW getRow() { return row; }
	CHESS_COLUMN getColumn() { return column; }
};

class PawnTransformationButton {
	sf::Texture* texture = nullptr;
	sf::Sprite* sprite = nullptr;
	sf::IntRect frames[2];
	bool active = false;
	enum TransformationButtonFieldState { DISABLED, SELECTED };

	PLAYER_COLOR color;
	PAWN_PROMOTION pawnPromotionType;

public:
	bool contains(sf::Vector2f point) {
		return sprite->getGlobalBounds().contains(point);
	}

	PawnTransformationButton(sf::Texture* texture) {
		this->texture = texture;
		sprite = new sf::Sprite(*texture);
	}
	void setActive(bool active) { this->active = active; }
	bool isActive() { return active; }
	void setXY(int x, int y) {
		sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
	}
	void setFrames(sf::IntRect selected, sf::IntRect disabled, PLAYER_COLOR color, PAWN_PROMOTION pawnPromotionType) {
		frames[DISABLED] = disabled;
		frames[SELECTED] = selected;

		this->color = color;
		this->pawnPromotionType = pawnPromotionType;

		this->selected();
	}

	void setType(TransformationButtonFieldState state) {
		sprite->setTextureRect(frames[state]);
	}

	void selected() {
		if (isActive())
			setType(SELECTED);
	}

	void disabled() {
		setType(DISABLED);
	}

	void draw(sf::RenderWindow* mainWindow) {
		mainWindow->draw(*sprite);
	}

	PLAYER_COLOR getPawnColor() { return color; }
	PAWN_PROMOTION getPawnPromotionType() { return pawnPromotionType; }
};

class EndGameDTO {
	std::vector<ChessPiece* > alivePiecesWithoutKing;
	std::vector<SimpleChessField> possibleMoves;

public:
	EndGameDTO(std::vector<ChessPiece* > alivePiecesWithoutKing, std::vector<SimpleChessField> possibleMoves)
		: alivePiecesWithoutKing(alivePiecesWithoutKing), possibleMoves(possibleMoves) {};

	void setAlivePiecesWithoutKing(std::vector<ChessPiece* > alivePiecesWithoutKing) {
		this->alivePiecesWithoutKing = alivePiecesWithoutKing;
	}
	void setPossibleMoves(std::vector<SimpleChessField> possibleMoves) {
		this->possibleMoves = possibleMoves;
	}

	std::vector<ChessPiece* > getAlivePiecesWithoutKing() {
		return alivePiecesWithoutKing;
	}
	std::vector<SimpleChessField> getPossibleMoves() {
		return possibleMoves;
	}
};

class PieceMove {
	ChessPiece* piece;
	SimpleChessField field;

public:
	PieceMove(ChessPiece* piece, SimpleChessField field)
		: piece(piece), field(field) {};

	ChessPiece* getPiece() { return piece; };
	SimpleChessField getField() { return field; };
};

class AllMoves {
	std::vector<PieceMove> blackMoves;
	std::vector<PieceMove> whiteMoves;

public:
	AllMoves() {}
	AllMoves(std::vector<PieceMove> blackMoves, std::vector<PieceMove> whiteMoves) : blackMoves(blackMoves), whiteMoves(whiteMoves) {};

	std::vector<PieceMove> getBlackMoves() { return blackMoves; }
	std::vector<PieceMove> getWhiteMoves() { return whiteMoves; }
};

class ChessBoard {

	PLAYER_COLOR currPlayer;
	ChessPiece* pieces[2][16];

	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);
	TextureResource* transformationButtonTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::TRANSFORMATION_PAWN_BUTTON);
	int TRANSFORMATION_BUTTON_FIELD = transformationButtonTexture->getConverter()->getElementWidth();

	King* kings[2];
	//King* checkedKing = NULL;

	Rook* rooks[2][2];
	bool castling[2][2];

	std::vector<Pawn*> enPassantPawns;
	Pawn* pawnBeingPromoted = nullptr;
	CHESS_GAME_STATE state = CONTINIUE;
	PawnTransformationButton* pawnTransformationButtons[2][4];

	int height, width;
	const static int BOARD_SIZE = 8;
	ChessBoardField board[BOARD_SIZE][BOARD_SIZE];
	sf::IntRect getWhiteFieldSprite();
	sf::IntRect getBlackFieldSprite();
	void checkKing(King* king);
	CHESS_BOARD_TYPE chessBoardType;

public:

	ChessBoard();
	ChessBoard(ChessBoard * board);
	void initEnPasantPawns(std::vector<Pawn*> pawns);
	void initCastlings();
	ChessPiece * createChessPiece(ChessPiece * piece);
	~ChessBoard();
	void prepareBoard();
	void draw(sf::RenderWindow* window);
	void updateCurrentPlayer(bool isChangeNeeded);
	void updateCastlings();
	void disableCastlings();
	void updateCastlingsFor(PLAYER_COLOR color);
	void updateCastlingsFor(PLAYER_COLOR color, CHESS_BOARD_SIDE boardSide, std::vector<SimpleChessField> enemyMoves);
	bool isFieldInVector(SimpleChessField field, std::vector<SimpleChessField> vector);
	CHESS_GAME_STATE checkIfGameEnd();
	CHESS_GAME_STATE checkIfGameEnd(EndGameDTO white, EndGameDTO black);
	bool checkIfIsOneLightPiece(std::vector<ChessPiece*> pieces);
	bool checkIfTwoKnights(std::vector<ChessPiece*> pieces);
	int countHeavyPieces(std::vector<ChessPiece*> pieces);
	int countLightPieces(std::vector<ChessPiece*> pieces);
	bool isHeavy(CHESS_PIECES type);
	bool isLight(CHESS_PIECES type);
	std::string endGame(CHESS_GAME_STATE gameState);
	CHESS_GAME_STATE getGameState();
	PLAYER_COLOR getCurrPlayer();
	void disableEnPassantPawns();
	void selectField(FieldSelector* fieldSelector);
	void saveMovement();
	void highlightFields(FieldSelector fieldSelector);
	bool checkIfKingIsInCheck(PLAYER_COLOR color);
	void unlightAllFields();
	void addEnPassantPawns(Pawn* pawn);
	void tryToKillEnPassantPawn(SimpleChessField field);
	void loadSprites();
	void promotePawnTo(PAWN_PROMOTION * pawnPromotion);
	void promotePawnTo(PAWN_PROMOTION);
	void makeMoveAndUpdateCurrentPlayer(ChessAIMove chessAIMove);

	void realPromotePawnTo(PAWN_PROMOTION pawnPromotion);

	void simulatePromotePawnTo(PAWN_PROMOTION pawnPromotion);

	void activatePromotionButtons(PLAYER_COLOR);
	void deactivatePromotionButtons();

	PawnTransformationButton* getPawnTransformationButton(PLAYER_COLOR color, PAWN_PROMOTION pawnType) {
		return pawnTransformationButtons[color][pawnType];
	}


	AllMoves getAllPossibleMoves();
	void setKing(King * king);

	void setPawnBeingPromoted(Pawn* pawn) { this->pawnBeingPromoted = pawn; }
	Pawn* getPawnBeingPromoted() { return pawnBeingPromoted; }
	ChessBoardField* getField(SimpleChessField field);
	ChessBoardField* getField(int col, int row);
	ChessBoardField* getField(CHESS_COLUMN c, CHESS_ROW r);
	ChessPiece** getPieces(PLAYER_COLOR color) { return pieces[color]; }

	ChessPiece* getMyChessPiece(ChessPiece* chessPieceFromTemporaryBoard);
	ChessBoard* toTemporaryBoard();
	bool isPawnBeingPromoted();

	bool isCastlingPossible(PLAYER_COLOR color, CHESS_BOARD_SIDE boardSide) {
		return castling[color][boardSide];;
	}

	Rook* getRook(PLAYER_COLOR color, CHESS_BOARD_SIDE side) {
		return rooks[color][side];
	}
	std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > findAttackedFields();

	std::unordered_map<std::string, std::vector<std::vector<ChessPiece*>>> findAttackedFields(AllMoves allMoves);

	void printfBoard(std::string comment);
};
