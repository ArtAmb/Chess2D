#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "PositionTextureConverter.h"

void ChessBoardField::setSprite(sf::Sprite* sprite)
{
	this->sprite = sprite;
}

bool ChessBoardField::isEmpty()
{
	return chessPiece == nullptr;
}

ChessPiece * ChessBoardField::getPiece()
{
	return chessPiece;
}

void ChessBoardField::setPiece(ChessPiece* piece)
{
	this->chessPiece = piece;
}

ChessBoardField::ChessBoardField(int width, int height, sf::Sprite* sprite)
{
	this->width = width;
	this->height = height;
	this->sprite = sprite;
}

void ChessBoardField::setXY(int x, int y)
{
	sprite->setPosition(static_cast<float>(x), static_cast<float>(y)); 
	if (chessPiece != nullptr)
		chessPiece->setXY(x,y);
}

void ChessBoardField::draw(sf::RenderWindow * mainWindow)
{
	mainWindow->draw(*sprite);
	if(chessPiece != nullptr)
		mainWindow->draw(*chessPiece->getSprite());
}

ChessBoardField* ChessBoard::getField(CHESS_COLUMN c, CHESS_ROW r)
{
	return &board[r][c];
}

ChessBoard::ChessBoard(int width, int height, sf::Sprite* background)
{
	this->width = width;
	this->height = height;

	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);

	blackField = fieldTexture->getSprite(2, 0);
	whiteField = fieldTexture->getSprite(2, 1);
	
	for (int i = 0; i < 8; ++i)
	{
		pieces[WHITE][i] = new Pawn(R_2, (CHESS_COLUMN)i, WHITE, this, fieldTexture->getSprite(0, 0));
	}

	for (int i = 0; i < 8; ++i)
	{
		pieces[BLACK][i] = new Pawn(R_7, (CHESS_COLUMN)i, BLACK, this, fieldTexture->getSprite(1, 0));
	}

	pieces[WHITE][8] = new Pawn(R_1, C_C, WHITE, this, fieldTexture->getSprite(0, 1));
	pieces[WHITE][9] = new Pawn(R_1, C_F, WHITE, this, fieldTexture->getSprite(0, 1));

	pieces[BLACK][8] = new Pawn(R_8, C_C, BLACK, this, fieldTexture->getSprite(1, 1));
	pieces[BLACK][9] = new Pawn(R_8, C_F, BLACK, this, fieldTexture->getSprite(1, 1));

	pieces[WHITE][10] = new Pawn(R_1, C_A, WHITE, this, fieldTexture->getSprite(0, 2));
	pieces[WHITE][11] = new Pawn(R_1, C_H, WHITE, this, fieldTexture->getSprite(0, 2));

	pieces[BLACK][10] = new Pawn(R_8, C_A, BLACK, this, fieldTexture->getSprite(1, 2));
	pieces[BLACK][11] = new Pawn(R_8, C_H, BLACK, this, fieldTexture->getSprite(1, 2));

	pieces[WHITE][12] = new Pawn(R_1, C_B, WHITE, this, fieldTexture->getSprite(0, 3));
	pieces[WHITE][13] = new Pawn(R_1, C_G, WHITE, this, fieldTexture->getSprite(0, 3));

	pieces[BLACK][12] = new Pawn(R_8, C_B, BLACK, this, fieldTexture->getSprite(1, 3));
	pieces[BLACK][13] = new Pawn(R_8, C_G, BLACK, this, fieldTexture->getSprite(1, 3));

	pieces[WHITE][14] = new Pawn(R_1, C_D, WHITE, this, fieldTexture->getSprite(0, 4));
	pieces[BLACK][14] = new Pawn(R_8, C_D, BLACK, this, fieldTexture->getSprite(1, 4));

	pieces[WHITE][15] = new Pawn(R_1, C_E, WHITE, this, fieldTexture->getSprite(0, 5));
	pieces[BLACK][15] = new Pawn(R_8, C_E, BLACK, this, fieldTexture->getSprite(1, 5));

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].setSprite(i % 2 == j % 2 ? fieldTexture->getSprite(2, 0) : fieldTexture->getSprite(2, 1));
			board[i][j].setXY(72 + j * 72, 72 + i * 72);
		}
	}
}

/*
int getRowInPixels(CHESS_ROW row) {

}
int getColInPixels(CHESS_COLUMN col) {

}
*/
void ChessBoard::draw(sf::RenderWindow* window) {

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].draw(window);
		}
	}

}
