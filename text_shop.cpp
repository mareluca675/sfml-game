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
	// Go through the items in the shop and set up their text
	for (const auto& item : itemsShop) {
		
	}
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

	return true;
}

void TextsShop::drawInGameTextsShop(sf::RenderWindow* window, float score, float upgradeCost, float mousePower) {
	//item1.setString("Score: " );
	window->draw(item1);
	//item1Cost.setString("Upgrade Cost: " );
	window->draw(item1Cost);
	//item2.setString("Mouse Power: ");
}