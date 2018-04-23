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

class ChessBoard {

	PLAYER_COLOR currPlayer;
	ChessPiece* pieces[2][16];
	
	TextureResource* fieldTexture= ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);

	King* kings[2];
	King* checkedKing = NULL;
	std::vector<Pawn*> enPassantPawns;
	CHESS_GAME_STATE state = CONTINIUE;


	int height, width;
	const static int BOARD_SIZE = 8;
	ChessBoardField board[BOARD_SIZE][BOARD_SIZE];
	sf::IntRect getWhiteFieldSprite();
	sf::IntRect getBlackFieldSprite();
	void checkKing(King* king);
public:

	

	ChessBoard();
	void prepareBoard();
		~ChessBoard();
	void draw(sf::RenderWindow* window);
	void updateCurrentPlayer(bool isChangeNeeded);
	CHESS_GAME_STATE checkIfGameEnd();
	void endGame(CHESS_GAME_STATE gameState);
	CHESS_GAME_STATE getGameState();
	PLAYER_COLOR getCurrPlayer();
	void disableEnPassantPawns();
	void selectField(FieldSelector* fieldSelector);
	void highlightFields(FieldSelector fieldSelector);
	bool checkIfKingIsInCheck(PLAYER_COLOR color);
	void unlightAllFields();
	void addEnPassantPawns(Pawn* pawn);
	void tryToKillEnPassantPawn(SimpleChessField field);
	void loadSprites();

	void setKing(King * king);

	ChessBoardField* getField(SimpleChessField field);
	ChessBoardField* getField(int col, int row);
	ChessBoardField* getField(CHESS_COLUMN c, CHESS_ROW r);
};
