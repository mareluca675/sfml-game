#include <SFML/Graphics.hpp>

#ifndef TEXTS_MAIN_H
#define TEXTS_MAIN_H

class TextsMain {
private:
	sf::Font font;
	void setUpTextMain(sf::Text*, sf::Vector2f);
public:
	TextsMain();
	sf::Text scoreText;
	sf::Text upgradeCostText;
	sf::Text mousePowerText;
	sf::Text criticalChance;
	sf::Text upgrade;
	sf::Text level;
	bool perfromSetupMain();
	void drawInGameTextsMain(sf::RenderWindow* window, float score, float upgradeCost, float mousePower, float criticalChance, int level);
};

#endif