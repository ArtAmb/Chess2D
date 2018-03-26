#include "Game.h"
#include "GameButtonAction.h"
#include "OptionsButtonAction.h"
#include "QuitButtonAction.h"
#include "ResultsButtonAction.h"
#include "CreditsButtonAction.h"




#define WIDTH_FIELD 72


#define WIDTH_BACKGROUND_MODE 648
#define HEIGHT_BACKGROUND_MODE 264


Game::Game(sf::RenderWindow* mainWindow, GraphicEngine* engine)
{
	this->mainWindow = mainWindow;
	TextureResource* buttonsTexture = resourceManager->getTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS);
	TextureResource* menuBackground = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);


	menuView = new LayoutView(menuBackground->getConverter()->getElementWidth(), menuBackground->getConverter()->getElementHeight(), menuBackground->getSprite(0, 0));
	int i = 0;
	Button* newGameButton = createDefaultButton(buttonsTexture, i, menuView);
	newGameButton->setOnClickAction(new GameButtonAction());
	++i;
	Button* optionsButton = createDefaultButton(buttonsTexture, i, menuView);
	optionsButton->setOnClickAction(new OptionsButtonAction());
	++i;
	Button* resultsButton = createDefaultButton(buttonsTexture, i, menuView);
	resultsButton->setOnClickAction(new ResultsButtonAction());
	++i;
	Button* creditsButton = createDefaultButton(buttonsTexture, i, menuView);
	creditsButton->setOnClickAction(new CreditsButtonAction());
	++i;
	Button* exitButton = createDefaultButton(buttonsTexture, i, menuView);
	exitButton->setOnClickAction(new QuitButtonAction());

	menuView->prepareView();

	TextureResource* gameBackground = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	chessBoard = new ChessBoard(gameBackground->getConverter()->getElementWidth(), gameBackground->getConverter()->getElementHeight(), gameBackground->getSprite(0, 1));

	
}


void Game::startGame()
{
	while (true) {
		menuView->display(mainWindow);
		
		//chessBoard->display(mainWindow);




		mainWindow->display();
	}

}


Button * Game::createDefaultButton(TextureResource * texture, int logicalRow, LayoutView* view)
{
	Button* button = new Button();
	button->SetTexture(texture->getTexture());
	button->AddFrameOFF(texture->getConverter()->getElementRect(logicalRow, 0));
	button->AddFrameON(texture->getConverter()->getElementRect(logicalRow, 1));
	view->addButton(button);
	return button;
}


Game::~Game()
{
}
