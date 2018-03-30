#pragma once
#include <SFML\Graphics.hpp>
#include "PositionTextureConverter.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "GraphicEngine.h"
#include "ChessPiece.h"

class ChessBoardField {
private:
	sf::Sprite* sprite;
	ChessPiece* chessPiece = nullptr;
	int height, width;

public:
	ChessBoardField() {}
	~ChessBoardField();
	ChessBoardField(int width, int height, sf::Sprite* sprite);
	void setXY(int x, int y);
	void draw(sf::RenderWindow* mainWindow);
	void setSprite(sf::Sprite* sprite);
	bool isEmpty();

	ChessPiece* getPiece();
	void setPiece(ChessPiece* piece);

};

class ChessBoard {

	ChessPiece* pieces[2][16];
	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::FIELDS);


	int height, width;
	const static int BOARD_SIZE = 8;
	ChessBoardField board[BOARD_SIZE][BOARD_SIZE];
	sf::Sprite* getWhiteFieldSprite();
	sf::Sprite* getBlackFieldSprite();
public:

	ChessBoard();
	~ChessBoard();
	void draw(sf::RenderWindow* window);
	ChessBoardField* getField(CHESS_COLUMN c, CHESS_ROW r);
};
