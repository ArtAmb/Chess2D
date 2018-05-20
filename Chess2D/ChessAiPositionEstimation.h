#pragma once
#include "ChessEnums.h"
#include "iostream"

class ChessAIPositionEstimation {
	double estimation;
	int posibleMoves;
	PAWN_PROMOTION forPromotionPawn;
public:
	ChessAIPositionEstimation() { estimation = 0.0; posibleMoves = 0; };
	ChessAIPositionEstimation(double estimation, int posibleMoves) {
		this->estimation = estimation;
		this->posibleMoves = posibleMoves;
	}
	double getEstimation() { return estimation; }
	int getAllPosibleMoves() { return posibleMoves; }

	PAWN_PROMOTION getForPromotionPawn() {
		return forPromotionPawn;
	}

	void setForPromotionPawn(PAWN_PROMOTION forPawnPromotion) {
		this->forPromotionPawn = forPawnPromotion;
	}

	bool operator <(ChessAIPositionEstimation entimationObject) {
		if (estimation == entimationObject.getEstimation())
			return posibleMoves < entimationObject.getAllPosibleMoves();
		return estimation < entimationObject.getEstimation();
		
	}
	bool operator >(ChessAIPositionEstimation entimationObject) {
		return ((*this) >= entimationObject) && ((*this) != entimationObject);
	}
	bool operator <=(ChessAIPositionEstimation entimationObject) {
		return !((*this) > entimationObject);
	}
	bool operator >=(ChessAIPositionEstimation entimationObject) {
		return !((*this) < entimationObject);
	}
	bool operator ==(ChessAIPositionEstimation entimationObject) {
		return (estimation == entimationObject.getEstimation()) && (posibleMoves == entimationObject.getAllPosibleMoves());
	}
	bool operator !=(ChessAIPositionEstimation entimationObject) {
		return !((*this) == entimationObject);
	}
	ChessAIPositionEstimation operator-(ChessAIPositionEstimation entimationObject) {
		ChessAIPositionEstimation result;
		result.estimation = this->estimation - entimationObject.getEstimation();
		result.posibleMoves = this->posibleMoves - entimationObject.getAllPosibleMoves();
		result.forPromotionPawn = this->forPromotionPawn;
		return result;
	}
	ChessAIPositionEstimation operator+(ChessAIPositionEstimation entimationObject) {
		ChessAIPositionEstimation result;
		result.estimation = this->estimation + entimationObject.getEstimation();
		result.posibleMoves = this->posibleMoves + entimationObject.getAllPosibleMoves();
		result.forPromotionPawn = this->forPromotionPawn;
		return result;
	}
	ChessAIPositionEstimation operator-=(ChessAIPositionEstimation entimationObject) {
		this->estimation -= entimationObject.getEstimation();
		this->posibleMoves -= entimationObject.getAllPosibleMoves();
		return (*this);
	}
	ChessAIPositionEstimation operator+=(ChessAIPositionEstimation entimationObject) {
		this->estimation += entimationObject.getEstimation();
		this->posibleMoves += entimationObject.getAllPosibleMoves();
		return (*this);
	}

	void printf() {
		std::cout << "estimation == " << estimation << std::endl;
		std::cout << "moves == " << posibleMoves<< std::endl;
	}
};