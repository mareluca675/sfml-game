#include "game.h"

Game::Game() {
	mousePower = 1.0f;
	score = 0.0f;
	upgradeCost = 1.0f;
    isMainScene = true;
    isShopScene = false;
}

bool Game::loadTexturesMain() {
    if (!backgroundTexture.loadFromFile("textures/background.png")) {
        std::cerr << "ERROR: Could not load backround image.";
        return false;
    }

    if (!upgradeButtonTexture.loadFromFile("textures/button.png")) {
        std::cerr << "ERROR: Could not load button image.";
        return false;
    }

	if (!shopButtonTexture.loadFromFile("textures/button.png")) {
		std::cerr << "ERROR: Could not load shop image.";
		return false;
	}

    if (!gumballTexture.loadFromFile("textures/gumball.png")) {
        std::cerr << "ERROR: Could not load gumball image.";
        return false;
    }

    // Set the texture rect for the button sprite
    upgradeButtonSprite.setTexture(upgradeButtonTexture);
    upgradeButtonSprite.setPosition(0.0f, 50.0f);

    // Set the texture rect for the gumball sprite
    gumballSprite.setTexture(gumballTexture);
    gumballSprite.setPosition(WINDOW_WIDTH / 2.0f - 50, WINDOW_HEIGHT / 2.0f - 50);

    // Set the texture rect for the background sprite
    shopButtonSprite.setTexture(shopButtonTexture);
    shopButtonSprite.setPosition(0.0f, 300.0f);

    // Set the texture rect for the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

bool Game::loadTexturesShop() {
	std::cout << "Esti bun." << std::endl;
    return true;
}

bool Game::performSetupMain() {
    textsMain = TextsMain();
    return loadTexturesMain() && textsMain.perfromSetupMain();
}

bool Game::performSetupShop() {
    textsShop = TextsShop();
    return loadTexturesShop() && textsShop.perfromSetupShop();
}

bool Game::runGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GumbaLL");

    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window event
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Mouse button pressed event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Get mouse position relative to the window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if the button was clicked
                if (upgradeButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (score >= upgradeCost) {
                        score -= upgradeCost;
                        score = std::round(score * 100.0f) / 100.0f;
                        mousePower += mousePower * UPGRADE_CONSTANT;
                        mousePower = std::round(mousePower * 100.0f) / 100.0f; // Round to 2 decimal places
                        upgradeCost = std::ceil(upgradeCost + 1.755f * upgradeCost * UPGRADE_CONSTANT);
                    }
                }
                else if (shopButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = !isMainScene;
                    isShopScene = !isShopScene;
                }
                else if (gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
                    score += mousePower;
                    score = std::round(score * 100.0f) / 100.0f;
                }
            }

            window.clear();

            if (isMainScene) {
                window.draw(backgroundSprite);
                textsMain.drawInGameTextsMain(&window, score, upgradeCost, mousePower);
                window.draw(upgradeButtonSprite);
				window.draw(shopButtonSprite);
                window.draw(gumballSprite);
            }
            else if (isShopScene) {
                window.draw(gumballSprite);
                window.draw(shopButtonSprite);
            }


            window.display();
        }
    }

    return false;
}