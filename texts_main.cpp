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
	textScore.setString("0.00");
	textUpgradeCost.setString("1.00");
	textMousePower.setString("Mouse Power: 1.0");
	fpsText.setString("FPS: 0");
}

void TextsMain::setUpTextMain(sf::Text* text, sf::Vector2f position) {
	text->setFont(font);
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setPosition(position);
}

bool TextsMain::perfromSetupMain() {
	if (!font.loadFromFile("fonts/arial.ttf")) {
		std::cout << "ERROR: Could not load font.\n";
		return false;
	}

	setUpTextMain(&textScore, sf::Vector2f(10.0f, 10.0f));
	setUpTextMain(&textUpgradeCost, sf::Vector2f(10.0f, WINDOW_HEIGHT - 50.0f));
	setUpTextMain(&textMousePower, sf::Vector2f(10.0f, WINDOW_HEIGHT - 80.0f));
	setUpTextMain(&fpsText, sf::Vector2f(WINDOW_WIDTH - 100.0f, 10.0f));

	return true;
}

void TextsMain::drawInGameTextsMain(sf::RenderWindow* window, float score, float upgradeCost, float mousePower) {
	textScore.setString("Score: " + formatFloat(score));
	window->draw(textScore);
	textUpgradeCost.setString("Upgrade Cost: " + formatFloat(upgradeCost));
	window->draw(textUpgradeCost);
	textMousePower.setString("Mouse Power: " + formatFloat(mousePower));
	window->draw(textMousePower);
}