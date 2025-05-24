#include "texts.h"
#include <iostream>

#ifndef GAMEWORLD_H
#define GAMEWORLD_H

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
	Texts texts;

	// Function for loading background
	bool loadTextures1();
public:
	// Constructor
	Game();
	bool performSetup();
	bool runGame();
};

#endif