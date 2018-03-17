#include "Game.h"


#define WIDTH_FIELD 56

#define WIDTH_BACKGROUND 836
#define HEIGHT_BACKGROUND 728

#define WIDTH_BACKGROUND_MODE 648
#define HEIGHT_BACKGROUND_MODE 264

#define WIDTH_BUTTON 296
#define HEIGHT_BUTTON 50

int ConvertBUTTONtoPositionOnTexture_COLUMN(int COLUMN)
{
	return COLUMN + WIDTH_BUTTON * COLUMN;
}

int ConvertBUTTONtoPositionOnTexture_ROW(int row)
{
	return 1 + row * HEIGHT_BUTTON + row;
}

Game::Game(sf::RenderWindow* mainWindow, GraphicEngine* engine)
{
	sf::Texture* texture = engine->loadTexture("resources/menu.png");
	sf::Texture* buttonsTexture = engine->loadTexture("resources/buttons.png");
	this->mainWindow = mainWindow;
	sf::Sprite* menuBackground = new sf::Sprite(*texture, sf::IntRect(0, 0, WIDTH_BACKGROUND, HEIGHT_BACKGROUND));
	menuView = new LayoutView(WIDTH_BACKGROUND, HEIGHT_BACKGROUND, menuBackground);
	int i = 0;
	Button* newGameButton = new Button();
	newGameButton->SetTexture(buttonsTexture);
	newGameButton->AddFrameOFF(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(0), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	newGameButton->AddFrameON(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(1), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	menuView->addButton(newGameButton);
	++i;
	Button* optionsButton = new Button();
	optionsButton->SetTexture(buttonsTexture);
	optionsButton->AddFrameOFF(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(0), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	optionsButton->AddFrameON(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(1), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	menuView->addButton(optionsButton);
	++i;
	Button* resultsButton = new Button();
	resultsButton->SetTexture(buttonsTexture);
	resultsButton->AddFrameOFF(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(0), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	resultsButton->AddFrameON(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(1), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	menuView->addButton(resultsButton);
	++i;
	Button* creditsButton = new Button();
	creditsButton->SetTexture(buttonsTexture);
	creditsButton->AddFrameOFF(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(0), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	creditsButton->AddFrameON(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(1), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	menuView->addButton(creditsButton);
	++i;
	Button* exitButton = new Button();
	exitButton->SetTexture(buttonsTexture);
	exitButton->AddFrameOFF(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(0), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	exitButton->AddFrameON(sf::IntRect(ConvertBUTTONtoPositionOnTexture_COLUMN(1), ConvertBUTTONtoPositionOnTexture_ROW(i), WIDTH_BUTTON, HEIGHT_BUTTON));
	menuView->addButton(exitButton);

	menuView->prepareView();
}


void Game::startGame()
{
	while (true) {
		menuView->display(mainWindow);

		mainWindow->display();
	}

}


Game::~Game()
{
}
