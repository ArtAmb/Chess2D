#pragma once

#include "ChessBoard.h"
#include "ChessAiPositionEstimation.h"
#include "ChessAiMove.h"

class PieceWithField {
	ChessPiece* piece;
	SimpleChessField field;
	ChessAIPositionEstimation estimation;
public:
	PieceWithField(ChessPiece* piece, SimpleChessField field, ChessAIPositionEstimation estimation)
		: piece(piece), field(field), estimation(estimation) {};

	ChessPiece* getPiece() { return piece; };
	SimpleChessField getField() { return field; };
	ChessAIPositionEstimation getEstimation() { return estimation; };
	void setEstimation(ChessAIPositionEstimation estimation) { this->estimation = estimation; }

	void printf() {
		std::cout << "[" << piece->getType() << "(" << piece->getRow() << "," << piece->getCol() << ") -> " << "(" << field.getRow() << "," << field.getColumn() << ")" << "] " << estimation.getEstimation() << std::endl;
	}


	bool operator <(PieceWithField object) {
		return estimation < object.getEstimation();
	}
	bool operator >(PieceWithField object) {
		return estimation > object.getEstimation();
	}
	bool operator <=(PieceWithField object) {
		return estimation <= object.getEstimation();
	}
	bool operator >=(PieceWithField object) {
		return estimation >= object.getEstimation();
	}
	bool operator ==(PieceWithField object) {
		return estimation == object.getEstimation();
	}
	static bool greater(PieceWithField object, PieceWithField object2) {
		return object > object2;
	}
};

class ChessAI
{
	PLAYER_COLOR color;
	LEVEL_OPTION level;
	bool thinking = false;
public:
	ChessAI(PLAYER_COLOR color, LEVEL_OPTION level) : color(color), level(level) {};
	~ChessAI();

	ChessAIPositionEstimation estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board);
	ChessAIPositionEstimation estimatePostionForPawnPromotion(ChessBoard * board);
	ChessAIPositionEstimation estimatePostiontionForPawnPromotionType(ChessBoard * board, PAWN_PROMOTION promotionType);
	ChessAIPositionEstimation estimatePosition(ChessBoard * board, PLAYER_COLOR color);
	ChessAIPositionEstimation estimateMove(PieceWithField pieceWithField, ChessBoard * board, int howDeep);
	ChessAIMove calculateNextMove(ChessBoard*);
	ChessAIMove calculateNextMove(ChessBoard * board, PLAYER_COLOR color);
	ChessAIMove calculateNextMove(ChessBoard * board, PLAYER_COLOR color, int depthLevel);

	PieceWithField findBestMove(std::vector<PieceWithField> allMoves);
	ChessAIPositionEstimation findBestEstimation(std::vector<ChessAIPositionEstimation> estimations);
	std::vector<PieceWithField> findBestMoves(std::vector<PieceWithField> allMoves, int howMany);
	PLAYER_COLOR getColor() { return color; }

	bool isThinking() { return thinking; }
	void startThinking() { thinking = true; }
	void stopThinking() { thinking = false; }
	PLAYER_COLOR getEnemyColor();
	PLAYER_COLOR getEnemyColorFor(PLAYER_COLOR color);
	float calculateMaterial(ChessPiece ** pieces);
	int calculatePossibleMoves(ChessPiece ** pieces);
	float calculateMaterial(ChessPiece * piece);
};

