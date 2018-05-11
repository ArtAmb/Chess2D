#include "ChessAI.h"

ChessAI::~ChessAI()
{
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board)
{
	return ChessAIPositionEstimation();
}


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

};

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board)
{
	std::vector<PieceWithField> allMoves;
	ChessPiece** allPieces = board->getPieces(color);
	for (int i = 0; i < 16; ++i) {
		for (auto field : allPieces[i]->getPossibleMoves()) {
			ChessAIPositionEstimation estimation = estimatePosition(allPieces[i], field, board);
			allMoves.push_back(PieceWithField(allPieces[i], field, estimation));
		}
	}

	int random = rand() % allMoves.size();
	PieceWithField selectedMove =  allMoves[random];
	return ChessAIMove(selectedMove.getPiece(), selectedMove.getField());
}
