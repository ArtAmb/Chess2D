#include "LayoutView.h"

void LayoutView::setEndKey(sf::Keyboard::Key key) {
	endKey = key;
}

void LayoutView::setTopPadding(int padding)
{
	this->topPadding = padding;
}

void LayoutView::addButton(Button * button)
{
	buttons.push_back(button);
}
void LayoutView::initDisplaying() {

}
void LayoutView::display(sf::RenderWindow* window)
{
	while (window->isOpen())
	{
		mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
		initDisplaying();

		while (window->pollEvent(happening)) {
			if (happening.type == sf::Event::Closed)
				window->close();

			if (happening.type == sf::Event::KeyReleased && happening.key.code == sf::Keyboard::Escape) {
				setDisplaying(false);
			}
			
			checkButtons(window);
			additionalEventCheck(window);
		}

		if (!isDisplaying()) {
			finishDisplaying();
			return;
		}
		
		draw(window);
		window->display();
	}
}

void LayoutView::setDisplaying(bool displaying)
{
	this->displaying = displaying;
}

void LayoutView::draw(sf::RenderWindow* window) {
	window->draw(*background);

	additionalDisplayAction(window);

	for (Button* button : buttons) {
		window->draw(button->RetSprite());
	}
}

void LayoutView::setTexture(sf::Sprite* background) {
	this->background = background;
}

LayoutView::LayoutView(int width, int height, sf::Sprite* background) {
	this->width = width;
	this->height = height;
	this->background = background;

	if (!font.loadFromFile("resources/Lora.ttf"))
		std::cout << "ERROR: LOADING FONT";
}

void LayoutView::prepareView()
{
	int middleWidth = width / 2;
	int i = 0;
	int heightPixel = topPadding;
	for (Button* button : buttons) {

		int buttonWidth = button->RetSprite().getTextureRect().width;
		int buttonHeight = button->RetSprite().getTextureRect().height;

		int widthPixel = middleWidth - buttonWidth / 2;
		heightPixel += (heightComponentsGap + 1);
		button->SetXY(widthPixel, heightPixel);

		heightPixel += buttonHeight;
		++i;
		if (heightPixel >= height)
			GraphicEngine::errorMessage("TO MANY BUTTONS...");
	}

}

void LayoutView::setHeightGap(int gap)
{
	heightComponentsGap = gap;
}


void LayoutView::finishDisplaying()
{
	displaying = true;
}

void LayoutView::additionalDisplayAction(sf::RenderWindow* window)
{

}

void LayoutView::additionalEventCheck(sf::RenderWindow * window)
{
}

void LayoutView::checkButtons(sf::RenderWindow* window)
{
	for (Button* button : buttons) {
		button->SetOFF();
	}

	for (Button* button : buttons) {
		if (button->contains(mousePosition)) {
			button->SetON();
			if (happening.type == sf::Event::MouseButtonReleased && happening.key.code == sf::Mouse::Left) {
				ClickEvent* event = new ClickEvent();
				event->setWindow(window);
				event->setView(this);

				button->click(event);
			}
		}

	}
}

LayoutView::~LayoutView()
{
}
