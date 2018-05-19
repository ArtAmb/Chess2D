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
	checkStatus(window);
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
						board->promotePawnTo(button->getPawnPromotionType());
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
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	case WINNER_WHITE:
		str.setString(L"MAT! ZWYCIÊZCA: BIA£E");
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	case STALEMATE:
		str.setString("PAT");
		str.setPosition(1008 / 2 - str.getGlobalBounds().width / 2, 300);
		break;

	default:
		break;
	}
	window->draw(str);


}
