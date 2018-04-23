#include "Game.h"
#include "GameModeButtonAction.h"
#include "OptionsButtonAction.h"
#include "QuitButtonAction.h"
#include "InstructionButtonAction.h"
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
	Button* gameModeButton = createDefaultButton(buttonsTexture, i, menuView);
	gameModeButton->setOnClickAction(new GameModeButtonAction());
	++i;
	Button* optionsButton = createDefaultButton(buttonsTexture, i, menuView);
	optionsButton->setOnClickAction(new OptionsButtonAction());
	++i;
	Button* instructionButton = createDefaultButton(buttonsTexture, i, menuView);
	instructionButton->setOnClickAction(new InstructionButtonAction());
	++i;
	Button* creditsButton = createDefaultButton(buttonsTexture, i, menuView);
	creditsButton->setOnClickAction(new CreditsButtonAction());
	++i;
	Button* exitButton = createDefaultButton(buttonsTexture, i, menuView);
	exitButton->setOnClickAction(new QuitButtonAction());

	menuView->prepareView();

	TextureResource* gameBackground = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	chessBoard = new ChessBoard();

	
}


void Game::startGame()
{
	menuView->display(mainWindow);
	
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

