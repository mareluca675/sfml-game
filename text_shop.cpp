#include "texts_shop.h"
#include "item.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// Function to format float to two decimal places
std::string formatFloatShop(float value) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(2) << value;
	return out.str();
}

void TextsShop::setUpTextShop(sf::Text* text, sf::Vector2f position) {
	text->setFont(font);
	text->setCharacterSize(40);
	text->setFillColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setPosition(position);
}

bool TextsShop::perfromSetupTextShop(std::vector<Item> items) {
	if (!font.loadFromFile("fonts/pixel.ttf")) {
		std::cout << "ERROR: Could not load font.\n";
		return false;
	}

	// Draw cost / name of each item on the screen
	for (size_t i = 0; i < items.size(); ++i) {
		sf::Text itemText;
		setUpTextShop(&itemText, sf::Vector2f(10.0f, 50.0f + i * 30.0f));
		itemText.setString(items[i].getName() + " - Cost: " + formatFloatShop(items[i].getCost()));
	}

	return true;  
}

void TextsShop::drawInGameTextsShop(sf::RenderWindow* window, std::vector<Item> items, float score, float mousePower) {
	// Draw the score and mouse power in the shop scene
	sf::Text scoreText;
	setUpTextShop(&scoreText, sf::Vector2f(10.0f, 10.0f));
	scoreText.setString("Score: " + formatFloatShop(score));
	window->draw(scoreText);

	// Draw the mouse power in the shop scene
	sf::Text mousePowerText;
	setUpTextShop(&mousePowerText, sf::Vector2f(10.0f, 40.0f));
	mousePowerText.setString("Mouse Power: " + formatFloatShop(mousePower));
	window->draw(mousePowerText);

	// Draw the items in the shop scene
	for (size_t i = 0; i < items.size(); ++i) {
		sf::Text itemText;
		setUpTextShop(&itemText, sf::Vector2f(10.0f, 50.0f + i * 30.0f));
		itemText.setString(items[i].getName() + " - Cost: " + formatFloatShop(items[i].getCost()));
		window->draw(itemText);
	}
}