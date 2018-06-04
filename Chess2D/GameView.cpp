#include "GameView.h"

GameView::~GameView()
{
	if (board != nullptr)
		delete board;

	if (chessAI != nullptr)
		delete chessAI;

	if (fieldSelector != nullptr)
		delete fieldSelector;
}

void GameView::additionalDisplayAction(sf::RenderWindow * window) {
	board->unlightAllFields();
	board->highlightFields(*fieldSelector);
	highlightSelectedPromotionPawnButton();

	board->draw(window);
	writeText(window);
	checkStatus(window);
	displayHistory(window);
}

void GameView::highlightSelectedPromotionPawnButton() {
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j) {
			PawnTransformationButton* button = board->getPawnTransformationButton((PLAYER_COLOR)i, (PAWN_PROMOTION)j);
			if (button->contains(mousePosition)) {
				button->selected();
			}
		}

}

void GameView::initDisplaying() {
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			board->getPawnTransformationButton((PLAYER_COLOR)i, (PAWN_PROMOTION)j)->disabled();
		}
	}
}

void GameView::additionalEventCheck(sf::RenderWindow * window) {

	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::S) {
		std::cout << "ROW " << fieldSelector->getRow() << std::endl
			<< "COLUMN " << fieldSelector->getColumn() << std::endl
			<< "Saved piece  " << fieldSelector->getSavedPiece() << std::endl << std::endl;
	}

	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::T) {
		testMode = !testMode;

		if (testMode)
			std::cout << "TEST MODE ACTIVATED!!!!!" << std::endl;
		else
			std::cout << "TEST MODE DEACTIVATED!!!!!" << std::endl;
	}

	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::X) {
		if (testMode) {
			auto field = board->getField(fieldSelector->getColumn(), fieldSelector->getRow());
			if (field->getPiece() != nullptr) {
				auto piece = field->getPiece();
				piece->die();
				std::cout << "The piece["<< piece->getType() <<"] on field [" << fieldSelector->getRow() << "," << fieldSelector->getColumn() << "] was killed" << std::endl;
			}
			else {
				std::cout << "There is no piece on field [" << fieldSelector->getRow() << "," << fieldSelector->getColumn() << "]" << std::endl;
			}
		}
	}

	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::N) {
		auto attackedFields = board->findAttackedFields();
		auto field = board->getField(fieldSelector->getColumn(), fieldSelector->getRow());
		auto influence = chessAI->estimatePositionBasingOnFieldImpact(board, board->getCurrPlayer(), attackedFields);

		std::cout << field->toSimpleField().toHashString() << "WHOLE BOARD INFLUENCE == " << influence << std::endl;

	}

	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::I) {
		auto attackedFields = board->findAttackedFields();
		auto field = board->getField(fieldSelector->getColumn(), fieldSelector->getRow());
		FieldInfluence fieldInfluence = chessAI->estimateInfluenceOnField(board->getCurrPlayer(), field, attackedFields);
		std::cout << field->toSimpleField().toHashString() << " INFLUENCE == " << fieldInfluence.getMetarialExchangeEstimation() << std::endl;

	}

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j) {
			ChessBoardField* field = board->getField(i, j);
			if (field->contains(mousePosition)) {
				field->selected();
				if (!testMode && chessAI != nullptr && board->getCurrPlayer() == chessAI->getColor())
					continue;

				fieldSelector->update(field->toSimpleField());

				if (happening.type == sf::Event::MouseButtonReleased && happening.key.code == sf::Mouse::Left) {
					board->selectField(fieldSelector);
				}
			}

		}
	
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 4; ++j) {
			PawnTransformationButton* button = board->getPawnTransformationButton((PLAYER_COLOR)i, (PAWN_PROMOTION)j);
			if (button->contains(mousePosition)) {

				if (happening.type == sf::Event::MouseButtonReleased && happening.key.code == sf::Mouse::Left) {
					if (button->isActive()) {
						ChessPiece* piece = board->getPawnBeingPromoted();
						board->promotePawnTo(button->getPawnPromotionType(), ChessMoveToSave(piece->getSimpleField(), piece->getSimpleField(), piece));
					}
				}
			}
		}

	if (!testMode && chessAI != nullptr && board->getGameState() == CONTINIUE && board->getCurrPlayer() == chessAI->getColor() && !chessAI->isThinking()) {
		chessAI->startThinking();
		ChessAIMove chessAIMove = chessAI->calculateNextMove(board);
		board->makeMoveAndUpdateCurrentPlayer(chessAIMove);
		chessAI->stopThinking();
	}

	
	
}

void GameView::checkStatus(sf::RenderWindow * window)
{

	sf::Text str;
	str.setFont(font);
	str.setCharacterSize(40);
	str.setFillColor(sf::Color(0, 0, 0));
	str.setStyle(sf::Text::Bold);
	str.setPosition(710, 100);


	switch (board->getGameState())
	{
	case CONTINIUE:
	{
		if (board->getCurrPlayer() == WHITE)
			str.setString(L"Ruch: BIA£E");
		else
			str.setString("Ruch: CZARNE");
		break;
	}
	case WINNER_BLACK:
		str.setString(L"MAT! ZWYCIÊZCA: CZARNE");
		str.setFillColor(sf::Color(255, 0, 0));
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	case WINNER_WHITE:
		str.setString(L"MAT! ZWYCIÊZCA: BIA£E");
		str.setFillColor(sf::Color(255, 0, 0));
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	case STALEMATE:
		str.setString("PAT");
		str.setFillColor(sf::Color(255, 0, 0));
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	default:
		break;
	}
	window->draw(str);


}

void GameView::displayHistory(sf::RenderWindow * window)
{
	std::vector<std::string> movements = board->getMovements();

	sf::Text title;
	title.setFont(font);
	title.setCharacterSize(34);
	title.setFillColor(sf::Color(0, 0, 0));
	title.setStyle(sf::Text::Bold);
	title.setPosition(710, 180);
	title.setString(L"Historia ruchów:");



	const size_t mSize = movements.size();
	size_t startIt = 0;

	if (mSize > 15)
		startIt = mSize - 15;


	std::vector<sf::Text> str(mSize);
	float pos = 230;
	
	int j = 0;
	for (size_t i = startIt; i < movements.size(); i++) {

		str[j].setFont(font);
		str[j].setCharacterSize(20);
		str[j].setFillColor(sf::Color(0, 0, 0));
		str[j].setStyle(sf::Text::Bold);
		str[j].setPosition(710, pos);

		std::string nr = std::to_string(i+1);		
		str[j].setString(nr+". " + movements[i]);
		pos += 28.f;
		++j;

	}



	window->draw(title);
	for (auto& text : str)
	{
		window->draw(text);
	}


}
void GameView::writeText(sf::RenderWindow * window)
{

	sf::Text str[2];
	for (int i = 0; i < 2; i++) {
		str[i].setFont(font);
		str[i].setCharacterSize(26);
		str[i].setFillColor(sf::Color(0, 0, 0));
		str[i].setStyle(sf::Text::Bold);
		str[i].setString(L"Promocja pionka:");
	}
	str[0].setPosition(40, 10);
	str[1].setPosition(40, 680);
		
			
	for (int i = 0; i < 2; i++) {
		window->draw(str[i]);
	}

}