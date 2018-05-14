#include "ChessAI.h"

ChessAI::~ChessAI()
{
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board)
{
	
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	tmpBoard->getMyChessPiece(piece)->tryToMove(field);
	ChessAIPositionEstimation estimation = estimatePosition(tmpBoard);
	delete tmpBoard;
	return estimation;

	//return estimatePosition(board);
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessBoard* board) {
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

	void printf() {
		std::cout << "[" << piece->getType() << "(" << piece->getRow() << "," << piece->getCol() << ") -> " << "(" << field.getRow() << "," << field.getColumn() << ")" << "]" << std::endl;
	}
};

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board)
{
	board->printfBoard(" REAL ");
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	tmpBoard->printfBoard(" TEMP ");
	std::vector<PieceWithField> allMoves;
	ChessPiece** allPieces = tmpBoard->getPieces(color);
	for (int i = 0; i < 16; ++i) {
		for (auto field : allPieces[i]->getPossibleMoves()) {
			ChessAIPositionEstimation estimation = estimatePosition(allPieces[i], field, tmpBoard);
			allMoves.push_back(PieceWithField(allPieces[i], field, estimation));
		}
	}
	
	int random = rand() % allMoves.size();
	PieceWithField selectedMove = allMoves[random];
	std::cout << "SELECTED MOVE: ";
	selectedMove.printf();

	board->printfBoard(" REAL ?? again ");
	ChessPiece* realPiece = board->getMyChessPiece(selectedMove.getPiece());
	std::cout << "REAL PIECE: ";
	realPiece->printf();

	delete tmpBoard;
	return ChessAIMove(realPiece, selectedMove.getField());
	

	/*
	std::vector<PieceWithField> allMoves;
	ChessPiece** allPieces = board->getPieces(color);
	for (int i = 0; i < 16; ++i) {
		for (auto field : allPieces[i]->getPossibleMoves()) {
			ChessAIPositionEstimation estimation = estimatePosition(allPieces[i], field, board);
			allMoves.push_back(PieceWithField(allPieces[i], field, estimation));
		}
	}

	int random = rand() % allMoves.size();
	PieceWithField selectedMove = allMoves[random];


	return ChessAIMove(selectedMove.getPiece(), selectedMove.getField());*/
}
