#pragma once
#include <SFML\Graphics.hpp>
#include "PositionTextureConverter.h"
#include "ResourceManager.h"
#include "ResourceKeys.h"
#include "GraphicEngine.h"

class ChessBoardField {
private:

	int WIDTH_FIELD = 72;
	sf::Sprite* spriteField;

	int height, width;
	sf::RenderWindow* mainWindow;
	ResourceManager* resourceManager = ResourceManager::getInstance();


public:
	ChessBoardField() {}
	~ChessBoardField() {}
	ChessBoardField(int width, int height, sf::Sprite * spriteField);
	//void SetXY(int x, int y) { spriteField.setPosition(static_cast<float>(x), static_cast<float>(y)); }
	//void draw(sf::Sprite SpriteField);
	void prepareChessBoardField(sf::RenderWindow * window);
	void setTexture(sf::Sprite *spriteField);

};

class ChessBoard {

	sf::Sprite* background;

	int height, width;
	const static int BOARD_SIZE = 8;
	//ChessBoardField board[BOARD_SIZE][BOARD_SIZE];


public:

	ChessBoard(int height, int width, sf::Sprite* background);

	void draw(sf::RenderWindow* window);
	void display(sf::RenderWindow* window);
	void setTexture(sf::Sprite* background);
};
