#pragma once
#include <SFML\Graphics.hpp>
#include "PositionTextureConverter.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "GraphicEngine.h"
#include "ChessPiece.h"
#include "King.h"
#include "Pawn.h"
#include "FieldSelector.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

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
	enum TransformationButtonFieldState { DISABLED, SELECTED};
	
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

class ChessBoard {

	PLAYER_COLOR currPlayer;
	ChessPiece* pieces[2][16];
	
	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);
	TextureResource* transformationButtonTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::TRANSFORMATION_PAWN_BUTTON);
	int TRANSFORMATION_BUTTON_FIELD = transformationButtonTexture->getConverter()->getElementWidth();


	King* kings[2];
	King* checkedKing = NULL;
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
	
public:
	
	ChessBoard();
	ChessBoard(ChessBoard * board);
	void initEnPasantPawns(std::vector<Pawn*> pawns);
	ChessPiece * createChessPiece(ChessPiece * piece);
	~ChessBoard();
	void prepareBoard();
	void draw(sf::RenderWindow* window);
	void updateCurrentPlayer(bool isChangeNeeded);
	CHESS_GAME_STATE checkIfGameEnd();
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
	void promotePawnTo(PAWN_PROMOTION);

	void activatePromotionButtons(PLAYER_COLOR);
	void deactivatePromotionButtons();
	
	PawnTransformationButton* getPawnTransformationButton(PLAYER_COLOR color, PAWN_PROMOTION pawnType) {
		return pawnTransformationButtons[color][pawnType];
	}
	
	void setKing(King * king);

	void setPawnBeingPromoted(Pawn* pawn) { this->pawnBeingPromoted = pawn; }
	Pawn* getPawnBeingPromoted() { return pawnBeingPromoted; }
	ChessBoardField* getField(SimpleChessField field);
	ChessBoardField* getField(int col, int row);
	ChessBoardField* getField(CHESS_COLUMN c, CHESS_ROW r);
	ChessPiece** getPieces(PLAYER_COLOR color) { return pieces[color]; }

	ChessPiece* getMyChessPiece(ChessPiece* chessPieceFromTemporaryBoard);
	ChessBoard* toTemporaryBoard();


	void printfBoard(std::string comment);
};
