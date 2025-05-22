#include "game.h"

Game::Game() {
	mousePower = 1.0f;
	score = 0.0f;
	upgradeCost = 1.0f;
}

bool Game::loadTextures() {
    if (!backgroundTexture.loadFromFile("textures/background.png")) {
        std::cerr << "ERROR: Could not load backround image.";
        return false;
    }

	if (!buttonTexture.loadFromFile("textures/button.png")) {
		std::cerr << "ERROR: Could not load button image.";
		return false;
	}

	if (!gumballTexture.loadFromFile("textures/gumball.png")) {
		std::cerr << "ERROR: Could not load gumball image.";
		return false;
	}

	// Set the texture rect for the button sprite
	buttonSprite.setTexture(buttonTexture);
	buttonSprite.setPosition(0.0f,50.0f);
    
	// Set the texture rect for the gumball sprite
	gumballSprite.setTexture(gumballTexture);
    gumballSprite.setPosition(WINDOW_WIDTH / 2.0f -  50, WINDOW_HEIGHT / 2.0f - 50);

	// Set the texture rect for the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

bool Game::performSetup() {
    texts = Texts();
    return loadTextures() && texts.perfromSetup();
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
                if (buttonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (score >= upgradeCost) {
                        score -= upgradeCost;
                        score = std::round(score * 100.0f) / 100.0f;
                        mousePower += mousePower * UPGRADE_CONSTANT;
                        mousePower = std::round(mousePower * 100.0f) / 100.0f; // Round to 2 decimal places
                        upgradeCost = std::ceil(upgradeCost + 1.755f * upgradeCost * UPGRADE_CONSTANT);
                    }
                }
                else if (gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
                    score += mousePower;
                    score = std::round(score * 100.0f) / 100.0f;
                }
            }

            window.clear();
            window.draw(backgroundSprite);
            texts.drawInGameTexts(&window, score, upgradeCost, mousePower);
			window.draw(buttonSprite);
			window.draw(gumballSprite);
            window.display();
        }
    }

    return false;
}