#pragma once
#include <SFML\Graphics.hpp>
class PositionTextureConverter
{

	int width_element;
	int height_element;
	bool isGridOnTexture = false;
public:

	void setIsGridOnTexture(bool);
	int getElementWidth();
	int getElementHeight();
	PositionTextureConverter(int width, int height);

	int convertToColumn(int COLUMN);
	int convertToRow(int row);
	sf::IntRect getElementRect(int row, int col);
	
	~PositionTextureConverter();
};

