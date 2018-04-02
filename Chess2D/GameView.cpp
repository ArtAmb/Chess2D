#include "GameView.h"

GameView::~GameView()
{
	if (board != nullptr)
		delete board;
}

void GameView::additionalDisplayAction(sf::RenderWindow * window)
{
	board->unlightAllFields();
	board->highlightFields(*fieldSelector);

	board->draw(window);
}

void GameView::additionalEventCheck(sf::RenderWindow * window)
{
	if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::S) {
		std::cout << "ROW " << fieldSelector->getRow() << std::endl
			<< "COLUMN " << fieldSelector->getColumn() << std::endl
			<< "Saved piece  " << fieldSelector->getSavedPiece() << std::endl << std::endl;
	}
	for(int i = 0; i <8; ++i)
		for (int j = 0; j < 8; ++j)	{
			ChessBoardField* field = board->getField(i, j);
			if (field->contains(mousePosition)) {
				field->selected();
				fieldSelector->update(field->toSimpleField());

				if (happening.type == sf::Event::MouseButtonReleased && happening.key.code == sf::Mouse::Left) {
					board->selectField(fieldSelector);
				}
			}
			
		}
}
