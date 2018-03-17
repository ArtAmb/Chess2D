#include "Game.h"



#define WIDTH_FIELD 56



#define WIDTH_BACKGROUND_MODE 648
#define HEIGHT_BACKGROUND_MODE 264


Game::Game(sf::RenderWindow* mainWindow, GraphicEngine* engine)
{
	this->mainWindow = mainWindow;
	TextureResource* buttonsTexture = resourceManager->getTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS);
	TextureResource* menuBackground = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);

	
	menuView = new LayoutView(menuBackground->getConverter()->getElementWidth(), menuBackground->getConverter()->getElementHeight(), menuBackground->getSprite(0,0));
	int i = 0;
	Button* newGameButton = createDefaultButton(buttonsTexture, i, menuView);
	++i;
	Button* optionsButton = createDefaultButton(buttonsTexture, i, menuView);
	++i;
	Button* resultsButton = createDefaultButton(buttonsTexture, i, menuView);
	++i;
	Button* creditsButton = createDefaultButton(buttonsTexture, i, menuView);
	++i;
	Button* exitButton = createDefaultButton(buttonsTexture, i, menuView);

	menuView->prepareView();
}


void Game::startGame()
{
	while (true) {
		menuView->display(mainWindow);





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
