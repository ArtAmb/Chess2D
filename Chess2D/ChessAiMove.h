#pragma once
#include "ChessAiPositionEstimation.h"
#include "ChessPiece.h"
#include "ChessEnums.h"
#include "SimpleChessField.h"

class ChessAIMove {
	ChessPiece* piece = nullptr;
	CHESS_ROW row;
	CHESS_COLUMN column;
	PAWN_PROMOTION pawnPromotionType;
	ChessAIPositionEstimation estimation;
public:
	ChessAIMove() {}
	ChessAIMove(ChessPiece* piece, SimpleChessField field) : piece(piece), row(field.getRow()), column(field.getColumn()) {};
	ChessAIMove(ChessPiece* piece, SimpleChessField field, PAWN_PROMOTION pawnPromotionType, ChessAIPositionEstimation estimation ) : piece(piece), row(field.getRow()), column(field.getColumn()), pawnPromotionType(pawnPromotionType), estimation(estimation) {};
	SimpleChessField getField() { return SimpleChessField(row, column); }
	ChessPiece* getPiece() { return piece; }
	void setPawnPromotionType(PAWN_PROMOTION pawnPromotionType) { this->pawnPromotionType = pawnPromotionType; };
	PAWN_PROMOTION getPawnPromotionType() { return pawnPromotionType; }
	ChessAIPositionEstimation getEstimation() { return estimation; }
	void setEstimation(ChessAIPositionEstimation estimation) { this->estimation = estimation; }
};
