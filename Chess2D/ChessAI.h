#pragma once

#include "ChessBoard.h"
#include "ChessAiPositionEstimation.h"
#include "ChessAiMove.h"
#include <unordered_map>

class PieceWithField {
	ChessPiece* piece;
	SimpleChessField field;
	ChessAIPositionEstimation estimation;
	std::vector<std::string> movements;
public:
	PieceWithField(ChessPiece* piece, SimpleChessField field, ChessAIPositionEstimation estimation)
		: piece(piece), field(field), estimation(estimation) {};

	PieceWithField(ChessPiece* piece, SimpleChessField field)
		: piece(piece), field(field){};

	ChessPiece* getPiece() { return piece; };
	SimpleChessField getField() { return field; };
	ChessAIPositionEstimation getEstimation() { return estimation; };
	void setEstimation(ChessAIPositionEstimation estimation) { this->estimation = estimation; }

	void printf() {
		if (piece == nullptr)
			std::cout << "CHESS PIECE IS NULL. MOVE IS NOT POSSIBLE!" << std::endl;
		else
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

class ChessAIMovesDTO {
	EndGameDTO endGameDTO;
	std::vector<PieceWithField> pieceWithFields;
public:
	ChessAIMovesDTO(EndGameDTO endGameDTO, std::vector<PieceWithField> pieceWithFields) : endGameDTO(endGameDTO), pieceWithFields(pieceWithFields) {}
	std::vector<PieceWithField> getPieceWithFields() {
		return pieceWithFields;
	}
	EndGameDTO getEndGameDTO() {
		return endGameDTO;
	}
};

class FieldInfluence {
	float materialDifference;
	int piecesDifference;
public:
	FieldInfluence(float materialDifference, int piecesDifference) : materialDifference(materialDifference), piecesDifference(piecesDifference) {}

	float getMaterialDifference() { return materialDifference; }
	int getPiecesDifference() { return piecesDifference; }
};

class ChessAI
{
	PLAYER_COLOR color;
	LEVEL_OPTION level;
	bool thinking = false;
public:
	ChessAI(PLAYER_COLOR color, LEVEL_OPTION level) : color(color), level(level) {};
	~ChessAI();

	ChessAIPositionEstimation estimatePosition(ChessPiece * piece, SimpleChessField field, ChessBoard * board, std::unordered_map<std::string, std::vector<std::vector<ChessPiece*>>> attackedFields);
	ChessAIPositionEstimation estimatePosition(ChessBoard * board, PLAYER_COLOR color, std::unordered_map<std::string, std::vector<std::vector<ChessPiece*>>> attackedFields);
	std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > findAttackedFields(ChessBoard* board, AllMoves allMoves);

	//ChessAIPositionEstimation estimatePosition(ChessPiece * piece, SimpleChessField field, ChessBoard * board, AllMoves allPossibleMovesOnBoard);
	//ChessAIPositionEstimation estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board);
	ChessAIPositionEstimation estimatePostionForPawnPromotion(ChessBoard * board);
	ChessAIPositionEstimation estimatePostiontionForPawnPromotionType(ChessBoard * board, PAWN_PROMOTION promotionType);
	
	//ChessAIPositionEstimation estimatePosition(ChessBoard * board, PLAYER_COLOR color, AllMoves allPossibleMovesOnBoard);
	//ChessAIPositionEstimation estimatePosition(ChessBoard * board, PLAYER_COLOR color, std::vector<PieceWithField> moves);
	//ChessAIPositionEstimation estimatePosition(ChessBoard * board, PLAYER_COLOR color);
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
	FieldInfluence estimateInfluenceOnField(PLAYER_COLOR myColor, SimpleChessField field, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields);
	float calculateMaterial(std::vector<ChessPiece*> pieces);
	PLAYER_COLOR getEnemyColor();
	PLAYER_COLOR getEnemyColorFor(PLAYER_COLOR color);
	float calculateMaterial(ChessPiece ** pieces);
	float calculateMaterial(ChessPiece * piece);
	ChessAIMovesDTO calculatePossibleMoves(ChessPiece ** pieces);
};

