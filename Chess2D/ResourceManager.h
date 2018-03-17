#pragma once
#include <map>
#include "TextureResource.h"
#include "GraphicEngine.h"


class ResourceManager
{
	static ResourceManager* instance;
	std::string pathToResource = "";
	std::map<int, TextureResource*> textureMap;
public:

	void setPathToResource(std::string path);

	static ResourceManager* getInstance();

	void loadTexture(int key, std::string path, int elementWidth, int elementHeight);
	void loadTextureFullPath(int key, std::string fullPath, int elementWidth, int elementHeight);
	TextureResource* getTexture(int key);

	ResourceManager();
	~ResourceManager();
};
