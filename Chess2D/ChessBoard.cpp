#include "ChessBoard.h"

void ChessBoardField::setTexture(sf::Sprite* spriteField)
{
	this->spriteField = spriteField;
}

ChessBoardField::ChessBoardField(int width, int height, sf::Sprite* spriteField)
{
	this->width = width;
	this->height = height;
	this->spriteField = spriteField;
}





void ChessBoardField::prepareChessBoardField(sf::RenderWindow* window)
{
TextureResource* fieldTexture = resourceManager->getTexture(RESOURCE::TEXTURE::FIELDS);

ChessBoardField* blackField= new ChessBoardField(fieldTexture->getConverter()->getElementWidth(), fieldTexture->getConverter()->getElementHeight(), fieldTexture->getSprite(3, 0));
ChessBoardField* whiteField = new ChessBoardField(fieldTexture->getConverter()->getElementWidth(), fieldTexture->getConverter()->getElementHeight(), fieldTexture->getSprite(3, 1));

}

void ChessBoard::setTexture(sf::Sprite* background)
{
	this->background = background;
}

ChessBoard::ChessBoard(int width, int height, sf::Sprite* background)
{
	this->width = width;
	this->height = height;
	this->background = background;
}



void ChessBoard::draw(sf::RenderWindow* window) {
	window->draw(*background);	

}

/*
void ::draw(sf::RenderWindow* window)
{
window->draw(*background);
	
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].draw(i % 2 == j % 2 ? window->draw(blackField->RetSpire()) : window->draw(whiteField->RetSpire()));
		}
	}
}*/
void ChessBoard::display(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		sf::Event happening;
		while (window->pollEvent(happening))
		{
			if (happening.type == sf::Event::Closed)
				window->close();

		}


		sf::Vector2f mousePosition(sf::Mouse::getPosition(*window));

		


		draw(window);
		window->display();
	}
}
