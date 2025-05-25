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

void TextsShop::setUpTextShop(sf::Text* text, sf::Vector2f position, int siize) {
	text->setFont(font);
	text->setCharacterSize(siize);
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
		setUpTextShop(&itemText, sf::Vector2f(10.0f, 50.0f + i * 30.0f), 40);
		itemText.setString(items[i].getName() + " - Cost: " + formatFloatShop(items[i].getCost()));
	}

	return true;  
}

void TextsShop::drawInGameTextsShop(sf::RenderWindow* window, std::vector<Item> items, float score, float mousePower, float criticalChance) {
	// Draw the score and mouse power in the shop scene
	sf::Text scoreText;
	setUpTextShop(&scoreText, sf::Vector2f(10.0f, 10.0f), 40);
	scoreText.setString("Score: " + formatFloatShop(score));
	window->draw(scoreText);

	// Draw the mouse power in the shop scene
	sf::Text mousePowerText;
	setUpTextShop(&mousePowerText, sf::Vector2f(10.0f, 40.0f), 40);
	mousePowerText.setString("Mouse Power: " + formatFloatShop(mousePower));
	window->draw(mousePowerText);

	// Draw the critical chance in the shop scene
	sf::Text criticalChanceText;
	setUpTextShop(&criticalChanceText, sf::Vector2f(10.0f, 70.0f), 40);	
	criticalChanceText.setString("Critical Chance: " + formatFloatShop(criticalChance * 100.0f) + "%");
	window->draw(criticalChanceText);

	// Draw the items in the shop scene
	for (size_t i = 0; i < items.size(); ++i) {
		sf::Text itemText;
		sf::Text itemMousePower;
		sf::Text itemCriticalChance;
		// Set up the text for each item
		setUpTextShop(&itemText, sf::Vector2f(400.0f + i * 250.0f - 15 * i, 280 + 15 * i), 30);
		itemText.setString(items[i].getName() + " - Cost: " + formatFloatShop(items[i].getCost()));
		window->draw(itemText);
		// Set up the mouse power text for each item
		setUpTextShop(&itemMousePower, sf::Vector2f(400.0f + i * 250.0f - 15 * i, 310 + i * 150), 30);
		itemMousePower.setString("Mouse Power: " + formatFloatShop(items[i].getMousePower()));
		window->draw(itemMousePower);
		// Set up the critical chance text for each item
		setUpTextShop(&itemCriticalChance, sf::Vector2f(400.0f + i * 235.0f - 40 * (i == 0), 330 + (i == 0) * 150), 30);
		itemCriticalChance.setString("Critical Chance: " + formatFloatShop(items[i].getCriticalChance() * 100.0f) + "%");
		window->draw(itemCriticalChance);
	}
}