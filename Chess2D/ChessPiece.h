#pragma once
#include "ChessEnums.h"
#include "SFML/Graphics.hpp"
#include "SimpleChessField.h"

class ChessBoard;
class ChessBoardField;
class ChessPiece
{
protected:
	CHESS_COLUMN col;
	CHESS_ROW row;

	CHESS_COLUMN newColumn;
	CHESS_ROW newRow;

	PLAYER_COLOR chessColor;
	sf::Sprite* sprite;
	ChessBoard* board;
	bool alive = true;
	std::vector<SimpleChessField> possibleMoves;
	bool beingProcessed = false;
	
	void fillPossibleMovesFieldSeries(int deltaRow, int deltaColumn);
	void fillPossibleMovesForRook();
	void fillPossibleMovesForBishop();
	void addToPossibleMoves(ChessBoardField* field);
	void resetPossibleMoves();
	void tryToFillPossibleMoves();
	void highlightField(SimpleChessField field);

	virtual void move(ChessBoardField* field);
	bool isBeingProcessed() { return beingProcessed; }
	void startProcessing() { beingProcessed = true; }
	void stopProcessing() { beingProcessed = false; }
	SimpleChessField getNewField() { return SimpleChessField(newRow, newColumn); }
	void setNewField(CHESS_ROW r, CHESS_COLUMN col) { newRow = r; newColumn = col; }

	void stopProcesing(ChessBoardField* field, ChessPiece* tmpPiece);

public:
	ChessPiece();
	void init(CHESS_COLUMN, CHESS_ROW, PLAYER_COLOR, ChessBoard*, sf::Sprite*);
	virtual ~ChessPiece();
	void draw(sf::RenderWindow* window);
	sf::Sprite* getSprite();
	void setXY(int x, int y) {
		sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
	}

	PLAYER_COLOR getColor();
	void reset();
	void highlightPossibleMoves();
	bool isAlive() {
		return alive;
	};
	void die() { alive = false; }

	virtual void fillPossibleMoves() = 0;
	std::vector<SimpleChessField> getPossibleMovesIncludingKing();

	bool checkNextMove(SimpleChessField field);
	bool tryToMove(ChessBoardField * field);
	SimpleChessField getSimpleField();
	void setAlive(bool alive) { this->alive = alive; }
	std::vector<SimpleChessField> getPossibleMoves();
	
};

