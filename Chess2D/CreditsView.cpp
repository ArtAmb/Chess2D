#include "CreditsView.h"

CreditsView::~CreditsView()
{
	
}

void CreditsView::additionalDisplayAction(sf::RenderWindow* window)
{
	
	const int howMany=6;
	sf::Text str[howMany];
	
	
	for (int i = 0; i < howMany; i++) {
		str[i].setFont(font);
		str[i].setCharacterSize(40);
		str[i].setFillColor(sf::Color(255, 255, 255));
		str[i].setStyle(sf::Text::Bold);
		

		str[i].setPosition(100, 200 + i * 55);
	
		
		
	}
	str[0].setString(L"Politechnika Œwiêtokrzyska");
	//str[1].setString(L"Komunikacja cz³owiek-komputer");
	str[1].setString(L"Projekt zespo³owy");
	str[2].setString("Autorzy:");
	str[3].setString("Ambrolewicz Artur");
	//str[3].setString("Autor:");
	str[4].setString(L"B¹tkowska Karolina");

	str[5].setPosition(100, 600);
	str[5].setString(L"Kielce 2018");

	for (int i = 0; i < howMany; i++) {
		
		window->draw(str[i]);
	}
}
