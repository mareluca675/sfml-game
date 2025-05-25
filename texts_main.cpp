#include "texts_main.h"
#include "game.h"

#include <iostream>
#include <sstream>
#include <iomanip>

// Function to format float to two decimal places
std::string formatFloat(float value) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(2) << value;
	return out.str();
}

TextsMain::TextsMain() {
	scoreText.setString("0.00");
	upgradeCostText.setString("1.00");
	mousePowerText.setString("Mouse Power: 1.0");
}

void TextsMain::setUpTextMain(sf::Text* text, sf::Vector2f position) {
	text->setFont(font);
	text->setCharacterSize(40);
	text->setFillColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setPosition(position);
}

bool TextsMain::perfromSetupMain() {
	if (!font.loadFromFile("fonts/pixel.ttf")) {
		std::cout << "ERROR: Could not load font.\n";
		return false;
	}

	setUpTextMain(&scoreText, sf::Vector2f(10.0f, 10.0f));
	setUpTextMain(&upgradeCostText, sf::Vector2f(10.0f, WINDOW_HEIGHT - 50.0f));
	setUpTextMain(&mousePowerText, sf::Vector2f(10.0f, WINDOW_HEIGHT - 80.0f));

	return true;
}

void TextsMain::drawInGameTextsMain(sf::RenderWindow* window, float score, float upgradeCost, float mousePower) {
	scoreText.setString("Score: " + formatFloat(score));
	window->draw(scoreText);
	upgradeCostText.setString("Upgrade Cost: " + formatFloat(upgradeCost));
	window->draw(upgradeCostText);
	mousePowerText.setString("Mouse Power: " + formatFloat(mousePower));
	window->draw(mousePowerText);
}