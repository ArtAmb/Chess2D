#pragma once
#include "ChessEnums.h"
#include "SFML/Graphics.hpp"

class ChessBoard;
class ChessBoardField;
class ChessPiece
{
	CHESS_COLUMN col;
	CHESS_ROW row;
	PLAYER_COLOR chessColor;
	sf::Sprite* sprite;
	ChessBoard* board;


public:
	ChessPiece();
	void init(CHESS_COLUMN, CHESS_ROW, PLAYER_COLOR, ChessBoard*, sf::Sprite*);
	virtual ~ChessPiece();
	void draw(sf::RenderWindow* window);
	sf::Sprite* getSprite();
	void setXY(int x, int y) {
		sprite->setPosition(static_cast<float>(x), static_cast<float>(y));
	}
};

