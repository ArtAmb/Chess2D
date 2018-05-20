#include "ChessAI.h"
#include <algorithm>   

ChessAI::~ChessAI()
{
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board)
{
	ChessAIPositionEstimation estimation;
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	tmpBoard->getMyChessPiece(piece)->tryToMove(field);

	if (tmpBoard->isPawnBeingPromoted()) {
		estimation = estimatePostionForPawnPromotion(tmpBoard);
	}
	else {
		estimation = estimatePosition(tmpBoard, piece->getColor());
	}

	
	delete tmpBoard;
	return estimation;
}

ChessAIPositionEstimation ChessAI::estimatePostionForPawnPromotion(ChessBoard* board) {

	std::vector<ChessAIPositionEstimation> promotionEstimations;

	promotionEstimations.push_back(estimatePostiontionForPawnPromotionType(board, PROM_QUEEN));
	promotionEstimations.push_back(estimatePostiontionForPawnPromotionType(board, PROM_BISHOP));
	promotionEstimations.push_back(estimatePostiontionForPawnPromotionType(board, PROM_KNIGHT));
	promotionEstimations.push_back(estimatePostiontionForPawnPromotionType(board, PROM_ROOK));

	ChessAIPositionEstimation bestEstimation = findBestEstimation(promotionEstimations);

	return bestEstimation;
}

ChessAIPositionEstimation ChessAI::estimatePostiontionForPawnPromotionType(ChessBoard* board, PAWN_PROMOTION promotionType) {
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	PLAYER_COLOR playerColor = board->getPawnBeingPromoted()->getColor();
	board->promotePawnTo(PROM_QUEEN);
	ChessAIPositionEstimation estimation = estimatePosition(board, playerColor);
	estimation.setForPromotionPawn(promotionType);
	delete tmpBoard;

	return estimation;
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessBoard* board, PLAYER_COLOR color) {
	ChessPiece** myPieces = board->getPieces(color);
	ChessPiece** enemyPieces = board->getPieces(getEnemyColorFor(color));

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float estimation = myMaterial - enemyMaterial;
	
	int myPossibleMoves = calculatePossibleMoves(myPieces);
	int enemyPossibleMoves = calculatePossibleMoves(enemyPieces);

	int possibleMoves = myPossibleMoves - enemyPossibleMoves;

	return ChessAIPositionEstimation(estimation, possibleMoves);
}

PLAYER_COLOR ChessAI::getEnemyColor() {
	return getEnemyColorFor(color);
}

PLAYER_COLOR ChessAI::getEnemyColorFor(PLAYER_COLOR color) {
	return color == WHITE ? BLACK : WHITE;
}

float ChessAI::calculateMaterial(ChessPiece** pieces) {
	float result = 0;

	for (int i = 0; i < 16; ++i) {
		if (pieces[i]->isAlive()) {
			result += calculateMaterial(pieces[i]);
		}
	}

	return result;
}

int ChessAI::calculatePossibleMoves(ChessPiece** pieces) {
	int result = 0;

	for (int i = 0; i < 16; ++i) {
		if (pieces[i]->isAlive()) {
			result += pieces[i]->getPossibleMoves().size();
		}
	}

	return result;
}

float ChessAI::calculateMaterial(ChessPiece* piece) {
	switch (piece->getType()) {

	case PAWN: {
		return 1;
	}

	case KNIGHT:
	{
		return 3;
	}
	case ROOK:
	{
		return 5;
	}
	case BISHOP:
	{
		return 3;
	}
	case QUEEN:
	{
		return 9;
	}
	case KING:
	{
		return 0;
	}
	}

	throw "ChessAI::calculateMaterial -> UNKNOWN TYPE";
}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board)
{
	return calculateNextMove(board, color, 1);
}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board, PLAYER_COLOR color) {

	return calculateNextMove(board, color, 1);
}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board, PLAYER_COLOR color, int depthLevel)
{
	ChessBoard* tmpBoard = board->toTemporaryBoard();

	std::vector<PieceWithField> allMoves;
	ChessPiece** allPieces = tmpBoard->getPieces(color);
	for (int i = 0; i < 16; ++i) {
		for (auto field : allPieces[i]->getPossibleMoves()) {
			ChessAIPositionEstimation estimation = estimatePosition(allPieces[i], field, tmpBoard);
			allMoves.push_back(PieceWithField(allPieces[i], field, estimation));
		}
	}

	/*std::cout << "============== ALL MOVES ==============" << std::endl;
	for (auto tmp : allMoves) {
		tmp.printf();
	}*/

	std::vector<PieceWithField> selectedMoves;

	if (depthLevel == 0) {
		selectedMoves = allMoves;
	} else {
		int howMany = 3;
		selectedMoves = findBestMoves(allMoves, 3);
		for (int i = 0; i < selectedMoves.size(); ++i) {
			selectedMoves[i].setEstimation(estimateMove(selectedMoves[i], tmpBoard, 1));
		}
		for (auto move : selectedMoves)
			move.printf();
	}
	
	PieceWithField selectedMove = findBestMove(selectedMoves);

	ChessPiece* realPiece = board->getMyChessPiece(selectedMove.getPiece());

	delete tmpBoard;
	return ChessAIMove(realPiece, selectedMove.getField(), selectedMove.getEstimation().getForPromotionPawn(), selectedMove.getEstimation());
}

ChessAIPositionEstimation ChessAI::estimateMove(PieceWithField pieceWithField, ChessBoard* board, int howDeep) {
	pieceWithField.printf();
	pieceWithField.saveMovement();
	ChessAIPositionEstimation finalEstimation = pieceWithField.getEstimation();
	ChessBoard* tmpBoard = board->toTemporaryBoard();

	ChessPiece* piece = tmpBoard->getMyChessPiece(pieceWithField.getPiece());
	piece->tryToMove(pieceWithField.getField());

	
	for (int i = 0; i < howDeep; ++i) {
		ChessAIMove enemyMove = calculateNextMove(tmpBoard, getEnemyColor(), 0);
		enemyMove.getEstimation().printf();
		finalEstimation -= enemyMove.getEstimation();
		std::cout << "FINAL = ";  finalEstimation.printf();
		board->makeMoveAndUpdateCurrentPlayer(enemyMove);

		ChessAIMove myMove = calculateNextMove(tmpBoard, color, 0);
		myMove.getEstimation().printf();
		finalEstimation += myMove.getEstimation();
		std::cout << "FINAL = "; finalEstimation.printf();
		board->makeMoveAndUpdateCurrentPlayer(myMove);
	}
	
	delete tmpBoard;
	std::cout << "LAST ONE == " << finalEstimation.getEstimation() << std::endl;
	return finalEstimation;
}

PieceWithField ChessAI::findBestMove(std::vector<PieceWithField> allMoves) {
	PieceWithField bestMove = allMoves[0];
	for (auto move : allMoves) {
		if (bestMove.getEstimation() < move.getEstimation())
			bestMove = move;
	}

	return bestMove;
}

ChessAIPositionEstimation ChessAI::findBestEstimation(std::vector<ChessAIPositionEstimation> estimations) {
	ChessAIPositionEstimation bestEstimation = estimations[0];
	for (auto estimation : estimations) {
		if (bestEstimation < estimation)
			bestEstimation = estimation;
	}

	return bestEstimation;
}

std::vector<PieceWithField> ChessAI::findBestMoves(std::vector<PieceWithField> allMoves, int howMany) {
	std::sort(allMoves.begin(), allMoves.end(), PieceWithField::greater);
	if (allMoves.size() <= howMany)
		return allMoves;

	return std::vector<PieceWithField>(allMoves.begin(), allMoves.begin() + howMany);
}