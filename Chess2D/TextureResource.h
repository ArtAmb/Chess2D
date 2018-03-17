#pragma once
#include "PositionTextureConverter.h"
#include "SFML\Graphics.hpp"
#include "GraphicEngine.h"

class TextureResource
{
	PositionTextureConverter* converter;
	sf::Texture* texture;
public:
	TextureResource(std::string texturePath, int width, int heigth);
	PositionTextureConverter * getConverter();
	sf::Texture* getTexture();
	sf::Sprite* getSprite(int logicalRow, int logicalColumn);
	~TextureResource();


};

