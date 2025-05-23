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
	sf::Texture backgroundTexture;
	sf::Texture buttonTexture;
	sf::Texture gumballTexture;
	sf::Sprite backgroundSprite;
	sf::Sprite buttonSprite;
	sf::Sprite gumballSprite;
	TextsMain textsMain;

	sf::Texture shopButton;
	sf::Sprite shopButtonSprite;
	TextsShop textsShop;

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