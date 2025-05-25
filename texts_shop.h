#ifndef TEXTS_SHOP_H
#define TEXTS_SHOP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "item.h"

class TextsShop {
private:
	sf::Font font;
	void setUpTextShop(sf::Text*, sf::Vector2f,int siize);
public:
	TextsShop() = default;
	bool perfromSetupTextShop(std::vector<Item>);
	void drawInGameTextsShop(sf::RenderWindow*, std::vector<Item>, float, float, float);
};

#endif
