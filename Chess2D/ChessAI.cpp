#include "ChessAI.h"
#include <vector>
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
	std::vector <std::string> movements;

public:
	PieceWithField(ChessPiece* piece, SimpleChessField field, ChessAIPositionEstimation estimation)
		: piece(piece), field(field), estimation(estimation) {};

	ChessPiece* getPiece() { return piece; };
	SimpleChessField getField() { return field; };
	ChessAIPositionEstimation getEstimation() { return estimation; };	
	std::vector <std::string> getMovements() { return movements; };

	void printf() {
		std::cout << "[" << piece->getType() << "(" << piece->getRow() << "," << piece->getCol() << ") -> " << "(" << field.getRow() << "," << field.getColumn() << ")" << "]" << std::endl;
	}

	void saveMovement() {
		

		std::string movement = "[" + getPiece()->getTypeName() + "(" + piece->getRowName() + "," + piece->getColumnName() + ") -> " + "(" + field.getRowName() + "," + field.getColumnName() + ")" + "]";
		std::cout << movement << std::endl;

		movements.push_back(movement);

		std::cout << "Ostatnie 5 ruchow" << std::endl;
		size_t mSize = movements.size();
		size_t startIt = 0;

		if (mSize >5)
			startIt = mSize - 5;

		for (size_t i = startIt; i < movements.size(); i++)
			std::cout << movements[i] << std::endl;
		
		std::fstream plik;

		plik.open("resources/movements.txt", std::ios::out | std::ios::app);
		if (plik.good() == true)
		{
		plik << movement<< std::endl;

		plik.close();
		}

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
	selectedMove.saveMovement();
	

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
