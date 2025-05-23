#include "texts_main.h"
#include "game.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// Function to format float to two decimal places
std::string formatFloatShop(float value) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(2) << value;
	return out.str();
}

TextsShop::TextsShop() {
	item1.setString("NIGGER");
	item1Cost.setString("1.00");
	item2.setString("MICU");
	item2Cost.setString("0.99");
}

void TextsShop::setUpTextShop(sf::Text* text, sf::Vector2f position) {
	text->setFont(font);
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setPosition(position);
}

bool TextsShop::perfromSetupShop() {
	if (!font.loadFromFile("fonts/arial.ttf")) {
		std::cout << "ERROR: Could not load font.\n";
		return false;
	}

	setUpTextShop(&item1, sf::Vector2f(10.0f, 10.0f));
	setUpTextShop(&item1Cost, sf::Vector2f(10.0f, WINDOW_HEIGHT - 50.0f));
	setUpTextShop(&item2, sf::Vector2f(10.0f, WINDOW_HEIGHT - 80.0f));
	setUpTextShop(&item2Cost, sf::Vector2f(WINDOW_WIDTH - 100.0f, 10.0f));

	return true;
}

void TextsShop::drawInGameTextsShop(sf::RenderWindow* window, float score, float upgradeCost, float mousePower) {
	item1.setString("Score: " );
	window->draw(item1);
	item1Cost.setString("Upgrade Cost: " );
	window->draw(item1Cost);
	item2.setString("Mouse Power: ");
	window->draw(item2);
	item2Cost.setString("rebe sa mearga: ");
	window->draw(item2Cost);
}