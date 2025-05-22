#include <SFML/Graphics.hpp>

#ifndef TEXTS_H
#define TEXTS_H

class Texts {
private:
	sf::Font font;
	void setUpText(sf::Text*, sf::Vector2f);
public:
	Texts();
	sf::Text textScore;
	sf::Text textUpgradeCost;
	sf::Text textMousePower;
	sf::Text fpsText;
	bool perfromSetup();
	void drawInGameTexts(sf::RenderWindow* window, float score, float upgradeCost, float mousePower);
};

#endif