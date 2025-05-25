#include "texts_main.h"
#include "texts_shop.h"
#include "item.h"

#include <iostream>
#include <vector>

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
	float upgradeCost;

	// Background
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

	// Background Shop
	sf::Texture backgroundShopTexture;
	sf::Sprite backgroundShopSprite;

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
	
	int level = 1;
public:
	// Constructor
	Game();
	bool runGame();

	// Getter and Setter for upgradeCost	
	float getUpgradeCost() const { return upgradeCost; }
	void setUpgradeCost(float newUpgradeCost) { upgradeCost = newUpgradeCost; }

	// Getters for level variable
	float getLevel() const { return level; }
	void setLevel(int newLevel) { level = newLevel; }
	bool getIsMainScene() const { return isMainScene; }
	bool getIsShopScene() const { return isShopScene; }
};

#endif