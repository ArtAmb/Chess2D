#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>
#include <cmath>
#include "MenuButton.h"
#include "LayoutView.h"
#include "Game.h"

int main()
{
	GraphicEngine graphicEngine;
	Game game(graphicEngine.getMainWindow(), &graphicEngine);
	
	game.startGame();

	return 0;
}