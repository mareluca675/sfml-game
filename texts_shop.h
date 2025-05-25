#include <SFML/Graphics.hpp>
#include "list.hpp"
#include "item.h"

#ifndef TEXTS_SHOP_H
#define TEXTS_SHOP_H

class TextsShop {
private:
	sf::Font font;
	void setUpTextShop(sf::Text*, sf::Vector2f);
public:
	TextsShop();
	List<Item> itemsShop;

	List<std::string> itemsShopNames = {
		"RMT",
		"Book of Critical Chance",
		"Mouse Power Upgrade"
	};

	List<float> itemsShopCosts = {
		100.0f, // RMT
		200.0f, // Book of Critical Chance
		300.0f  // Mouse Power Upgrade
	};

	List<std::string> itemsShopTextures = {
		"textures/rmt.png",
		"textures/book.png",
		"textures/mouse_power_upgrade.png"
	};
	
	bool perfromSetupShop();
	void drawInGameTextsShop(sf::RenderWindow* window, float score, float upgradeCost, float mousePower);
};

#endif