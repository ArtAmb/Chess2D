#pragma once

#include "ChessBoard.h"
#include "ChessAiPositionEstimation.h"
#include "ChessAiMove.h"
#include "vector"
#include <map>

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
		std::cout << "[" << piece->getType() << "(" << piece->getRow() << "," << piece->getCol() << ") -> " << "(" << field.getRow() << "," << field.getColumn() << ")" << "] " << estimation.getEstimation() << std::endl;
	}


	void saveMovement() {


		std::string movement = "[" + getPiece()->getTypeName() + "(" + piece->getRowName() + "," + piece->getColumnName() + ") -> " + "(" + field.getRowName() + "," + field.getColumnName() + ")" + "]";
		std::cout << movement << std::endl;

		movements.push_back(movement);

		std::cout << "Ostatnie 5 ruchow" << std::endl;
		size_t mSize = movements.size();
		size_t startIt = 0;

		if (mSize > 5)
			startIt = mSize - 5;

		for (size_t i = startIt; i < movements.size(); i++)
			std::cout << movements[i] << std::endl;

		std::fstream plik;

		plik.open("resources/movements.txt", std::ios::out | std::ios::app);
		if (plik.good() == true)
		{
			plik << movement << std::endl;

			plik.close();
		}

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
	std::map<SimpleChessField, std::vector<ChessPiece* >> findAttackedFields(ChessBoard * board, std::vector<PieceWithField> moves);
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
	float calculateMaterial(ChessPiece * piece);
	ChessAIMovesDTO calculatePossibleMoves(ChessPiece ** pieces);
};

