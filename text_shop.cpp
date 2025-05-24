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
	item1.setString("ITEM 1");
	item1Cost.setString("1.00");
	item2.setString("ITEM 2");
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

void TextsShop::drawInGameTextsShop(sf::RenderWindow* window, std::string item1Name, float item1Coost, std::string item2Name, float item2Coost) {
	item1.setString("Item Name: " + item1Name);
	window-> draw(item1);
	item1Cost.setString("Item Price: " + formatFloatShop(item1Coost));
	window->draw(item1Cost);
	item2.setString("Item Name: " + item2Name);
	window->draw(item2);
	item1Cost.setString("Item Price: " + formatFloatShop(item2Coost));
	window->draw(item2Cost);
}