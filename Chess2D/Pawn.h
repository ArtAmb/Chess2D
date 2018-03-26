#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	Pawn(CHESS_ROW, CHESS_COLUMN, PLAYER_COLOR, ChessBoard*, sf::Sprite*);
	~Pawn();
};

