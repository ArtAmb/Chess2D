#include "LayoutView.h"

void LayoutView::addButton(Button * button)
{
	buttons.push_back(button);
}

void LayoutView::display(sf::RenderWindow* window)
{

	while (window->isOpen())
	{
		sf::Event happening;
		while (window->pollEvent(happening))
		{
			if (happening.type == sf::Event::Closed)
				window->close();

		}


		sf::Vector2f mousePosition(sf::Mouse::getPosition(*window));

		for (Button* button : buttons) {
			button->SetOFF();
		}

		for (Button* button : buttons) {
			if (button->contains(mousePosition)) {
				button->SetON();
				if (happening.type == sf::Event::MouseButtonReleased && happening.key.code == sf::Mouse::Left)
				{
					button->click();
					return;
				}
			}


		}


		draw(window);
		window->display();
	}
}

void LayoutView::draw(sf::RenderWindow* window) {
	window->draw(*background);

	for (Button* button : buttons) {
		window->draw(button->RetSprite());
	}
}

void LayoutView::setTexture(sf::Sprite* background)
{
	this->background = background;
}

LayoutView::LayoutView(int width, int height, sf::Sprite* background)
{
	this->width = width;
	this->height = height;
	this->background = background;
}

void LayoutView::prepareView()
{
	int middleWidth = width / 2;
	int i = 0;
	int heightPixel = heightComponentsGap;
	for (Button* button : buttons) {

		int buttonWidth = button->RetSprite().getTextureRect().width;
		int buttonHeight = button->RetSprite().getTextureRect().height;

		int widthPixel = middleWidth - buttonWidth/2;
		heightPixel += i * heightComponentsGap;
		button->SetXY(widthPixel, heightPixel);

		heightPixel += buttonHeight + 1;
		++i;
		if (heightPixel >= height)
			GraphicEngine::errorMessage("TO MANY BUTTONS...");
	}

}

void LayoutView::setHeightGap(int gap)
{
	heightComponentsGap = gap;
}


LayoutView::~LayoutView()
{
}
