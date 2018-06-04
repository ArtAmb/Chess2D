#include "OptionsButtonAction.h"
#include "LevelOptionsButton.h"
#include "OptionsView.h"


OptionsButtonAction::OptionsButtonAction() {
	
	gameSettings = new GameSettings();
	
	TextureResource* buttonsTexture = resourceManager->getTexture(RESOURCE::TEXTURE::NORMAL_BUTTONS);
	TextureResource* backgroundTexture = resourceManager->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	
	view = new OptionsView(backgroundTexture->getWidth(), backgroundTexture->getHeight(), backgroundTexture->getSprite(1, 1));
	auto optionView = static_cast<OptionsView*>(view);

	int i = 5;
	Button* colorModeButton = game->createDefaultButton(buttonsTexture, i, view);
	++i;
	
	Button* randomColorButton = createDefaultColorButton(RANDOM_O, buttonsTexture, i, optionView);
	++i;
	Button* whiteColorButton = createDefaultColorButton(WHITE_O, buttonsTexture, i, optionView);
	++i;
	Button* blackColorButton = createDefaultColorButton(BLACK_O, buttonsTexture, i, optionView);
	++i;
	
	Button* levelModeButton = game->createDefaultButton(buttonsTexture, i, view);	
	++i;
	
	
	Button* easyLevelButton = createDefaultLevelButton(EASY, buttonsTexture, i, optionView);
	++i;
	Button* normalLevelButton = createDefaultLevelButton(NORMAL, buttonsTexture, i, optionView);
	++i;
	Button* hardLevelButton = createDefaultLevelButton(HARD, buttonsTexture, i, optionView);

	
	view->prepareView();
}


Button * OptionsButtonAction::createDefaultColorButton(COLOR_OPTION color, TextureResource * texture, int logicalRow, OptionsView* view)
{
	ColorOptionsButton* button = new ColorOptionsButton(color, view);
	button->SetTexture(texture->getTexture());
	button->AddFrameOFF(texture->getConverter()->getElementRect(logicalRow, 0));
	button->AddFrameON(texture->getConverter()->getElementRect(logicalRow, 1));
	view->addButton(button);
	view->addColorButton(button);
	return button;
}

Button * OptionsButtonAction::createDefaultLevelButton(LEVEL_OPTION level, TextureResource * texture, int logicalRow, OptionsView* view)
{
	LevelOptionsButton* button = new LevelOptionsButton(level, view);
	button->SetTexture(texture->getTexture());
	button->AddFrameOFF(texture->getConverter()->getElementRect(logicalRow, 0));
	button->AddFrameON(texture->getConverter()->getElementRect(logicalRow, 1));
	view->addButton(button);
	view->addLevelButton(button);
	return button;
}

OptionsButtonAction::~OptionsButtonAction()
{
}

void OptionsButtonAction::doAction(ClickEvent* event)
{
	view->display(event->getWindow());
}
