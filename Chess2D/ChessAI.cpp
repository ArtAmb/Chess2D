#include "ChessAI.h"
#include <algorithm>   
#include <functional>   
#include <thread>

ChessAI::~ChessAI()
{
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessPiece* piece, SimpleChessField field, ChessBoard* board, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields)
{
	ChessAIPositionEstimation estimation;
	ChessBoard* tmpBoard = board->toTemporaryBoard();
	auto myAttackedFields = tmpBoard->convertToMyPieces(attackedFields);

	tmpBoard->getMyChessPiece(piece)->tryToMove(field);

	if (tmpBoard->isPawnBeingPromoted()) {
		estimation = estimatePostionForPawnPromotion(tmpBoard);
	}
	else {
		estimation = estimatePosition(tmpBoard, piece->getColor(), myAttackedFields);
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
	PLAYER_COLOR playerColor = tmpBoard->getPawnBeingPromoted()->getColor();
	tmpBoard->promotePawnTo(PROM_QUEEN, ChessMoveToSave());
	ChessAIPositionEstimation estimation = estimatePosition(tmpBoard, playerColor, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >>>());
	estimation.setForPromotionPawn(promotionType);
	delete tmpBoard;

	return estimation;
}

ChessAIPositionEstimation ChessAI::estimatePosition(ChessBoard* board, PLAYER_COLOR color, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	ChessPiece** myPieces = board->getPieces(color);
	ChessPiece** enemyPieces = board->getPieces(getEnemyColorFor(color));
	//float materialFromFieldImpact = estimatePositionBasingOnFieldImpact(board, color, attackedFields);
	float materialFromFieldImpact = estimateImpactOnFieldWithMyPieces(color, board, attackedFields);

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float estimation = myMaterial - enemyMaterial + materialFromFieldImpact;

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

float ChessAI::estimatePositionBasingOnFieldImpact(ChessBoard* board, PLAYER_COLOR color, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	float result = 0.0;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			FieldInfluence fieldInfluence = estimateInfluenceOnField(color, board->getField(i, j), attackedFields);
			result += fieldInfluence.getMetarialExchangeEstimation();
		}
	}

	return result;
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

float ChessAI::estimateImpactOnFieldWithMyPieces(PLAYER_COLOR myColor, ChessBoard* board, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	auto myPieces = board->getPieces(myColor);
	float result = 0.0;

	for (int i = 0; i < 16; ++i) {
		if (myPieces[i]->isAlive()) {
			result += estimateInfluenceOnFieldWithMyPiece(myColor, board->getField(myPieces[i]->getSimpleField()), attackedFields).getMetarialExchangeEstimation();
		}
	}

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board->getField(i, j)->isEmpty()) {
				result += estimateInfluenceOnFieldWithMyPiece(myColor, board->getField(i, j), attackedFields).getMetarialExchangeEstimation();
			}
		}
	}

	return result;
}

FieldInfluence ChessAI::estimateInfluenceOnFieldWithMyPiece(PLAYER_COLOR myColor, ChessBoardField* field, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	SimpleChessField simpleField = field->toSimpleField();

	if (attackedFields.find(simpleField.toHashString()) == attackedFields.end()) {
		return FieldInfluence(0.0, 0, 0.0);
	}

	auto pieces = attackedFields[simpleField.toHashString()];
	auto myPieces = pieces[myColor];
	auto enemyPieces = pieces[getEnemyColorFor(myColor)];

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float materialDiff = myMaterial - enemyMaterial;
	int piecesDiff = myPieces.size() - enemyPieces.size();

	float result = 0.0;

	ChessPiece* piece = field->getPiece();
	ChessBoardField tmpField;
	tmpField.setPiece(piece);

	int myIndex = 0;
	int enemyIndex = 0;


	if (piece != nullptr) {
		if (piece->getColor() == myColor && enemyPieces.size() > 0) {
			result -= calculateMaterial(piece);

			tmpField.setPiece(enemyPieces[enemyIndex++]);

			for (int i = 0; i < myPieces.size(); ++i) {
				if (myPieces[i] == piece) {
					myPieces.erase(myPieces.begin() + i);
					break;
				}
			}
		}
	}

	std::sort(myPieces.begin(), myPieces.end(), ChessAI::orderPieceByValueAsc);

	for (int i = 0; i < myPieces.size(); ++i) {
		if (myPieces[i]->getType() == KING) {
			ChessPiece* king = myPieces[i];
			myPieces.erase(myPieces.begin() + i);
			myPieces.push_back(king);
		}
	}

	std::sort(enemyPieces.begin(), enemyPieces.end(), ChessAI::orderPieceByValueAsc);

	for (int i = 0; i < enemyPieces.size(); ++i) {
		if (enemyPieces[i]->getType() == KING) {
			ChessPiece* king = enemyPieces[i];
			enemyPieces.erase(enemyPieces.begin() + i);
			enemyPieces.push_back(king);
		}
	}


	if (piece == nullptr) {
		if (enemyIndex < enemyPieces.size()) {
			if (enemyPieces[enemyIndex]->getType() == KING && myPieces.size() > 0) {
				return FieldInfluence(materialDiff, piecesDiff, 0.0);
			}

			tmpField.setPiece(enemyPieces[enemyIndex++]);
		}
		else return FieldInfluence(materialDiff, piecesDiff, 0.0);
	}

	while (true) {
		if (tmpField.getPiece()->getColor() == myColor && enemyIndex < enemyPieces.size()) {
			if (enemyPieces[enemyIndex]->getType() == KING && myPieces.size() > 0) {
				break;
			}

			result -= calculateMaterial(tmpField.getPiece());
			tmpField.setPiece(enemyPieces[enemyIndex++]);
		}
		else if (tmpField.getPiece()->getColor() != myColor && myIndex < myPieces.size()) {
			if (myPieces[myIndex]->getType() == KING && enemyPieces.size() > 0) {
				break;
			}
			result += calculateMaterial(tmpField.getPiece());
			tmpField.setPiece(myPieces[myIndex++]);
		}
		else break;
	}

	return FieldInfluence(materialDiff, piecesDiff, result);
}

FieldInfluence ChessAI::estimateInfluenceOnField(PLAYER_COLOR myColor, ChessBoardField* field, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields) {
	SimpleChessField simpleField = field->toSimpleField();

	if (attackedFields.find(simpleField.toHashString()) == attackedFields.end()) {
		return FieldInfluence(0.0, 0, 0.0);
	}

	auto pieces = attackedFields[simpleField.toHashString()];
	auto myPieces = pieces[myColor];
	auto enemyPieces = pieces[getEnemyColorFor(myColor)];

	float myMaterial = calculateMaterial(myPieces);
	float enemyMaterial = calculateMaterial(enemyPieces);

	float materialDiff = myMaterial - enemyMaterial;
	int piecesDiff = myPieces.size() - enemyPieces.size();

	float result = 0.0;

	std::sort(myPieces.begin(), myPieces.end(), ChessAI::orderPieceByValueAsc);
	std::sort(enemyPieces.begin(), enemyPieces.end(), ChessAI::orderPieceByValueAsc);

	ChessPiece* piece = field->getPiece();
	ChessBoardField tmpField;
	tmpField.setPiece(piece);

	int myIndex = 0;
	int enemyIndex = 0;


	if (piece != nullptr) {
		if (piece->getColor() == myColor && enemyPieces.size() > 0) {
			result -= calculateMaterial(piece);

			tmpField.setPiece(enemyPieces[enemyIndex++]);

			for (int i = 0; i < myPieces.size(); ++i) {
				if (myPieces[i] == piece) {
					myPieces.erase(myPieces.begin() + i);
					break;
				}
			}
		}
		else if (piece->getColor() != myColor && myPieces.size() > 0) {
			result += calculateMaterial(piece);

			tmpField.setPiece(myPieces[myIndex++]);

			for (int i = 0; i < enemyPieces.size(); ++i) {
				if (enemyPieces[i] == piece) {
					enemyPieces.erase(enemyPieces.begin() + i);
					break;
				}
			}

		}
	}
	else if (enemyPieces.size() > 0) {
		tmpField.setPiece(enemyPieces[enemyIndex++]);
	}
	else return FieldInfluence(materialDiff, piecesDiff, 0);

	while (true) {
		if (tmpField.getPiece()->getColor() == myColor && enemyIndex < enemyPieces.size()) {
			result -= calculateMaterial(tmpField.getPiece());
			tmpField.setPiece(enemyPieces[enemyIndex++]);
		}
		else if (tmpField.getPiece()->getColor() != myColor && myIndex < myPieces.size()) {
			result += calculateMaterial(tmpField.getPiece());
			tmpField.setPiece(myPieces[myIndex++]);
		}
		else break;
	}


	//auto myPiecesValues = mapPiecesToValue(myPieces);
	//auto enemyPiecesValues = mapPiecesToValue(enemyPieces);





	/*
	int myAllMoveCount = myPiecesValues.size();
	int enemyAllMoveCount = enemyPiecesValues.size();

	if (result < 0) {
		while (true) {
			if (myAllMoveCount > 0 && enemyIndex < enemyPiecesValues.size()) {
				result += enemyPiecesValues[enemyIndex++];
				--enemyAllMoveCount;
			}
			if (enemyAllMoveCount > 0 && myIndex < myPiecesValues.size()) {
				result -= myPiecesValues[myIndex++];
				--myAllMoveCount;
			}

		}
	}else if (result > 0) {
		result -= myPiecesValues[myIndex];
		result += enemyPiecesValues[enemyIndex];
	}*/

	/*for (; i < myPiecesValues.size() && i < enemyPiecesValues.size(); ++i) {
		result += enemyPiecesValues[i];
		result -= myPiecesValues[i];
	}*/

	return FieldInfluence(materialDiff, piecesDiff, result);
}

bool ChessAI::orderPieceByValueAsc(ChessPiece* one, ChessPiece* two) {
	return calculateMaterial(one) < calculateMaterial(two);
}

std::vector<float> ChessAI::mapPiecesToValue(std::vector<ChessPiece* > pieces) {
	std::vector<float> values;

	for (auto piece : pieces) {
		values.push_back(calculateMaterial(piece));
	}
	std::sort(values.begin(), values.end(), std::less<float>());

	return values;
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

}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board)
{
	return calculateNextMove(board, color, 1);
}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board, PLAYER_COLOR color) {

	return calculateNextMove(board, color, 1);
}

void ChessAI::estimatePositionThread(std::vector<PieceMove> &myMoves, ChessBoard* tmpBoard, std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > attackedFields, std::vector<PieceWithField> &result) {
	std::cout << "ZACZYNAM " << myMoves.size() << std::endl;
	for (auto chessMove : myMoves) {
		ChessAIPositionEstimation estimation = estimatePosition(chessMove.getPiece(), chessMove.getField(), tmpBoard, attackedFields);
		result.push_back(PieceWithField(chessMove.getPiece(), chessMove.getField(), estimation));
		//std::cout << "DODAJE " << result.size() << std::endl;
	}
}

ChessAIMove ChessAI::calculateNextMove(ChessBoard* board, PLAYER_COLOR color, int depthLevel) {
	ChessBoard* tmpBoard = board->toTemporaryBoard();

	std::vector<PieceWithField> allMoves;
	AllMoves allPossibleMovesOnBoard = tmpBoard->getAllPossibleMoves();
	std::vector<PieceMove> myMoves = (color == WHITE ? allPossibleMovesOnBoard.getWhiteMoves() : allPossibleMovesOnBoard.getBlackMoves());

	auto attackedFields = (level == HARD ? tmpBoard->findAttackedFields() : std::unordered_map<std::string, std::vector<std::vector<ChessPiece* >> > ());
	for (auto chessMove : myMoves) {
		ChessAIPositionEstimation estimation = estimatePosition(chessMove.getPiece(), chessMove.getField(), tmpBoard, attackedFields);
		allMoves.push_back(PieceWithField(chessMove.getPiece(), chessMove.getField(), estimation));
	}
		
	std::vector<PieceWithField> selectedMoves;

	if (depthLevel == 0) {
		selectedMoves = allMoves;
	}
	else {
		int howMany = (level == NORMAL ? 5 : 3);
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
	//pieceWithField.printf();

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
		tmpBoard->makeMoveAndUpdateCurrentPlayer(enemyMove);

		ChessAIMove myMove = calculateNextMove(tmpBoard, color, 0);
		myMove.getEstimation().printf();
		finalEstimation += myMove.getEstimation();
		std::cout << "FINAL = "; finalEstimation.printf();
		if (myMove.getPiece() == nullptr) {
			finalEstimation.setEstimation(-9000);
			break;
		}
		tmpBoard->makeMoveAndUpdateCurrentPlayer(myMove);
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




void unsucesfullOptimalizationTry() {
	/*
	const int numberOfParts = 4;
	int movePart = myMoves.size() / numberOfParts;

	std::cout << "SIZE == " << myMoves.size() << std::endl;
	std::cout << "movePart == " << movePart << std::endl;

	std::vector<PieceMove> myMovesInParts[numberOfParts];
	std::thread threads[numberOfParts];
	std::vector<PieceWithField> results[numberOfParts];

	for (int i = 0; i < numberOfParts; ++i) {
	myMovesInParts[i] = std::vector<PieceMove>();
	}

	for (int i = 0; i < numberOfParts; ++i) {
	auto begin = myMoves.begin() + i * movePart;

	auto end = begin + movePart;
	if (end >= myMoves.end()) {
	end = myMoves.end();
	myMovesInParts[i] = std::vector<PieceMove>(begin, end);
	break;
	}

	myMovesInParts[i] = std::vector<PieceMove>(begin, end);
	}

	std::cout << "myMoves == " << myMoves.size() << std::endl;
	for (int i = 0; i < numberOfParts; ++i) {
	std::cout  << "DLA I == " << i << "   "<< myMovesInParts[i].size() << std::endl;
	}


	std::cout << "ZACZYNAM WATKI %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << myMoves.size() << std::endl;
	for (int i = 0; i < numberOfParts; ++i) {
	results[i] = std::vector<PieceWithField>();
	//threads[i] = std::thread(&ChessAI::estimatePositionThread, (*this), myMovesInParts[i], tmpBoard, attackedFields, results[i]);
	//std::cout << "DLA I == " << i << "   " << myMovesInParts[i].size() << std::endl;
	threads[i] = std::thread([&](ChessAI* chessAI) { chessAI->estimatePositionThread(myMovesInParts[i], tmpBoard, attackedFields, results[i]); }, this);
	}

	for (int i = 0; i < numberOfParts; ++i) {
	threads[i].join();
	}

	for (int i = 0; i < numberOfParts; ++i) {
	std::cout << results[i].size() << std::endl;
	}

	for (int i = 0; i < numberOfParts; ++i) {
	auto vect = results[i];
	allMoves.insert(allMoves.end(), vect.begin(), vect.end());
	}
	*/

	//std::cout << "allMoves size == " << allMoves.size() << std::endl;

	/*std::cout << "============== ALL MOVES ==============" << std::endl;
	for (auto tmp : allMoves) {
	tmp.printf();
	}
	*/
}