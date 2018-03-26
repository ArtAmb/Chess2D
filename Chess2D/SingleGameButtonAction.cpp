#include "SingleGameButtonAction.h"
#include "SFML/Graphics.hpp"


SingleGameButtonAction::SingleGameButtonAction()
{

}


SingleGameButtonAction::~SingleGameButtonAction()
{
}

void SingleGameButtonAction::doAction(ClickEvent* event)
{
	TextureResource* fieldTexture = ResourceManager::getInstance()->getTexture(RESOURCE::TEXTURE::BACKGROUNDS);
	sf::Sprite* back = fieldTexture->getSprite(0, 1);

	sf::RenderWindow* window = event->getWindow();
	ChessBoard* board = new ChessBoard(0, 0, nullptr); //TODO

	while (window->isOpen())
	{
		sf::Event happening;
		while (window->pollEvent(happening))
		{
			if (happening.type == sf::Event::Closed)
				window->close();
		}

		sf::Vector2f mousePosition(sf::Mouse::getPosition(*window));

		window->draw(*back);
		board->draw(window);
		window->display();
	}

}
