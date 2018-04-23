#pragma once
#include "ChessEnums.h"
#include "SFML/Graphics.hpp"
class GameSettings
{
	LEVEL_OPTION level = NORMAL;
	COLOR_OPTION color = RANDOM_O;
	
	

public:
	
	GameSettings();
	~GameSettings();
};

