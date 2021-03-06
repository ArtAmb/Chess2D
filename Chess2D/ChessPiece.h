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

	CHESS_PIECES type;

	PLAYER_COLOR chessColor;
	sf::Sprite* sprite;
	ChessBoard* board;
	bool alive = true;
	bool colorChanged = false;
	std::vector<SimpleChessField> possibleMoves;
	bool beingProcessed = false;
	
	void fillPossibleMovesFieldSeries(int deltaRow, int deltaColumn);
	std::vector<SimpleChessField> getAttackedFieldSeries(int deltaRow, int deltaColumn);
	void fillPossibleMovesForRook();
	void fillPossibleMovesForBishop();
	std::vector<SimpleChessField> getAttackedFieldsByRook();
	std::vector<SimpleChessField> getAttackedFieldsByBishop();
	void addToPossibleMoves(ChessBoardField* field);
	void resetPossibleMoves();
	void tryToFillPossibleMoves();
	void highlightField(SimpleChessField field);

	virtual void move(ChessBoardField* field);
	
	SimpleChessField getNewField() { return SimpleChessField(newRow, newColumn); }
	void setNewField(CHESS_ROW r, CHESS_COLUMN col) { newRow = r; newColumn = col; }

	void stopProcesing(ChessBoardField* field, ChessPiece* tmpPiece);

public:
	ChessPiece();
	void init(CHESS_COLUMN, CHESS_ROW, PLAYER_COLOR, ChessBoard*, sf::Sprite*);
	void init(CHESS_COLUMN col, CHESS_ROW row, PLAYER_COLOR color, ChessBoard * board, bool setOnBoard);
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
	void die();

	virtual void fillPossibleMoves() = 0;
	std::vector<SimpleChessField> getPossibleMovesIncludingKing();

	bool checkNextMove(SimpleChessField field);
	bool tryToMove(ChessBoardField * field);
	bool tryToMove(SimpleChessField simpleField);
	SimpleChessField getSimpleField();
	void setAlive(bool alive) { this->alive = alive; }
	std::vector<SimpleChessField> getPossibleMoves();
	CHESS_ROW getRow() { return row; }
	CHESS_COLUMN getCol() { return col; }
	CHESS_PIECES getType() { return type; }

	std::string getTypeName();
	std::string getRowName();
	std::string getColumnName();

	bool isBeingProcessed() { return beingProcessed; }
	void startProcessing() { beingProcessed = true; }
	void stopProcessing() { beingProcessed = false; }

	void printf();
	void doCastlingOnField(SimpleChessField field);
	void changeColor(PLAYER_COLOR color) {
		this->chessColor = color;
		colorChanged = true;
	}
	bool isColorChanged() { return colorChanged; }

	void initColorChange(bool isColorChanged) { this->colorChanged = isColorChanged; }
	virtual std::vector<SimpleChessField> getAttackedFields() = 0;

	std::vector<SimpleChessField> tryToGetAttackedFields();
};

