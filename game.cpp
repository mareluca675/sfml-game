#include "game.h"
#include "player.h"
#include "item.h"
Item item1;
Item item2;
Game::Game() {
	upgradeCost = 1.0f;
	score = 0.0f;
    isMainScene = true;
    isShopScene = false;
}

bool Game::loadTexturesMain() {
    if (!backgroundTexture.loadFromFile("textures/newbackground.png")) {
        std::cerr << "ERROR: Could not load backround image.";
        return false;
    }

    if (!upgradeButtonTexture.loadFromFile("textures/upgradeButton.png")) {
        std::cerr << "ERROR: Could not load button image.";
        return false;
    }

	if (!shopButtonEnterTexture.loadFromFile("textures/Shop.png")) {
		std::cerr << "ERROR: Could not load shop image.";
		return false;
	}

    if (!gumballTexture.loadFromFile("textures/gumball_pixel.png")) {
        std::cerr << "ERROR: Could not load gumball image.";
        return false;
    }

    // Set the texture rect for the button sprite
    upgradeButtonSprite.setTexture(upgradeButtonTexture);
    upgradeButtonSprite.setPosition(25.0f, 50.0f);

    // Set the texture rect for the gumball sprite
    gumballSprite.setTexture(gumballTexture);
    gumballSprite.setPosition(WINDOW_WIDTH / 2.0f - 50, WINDOW_HEIGHT / 2.0f - 50);

    // Set the texture rect for the background sprite
    shopButtonEnterSprite.setTexture(shopButtonEnterTexture);
    shopButtonEnterSprite.setPosition(1110.0f, 379.0f);

    // Set the texture rect for the background sprite
    backgroundSprite.setTexture(backgroundTexture);
    return true;
}

bool Game::loadTexturesShop() {
    if (!backgroundShopTexture.loadFromFile("textures/backgroundShop.png")) {
        std::cerr << "ERROR: Could not load shop image.";
        return false;
    }
    if (!shopButtonLeaveTexture.loadFromFile("textures/door.png")) {
        std::cerr << "ERROR: Could not load shop image.";
        return false;
    }

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
	Game game;
    try {
        item1.setTexture("textures/rmt.png");
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return false;
    }

    item1.setName("carte");
    item1.setCost(10.0f);
    item1.setCriticalChance(0.5f);
    item1.setSpritePosition(WINDOW_WIDTH / 2.0f - 50, WINDOW_HEIGHT / 2.0f - 50);

    Player player;
    Item rmt(100.0f, "RMT", "textures/rmt.png");

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
                    if (game.getScore() >= game.getUpgradeCost()) {
                        game.setScore(game.getScore() - game.getUpgradeCost());
                        game.setScore(std::round(game.getScore() * 100.0f) / 100.0f);
                        player.setMousePower(player.getMousePower() + player.getMousePower() * UPGRADE_CONSTANT);//setereeee
                        player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f); // Round to 2 decimal places
                        game.setUpgradeCost(std::ceil(game.getUpgradeCost() + 1.755f * game.getUpgradeCost() * UPGRADE_CONSTANT));
                    }
                }
                if (isMainScene && gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
                    game.setScore(game.getScore() + player.getMousePower());
                    game.setScore(std::round(game.getScore() * 100.0f) / 100.0f);
                }
                else if (isMainScene && !isShopScene && shopButtonEnterSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 0;
                    isShopScene = 1;
                }
                else if (!isMainScene && isShopScene && shopButtonLeaveSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 1;
                    isShopScene = 0;
                }
                else if (isShopScene && !isMainScene && rmt.getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)) && game.getScore() >= rmt.getCost()) 
					player.equipItem(rmt);
					rmt.buyItem(rmt, game);
                }
            }

            window.clear();

            if (isMainScene) {
                loadTexturesMain();
                window.draw(backgroundSprite);
                textsMain.drawInGameTextsMain(&window, game.getScore(), game.getUpgradeCost(), player.getMousePower());
                window.draw(upgradeButtonSprite);
				window.draw(shopButtonEnterSprite);
                window.draw(gumballSprite);
            }
            else if (isShopScene) {
                loadTexturesShop();
                textsShop.drawInGameTextsShop(&window, item1.getName(), item1.getCost(), item2.getName(), item2.getCost());
                window.draw(backgroundShopSprite);
                window.draw(shopButtonLeaveSprite);
                window.draw(rmt.getSprite());
            }

            window.display();
        }
    }

    return false;
}