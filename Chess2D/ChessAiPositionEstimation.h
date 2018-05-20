#pragma once
#include "ChessEnums.h"
#include "iostream"

class ChessAIPositionEstimation {
	double estimation;
	PAWN_PROMOTION forPromotionPawn;
public:
	ChessAIPositionEstimation() { estimation = 0.0; };
	ChessAIPositionEstimation(double estimation) {
		this->estimation = estimation;
	}
	double getEstimation() { return estimation; }

	PAWN_PROMOTION getForPromotionPawn() {
		return forPromotionPawn;
	}

	void setForPromotionPawn(PAWN_PROMOTION forPawnPromotion) {
		this->forPromotionPawn = forPawnPromotion;
	}

	bool operator <(ChessAIPositionEstimation entimationObject) {
		return estimation < entimationObject.getEstimation();
	}
	bool operator >(ChessAIPositionEstimation entimationObject) {
		return estimation > entimationObject.getEstimation();
	}
	bool operator <=(ChessAIPositionEstimation entimationObject) {
		return estimation <= entimationObject.getEstimation();
	}
	bool operator >=(ChessAIPositionEstimation entimationObject) {
		return estimation >= entimationObject.getEstimation();
	}
	bool operator ==(ChessAIPositionEstimation entimationObject) {
		return estimation == entimationObject.getEstimation();
	}

	ChessAIPositionEstimation operator-(ChessAIPositionEstimation entimationObject) {
		ChessAIPositionEstimation result;
		result.estimation = this->estimation - entimationObject.getEstimation();
		result.forPromotionPawn = this->forPromotionPawn;
		return result;
	}
	ChessAIPositionEstimation operator+(ChessAIPositionEstimation entimationObject) {
		ChessAIPositionEstimation result;
		result.estimation = this->estimation + entimationObject.getEstimation();
		result.forPromotionPawn = this->forPromotionPawn;
		return result;
	}
	ChessAIPositionEstimation operator-=(ChessAIPositionEstimation entimationObject) {
		this->estimation -= entimationObject.getEstimation();
		return (*this);
	}
	ChessAIPositionEstimation operator+=(ChessAIPositionEstimation entimationObject) {
		this->estimation += entimationObject.getEstimation();
		return (*this);
	}

	void printf() {
		std::cout << "estimation == " << estimation << std::endl;
	}
};