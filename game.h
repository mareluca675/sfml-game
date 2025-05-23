#include "texts_main.h"
#include "texts_shop.h"
#include <iostream>

#ifndef GAME_H
#define GAME_H

// Constants
const float UPGRADE_CONSTANT = 0.2f;
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
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

	// Shop button
	sf::Texture shopButtonTexture;
	sf::Sprite shopButtonSprite;

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
};

#endif