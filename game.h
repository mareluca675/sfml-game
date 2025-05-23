#include "texts_main.h"
#include "texts_shop.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

// Constants
constexpr float UPGRADE_CONSTANT = 0.2f; // Use 'constexpr' instead of 'const' for compile-time constants
constexpr unsigned int WINDOW_WIDTH = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
const unsigned int FRAME_RATE_LIMIT = 60;

class Game {
private:
	// Game variables
	float mousePower;
	float score;
	float upgradeCost;

	// SFML objects

	// Backround
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	// Upgrade button
	sf::Texture upgradeButtonTexture;
	sf::Sprite upgradeButtonSprite;

	// Gumball
	sf::Texture gumballTexture;
	sf::Sprite gumballSprite;

	// Shop button enter
	sf::Texture shopButtonEnterTexture;
	sf::Sprite shopButtonEnterSprite;

	// Shop button leave
	sf::Texture shopButtonLeaveTexture;
	sf::Sprite shopButtonLeaveSprite;

	// Bacground Shop
	sf::Texture backgroundShopTexture;
	sf::Sprite backgroundShopSprite;
	// Item1 Texture
	sf::Texture item1Texture;
	sf::Sprite item1Sprite;

	// Item2 Texture
	sf::Texture item2Texture;
	sf::Sprite item2Sprite;

	// Texts for main scene
	TextsMain textsMain;

	// Texts for shop scene
	TextsShop textsShop;

	// Booleans for checking if we are in the main scene or shop scene
	bool isMainScene;
	bool isShopScene;

	// Function for loading background
	bool loadTexturesMain();
	bool loadTexturesShop();
public:
	// Constructor
	Game();
	bool performSetupMain();
	bool performSetupShop();
	bool runGame();
	// Getter and Setter for score
	float getScore() const { return score; }
	void setScore(float newScore) { score = newScore; }
};

#endif