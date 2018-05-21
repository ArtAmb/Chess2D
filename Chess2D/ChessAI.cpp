#include "ChessAI.h"
#include <algorithm>   

ChessAI::~ChessAI()
{
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields)
{
	//FieldInfluence fieldInfluence = estimateInfluenceOnField(piece->getColor(), field, attackedFields);
	
	ChessAIPositionEstimation estimation;
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	tmpBoard->getMyChessPiece(piece)->tryToMove(field);

	if (tmpBoard->isPawnBeingPromoted()) {
		estimation = estimatePostionForPawnPromotion(tmpBoard);
	}
	else {
		estimation = estimatePosition(tmpBoard, piece->getColor(), attackedFields);
	}

	/*
	if (fieldInfluence.getPiecesDifference() == 0) {
		if(fieldInfluence.getMaterialDifference() < 0)
	}*/

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
	ChessAIPositionEstimation estimation = estimatePosition(board, playerColor, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >>>());
	estimation.setForPromotionPawn(promotionType);
	delete tmpBoard;

	return estimation;
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessBoard* board, PLAYER_COLOR color, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	ChessPiece** myPieces = board->getPieces(color);
	ChessPiece** enemyPieces = board->getPieces(getEnemyColorFor(color));

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float estimation = myMaterial - enemyMaterial;

	ChessAIMovesDTO myMovesCalculationResult = calculatePossibleMoves(myPieces);
	ChessAIMovesDTO enemyMovesCalculationResult = calculatePossibleMoves(enemyPieces);

	EndGameDTO myEndGameDTO = myMovesCalculationResult.getEndGameDTO();
	EndGameDTO enemyEndGameDTO = enemyMovesCalculationResult.getEndGameDTO();

	int possibleMoves = myEndGameDTO.getPossibleMoves().size() - enemyEndGameDTO.getPossibleMoves().size();

	CHESS_GAME_STATE state = (color == WHITE ? board->checkIfGameEnd(myEndGameDTO, enemyEndGameDTO) : board->checkIfGameEnd(enemyEndGameDTO, myEndGameDTO));

	if (state == WINNER_BLACK && color == BLACK)
		estimation += 9000;
	if (state == WINNER_WHITE && color == WHITE)
		estimation += 9000;

	return ChessAIPositionEstimation(estimation, possibleMoves);
}

std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > ChessAI::findAttackedFields(ChessBoard* board, AllMoves allMoves) {
	std::unordered_map<std::string, std::vector<std::vector<ChessPiece*>>> attackedFieldsMap;

	for (auto move : allMoves.getBlackMoves()) {
		if (board->getField(move.getField())->getPiece() != nullptr) {
			if (attackedFieldsMap.find(move.getField().toHashString()) == attackedFieldsMap.end()) {
				attackedFieldsMap[move.getField().toHashString()] = std::vector<std::vector<ChessPiece*>>();
			}

			attackedFieldsMap[move.getField().toHashString()][BLACK].push_back(move.getPiece());
		}
	}

	for (auto move : allMoves.getWhiteMoves()) {
		if (board->getField(move.getField())->getPiece() != nullptr) {
			if (attackedFieldsMap.find(move.getField().toHashString()) == attackedFieldsMap.end()) {
				attackedFieldsMap[move.getField().toHashString()] = std::vector<std::vector<ChessPiece*>>();
			}

			attackedFieldsMap[move.getField().toHashString()][WHITE].push_back(move.getPiece());
		}
	}

	return attackedFieldsMap;
}

FieldInfluence ChessAI::estimateInfluenceOnField(PLAYER_COLOR myColor, SimpleChessField field, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	auto pieces = attackedFields[field.toHashString()];
	auto myPieces = pieces[myColor];
	auto enemyPieces = pieces[getEnemyColorFor(myColor)];

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float materialDiff =  myMaterial - enemyMaterial;
	int piecesDiff = myPieces.size() - enemyPieces.size();

	return FieldInfluence(materialDiff, piecesDiff);
}

float ChessAI::calculateMaterial(std::vector<ChessPiece* > pieces) {
	float result = 0;
	for (auto piece : pieces) {
		result += calculateMaterial(piece);
	}

	return result;
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

ChessAIMovesDTO ChessAI::calculatePossibleMoves(ChessPiece** pieces) {
	std::vector<SimpleChessField> possibeMoves;
	std::vector<ChessPiece* > alivePiecesWithoutKing;
	std::vector<PieceWithField> piecesWithFields;
	for (int i = 0; i < 16; ++i) {
		if (pieces[i]->isAlive()) {
			if (pieces[i]->getType() != KING)
				alivePiecesWithoutKing.push_back(pieces[i]);

			std::vector<SimpleChessField> tmp = pieces[i]->getPossibleMoves();
			for (auto tmpField : tmp)
				piecesWithFields.push_back(PieceWithField(pieces[i], tmpField));

			possibeMoves.insert(possibeMoves.end(), tmp.begin(), tmp.end());
		}
	}

	return ChessAIMovesDTO(EndGameDTO(alivePiecesWithoutKing, possibeMoves), piecesWithFields);
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

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board, PLAYER_COLOR color, int depthLevel) {
	ChessBoard* tmpBoard = board->toTemporaryBoard();

	std::vector<PieceWithField> allMoves;
	AllMoves allPossibleMovesOnBoard = tmpBoard->getAllPossibleMoves();
	std::vector<PieceMove> myMoves = (color == WHITE ? allPossibleMovesOnBoard.getWhiteMoves() : allPossibleMovesOnBoard.getBlackMoves());

	/*ChessPiece** allPieces = tmpBoard->getPieces(color);
	for (int i = 0; i < 16; ++i) {
		for (auto field : allPieces[i]->getPossibleMoves()) {
			ChessAIPositionEstimation estimation = estimatePosition(allPieces[i], field, tmpBoard, allPossibleMovesOnBoard);
			allMoves.push_back(PieceWithField(allPieces[i], field, estimation));
		}
	} */
	auto attackedFields = tmpBoard->findAttackedFields(allPossibleMovesOnBoard);
	for (auto chessMove : myMoves) {
		ChessAIPositionEstimation estimation = estimatePosition(chessMove.getPiece(), chessMove.getField(), tmpBoard, attackedFields);
		allMoves.push_back(PieceWithField(chessMove.getPiece(), chessMove.getField(), estimation));
	}

	/*std::cout << "============== ALL MOVES ==============" << std::endl;
	for (auto tmp : allMoves) {
		tmp.printf();
	}*/

	std::vector<PieceWithField> selectedMoves;

	if (depthLevel == 0) {
		selectedMoves = allMoves;
	}
	else {
		int howMany = 3;
		selectedMoves = findBestMoves(allMoves, 3);
		for (int i = 0; i < selectedMoves.size(); ++i) {
			selectedMoves[i].setEstimation(estimateMove(selectedMoves[i], tmpBoard, 1));
		}
		for (auto move : selectedMoves)
			move.printf();
	}

	if (selectedMoves.empty()) {
		delete tmpBoard;
		return ChessAIMove(nullptr, SimpleChessField(), PROM_QUEEN, ChessAIPositionEstimation(-9000.0, 0));
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

		if (enemyMove.getPiece() == nullptr) {
			break;
		}
		board->makeMoveAndUpdateCurrentPlayer(enemyMove);

		ChessAIMove myMove = calculateNextMove(tmpBoard, color, 0);
		myMove.getEstimation().printf();
		finalEstimation += myMove.getEstimation();
		std::cout << "FINAL = "; finalEstimation.printf();
		if (myMove.getPiece() == nullptr) {
			finalEstimation.setEstimation(-9000);
			break;
		}
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