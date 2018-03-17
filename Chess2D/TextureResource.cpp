#include "TextureResource.h"



PositionTextureConverter * TextureResource::getConverter()
{
	return converter;
}

sf::Texture * TextureResource::getTexture()
{
	return texture;
}

sf::Sprite* TextureResource::getSprite(int logicalRow, int logicalColumn)
{
	sf::IntRect tmp(converter->convertToColumn(logicalColumn), converter->convertToRow(logicalRow), converter->getElementWidth(), converter->getElementHeight());
	return new sf::Sprite(*texture, tmp);
}

TextureResource::TextureResource(std::string texturePath, int width, int heigth)
{
	this->texture = GraphicEngine::loadTexture(texturePath);
	converter = new PositionTextureConverter(width, heigth);
}


TextureResource::~TextureResource()
{
}
