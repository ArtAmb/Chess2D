#include "ResourceManager.h"

ResourceManager* ResourceManager::instance;

void ResourceManager::setPathToResource(std::string path)
{
	this->pathToResource = path;
}

ResourceManager * ResourceManager::getInstance()
{
	if (instance == nullptr)
		instance = new ResourceManager();

	return instance;
}

void ResourceManager::loadTexture(int key, std::string path, int elementWidth, int elementHeight)
{
	loadTextureFullPath(key, pathToResource + path, elementWidth, elementHeight);
}

void ResourceManager::loadTextureFullPath(int key, std::string fullPath, int elementWidth, int elementHeight)
{
	TextureResource* resource = new TextureResource(fullPath, elementWidth, elementHeight);
	textureMap[key] = resource;
}

TextureResource* ResourceManager::getTexture(int key)
{
	return textureMap[key];
}


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
