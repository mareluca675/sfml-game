#include <SFML/Graphics.hpp>

#ifndef TEXTS_MAIN_H
#define TEXTS_MAIN_H

class TextsMain {
private:
	sf::Font font;
	void setUpTextMain(sf::Text*, sf::Vector2f);
public:
	TextsMain();
	sf::Text textScore;
	sf::Text textUpgradeCost;
	sf::Text textMousePower;
	sf::Text fpsText;
	bool perfromSetupMain();
	void drawInGameTextsMain(sf::RenderWindow* window, float score, float upgradeCost, float mousePower);
};

#endif