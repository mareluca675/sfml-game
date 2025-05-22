#include "texts.h"
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

Texts::Texts() {
	textScore.setString("0.00");
	textUpgradeCost.setString("1.00");
	textMousePower.setString("Mouse Power: 1.0");
	fpsText.setString("FPS: 0");
}

void Texts::setUpText(sf::Text* text, sf::Vector2f position) {
	text->setFont(font);
	text->setCharacterSize(24);
	text->setFillColor(sf::Color::White);
	text->setStyle(sf::Text::Bold);
	text->setPosition(position);
}

bool Texts::perfromSetup() {
	if (!font.loadFromFile("fonts/arial.ttf")) {
		std::cout << "ERROR: Could not load font.\n";
		return false;
	}

	setUpText(&textScore, sf::Vector2f(10.0f, 10.0f));
	setUpText(&textUpgradeCost, sf::Vector2f(10.0f, WINDOW_HEIGHT - 50.0f));
	setUpText(&textMousePower, sf::Vector2f(10.0f, WINDOW_HEIGHT - 80.0f));
	setUpText(&fpsText, sf::Vector2f(WINDOW_WIDTH - 100.0f, 10.0f));

	return true;
}

void Texts::drawInGameTexts(sf::RenderWindow* window, float score, float upgradeCost, float mousePower) {
	textScore.setString("Score: " + formatFloat(score));
	window->draw(textScore);
	textUpgradeCost.setString("Upgrade Cost: " + formatFloat(upgradeCost));
	window->draw(textUpgradeCost);
	textMousePower.setString("Mouse Power: " + formatFloat(mousePower));
	window->draw(textMousePower);
}