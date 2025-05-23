#include <SFML/Graphics.hpp>

#ifndef TEXTS_SHOP_H
#define TEXTS_SHOP_H

class TextsShop {
private:
	sf::Font font;
	void setUpTextShop(sf::Text*, sf::Vector2f);
public:
	TextsShop();
	sf::Text item1;
	sf::Text item1Cost;
	sf::Text item2;
	sf::Text item2Cost;
	bool perfromSetupShop();
	void drawInGameTextsShop(sf::RenderWindow* window, std::string item1Name, float item1Cost, std::string item2Name, float item2Cost);
};

#endif