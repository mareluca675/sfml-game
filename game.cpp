#include "game.h"
#include "player.h"
#include "item.h"
Item item1;
Game::Game() {
	upgradeCost = 1.0f;
	score = 0.0f;
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

	if (!shopButtonEnterTexture.loadFromFile("textures/usa.png")) {
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
    shopButtonEnterSprite.setTexture(shopButtonEnterTexture);
    shopButtonEnterSprite.setPosition(1177.0f, 477.0f);

    // Set the texture rect for the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

bool Game::loadTexturesShop() {

    sf::Texture item1Texture;
    sf::Sprite item1Sprite;
    if (!item1Texture.loadFromFile("textures/book.png")) {
        std::cerr << "ERROR: Could not load shop image.";
        return false;
    }
	item1Sprite.setTexture(item1Texture);
    item1Sprite.setPosition(WINDOW_WIDTH / 2.0f - 50, WINDOW_HEIGHT / 2.0f - 50);
    item1.setName("carte"); 
	item1.setCost(10.0f);
	item1.setSprite(item1Sprite);
    item1.setCriticalChance(0.5);

    if (!backgroundShopTexture.loadFromFile("textures/Shop.png")) {
        std::cerr << "ERROR: Could not load shop image.";
        return false;
	}
    if (!shopButtonLeaveTexture.loadFromFile("textures/door.png")) {
        std::cerr << "ERROR: Could not load shop image.";
        return false;
    }

	// Set the texture rect for the button sprite
	shopButtonLeaveSprite.setTexture(shopButtonLeaveTexture);
	shopButtonLeaveSprite.setPosition(950.0f, 2.0f);

	backgroundShopSprite.setTexture(backgroundShopTexture); 
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
    Player player;
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
                if (isMainScene && upgradeButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    if (score >= upgradeCost) {
                        score -= upgradeCost;
                        score = std::round(score * 100.0f) / 100.0f;
                        player.setMousePower(  player.getMousePower() + player.getMousePower() * UPGRADE_CONSTANT);//setereeee
                        player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f); // Round to 2 decimal places
                        upgradeCost = std::ceil(upgradeCost + 1.755f * upgradeCost * UPGRADE_CONSTANT);
                    }
                }
                if (isMainScene && gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
                    score += player.getMousePower();
                    score = std::round(score * 100.0f) / 100.0f;
                }
                if (shopButtonEnterSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 0;
                    isShopScene = 1;
                }
                if (shopButtonLeaveSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 1;
                    isShopScene = 0;
                }
                if (isShopScene && item1.getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					// Check if the item is affordable
                    if (score >= item1.getCost()) {
                        // Deduct the cost from the score
                        score -= item1.getCost();
                        score = std::round(score * 100.0f) / 100.0f; // Round to 2 decimal places
                        // Apply the item's effect
                        player.setMousePower(player.getMousePower() + player.getMousePower() * item1.getCriticalChance());
                        player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f); // Round to 2 decimal places
                    }
                }
            }

            window.clear();

            if (isMainScene) {
                loadTexturesMain();
                window.draw(backgroundSprite);
                textsMain.drawInGameTextsMain(&window, score, upgradeCost, player.getMousePower());
                window.draw(upgradeButtonSprite);
				window.draw(shopButtonEnterSprite);
                window.draw(gumballSprite);
            }
            else if (isShopScene) {
                loadTexturesShop();
                window.draw(backgroundShopSprite);
                window.draw(shopButtonLeaveSprite);
                window.draw(item1.getSprite());
            }

            window.display();
        }
    }

    return false;
}