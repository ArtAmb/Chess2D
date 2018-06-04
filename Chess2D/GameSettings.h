#pragma once
#include "ChessEnums.h"
#include "SFML/Graphics.hpp"
class GameSettings
{
	LEVEL_OPTION level = NORMAL;
	COLOR_OPTION color = WHITE_O;
	
public:
	LEVEL_OPTION getLevel() {
		return level;
	}

	COLOR_OPTION getColor() {
		return color;
	}

	void setColor(COLOR_OPTION color) {
		this->color = color;
	}
	void setLevel(LEVEL_OPTION level) {
		this->level = level;
	}

	GameSettings();
	~GameSettings();
};

