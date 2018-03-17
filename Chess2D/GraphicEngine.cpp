#include "GraphicEngine.h"
sf::RenderWindow GraphicEngine::mainWindow;
sf::Texture* GraphicEngine::loadTexture(std::string fileName)
{
	sf::Texture* texture = new sf::Texture();
	if (!texture->loadFromFile(fileName))
		errorMessage("CANNOT LOAD TEXTURE UNDER PATH: " + fileName);
	return texture;
}
void GraphicEngine::errorMessage(std::string errorDescription)
{
	mainWindow.close();
	sf::Font font;
	if (!font.loadFromFile("resources/coolvetica rg.ttf"))
	{
		std::cout << "ERROR: ERROR MESSAGE() NIE MOZNA ZALAWODWAC FONT-u" << std::endl;
		_getch();
	}
	sf::Text text;
	text.setFont(font);
	text.setString(errorDescription);
	text.setCharacterSize(25);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(50, 50);



	sf::RenderWindow ErrorWindow;
	ErrorWindow.create(sf::VideoMode(800, 600), "ERROR WINDOW");


	sf::Event happening;
	while (ErrorWindow.isOpen())
	{

		while (ErrorWindow.pollEvent(happening))
		{
			if (happening.type == sf::Event::Closed)
				ErrorWindow.close();

			if (happening.type == sf::Event::KeyPressed && happening.key.code == sf::Keyboard::Escape)
				ErrorWindow.close();



		}

		ErrorWindow.clear(sf::Color(0, 0, 255, 0));
		ErrorWindow.draw(text);
		ErrorWindow.display();

	}
}

GraphicEngine::GraphicEngine()
{
	mainWindow.create(sf::VideoMode(WIDTH_BACKGROUND, HEIGHT_BACKGROUND, 32), "Chess 2D"); 
	mainWindow.setVerticalSyncEnabled(true);
}


GraphicEngine::~GraphicEngine()
{
}
