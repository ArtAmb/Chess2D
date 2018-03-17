#include "PositionTextureConverter.h"



int PositionTextureConverter::getElementWidth()
{
	return width_element;
}

int PositionTextureConverter::getElementHeight()
{
	return height_element;
}

PositionTextureConverter::PositionTextureConverter(int width, int height)
{
	width_element = width;
	height_element = height;
}

PositionTextureConverter::~PositionTextureConverter()
{
}

int PositionTextureConverter::convertToColumn(int COLUMN)
{
	return COLUMN + width_element * COLUMN;
}

int PositionTextureConverter::convertToRow(int row)
{
	return 1 + row * height_element + row;
}

sf::IntRect PositionTextureConverter::getElementRect(int row, int col)
{
	return sf::IntRect(convertToColumn(col), convertToRow(row), width_element, height_element);
}
