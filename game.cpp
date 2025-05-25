#include "game.h"
#include "player.h"
#include "item.h"

Game::Game() {
	upgradeCost = 1.0f;
    isMainScene = true;
    isShopScene = false;
}

bool Game::loadTexturesMain() {
    if (!backgroundTexture.loadFromFile("textures/background_main.png")) {
        std::cerr << "ERROR: Could not load backround image.";
        return false;
    }

    if (!upgradeButtonTexture.loadFromFile("textures/upgrade_button.png")) {
        std::cerr << "ERROR: Could not load button image.";
        return false;
    }

	if (!shopButtonEnterTexture.loadFromFile("textures/shop.png")) {
		std::cerr << "ERROR: Could not load shop image.";
		return false;
	}

    if (!gumballTexture.loadFromFile("textures/gumball_pixel.png")) {
        std::cerr << "ERROR: Could not load gumball image.";
        return false;
    }

    // Set the texture rect for the button sprite
    upgradeButtonSprite.setTexture(upgradeButtonTexture);
    upgradeButtonSprite.setPosition(25.0f, 60.0f);

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
    if (!backgroundShopTexture.loadFromFile("textures/background_shop.png")) {
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

bool Game::runGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GumbaLL");
	Game game;
    Player player;

    sf::Texture rmtTexture;
    sf::Texture bananaTexture;

    if (!rmtTexture.loadFromFile("textures/rmt.png")) {
        std::cerr << "Failed to load RMT texture\n";
    }
    if (!bananaTexture.loadFromFile("textures/bananas.png")) {
        std::cerr << "Failed to load BANANAS texture\n";
    }

    std::vector<Item> items;
    items.emplace_back(10.0f, "RMT", std::move(rmtTexture), 2, 0);
    items.emplace_back(20.0f, "BANANAS", std::move(bananaTexture), 0, 0.02);

    textsMain = TextsMain();
    if (!(loadTexturesMain() && textsMain.perfromSetupMain())) {
        std::cout << "ERROR: Couldn't perfrom main scene setup.";
        return 1;
    }

    textsShop = TextsShop();
    if (!(loadTexturesShop() && textsShop.perfromSetupTextShop(items))) {
        std::cout << "ERROR: Couldn't perfrom shop scene setup.";
        return 1;
    }

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
                    if (player.getScore() >= game.getUpgradeCost()) {
                        player.setScore(player.getScore() - game.getUpgradeCost());
                        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
                        player.setMousePower(player.getMousePower() + player.getMousePower() * UPGRADE_CONSTANT);//setereeee
                        player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f); // Round to 2 decimal places
                        game.setUpgradeCost(std::ceil(game.getUpgradeCost() + 1.755f * game.getUpgradeCost() * UPGRADE_CONSTANT));
                    }
                }
                if (isMainScene && gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
					if (player.getCriticalChance() > static_cast<float>(rand() % 100) / 100.0f) {
                        player.setScore(player.getScore() + player.getMousePower() * 2);// Critical hit
                        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
                        //reset srand
						srand(static_cast<unsigned int>(time(0))); // Reset the random seed
					}
                    else {
                        player.setScore(player.getScore() + player.getMousePower());
                        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
                    }
                }
                else if (isMainScene && !isShopScene && shopButtonEnterSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 0;
                    isShopScene = 1;
                }
                else if (!isMainScene && isShopScene && shopButtonLeaveSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 1;
                    isShopScene = 0;
                }
                else if (!isMainScene && isShopScene && items[0].getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
					if (player.getScore() >= items[0].getCost()) {
						player.setScore(player.getScore() - items[0].getCost());
						player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
						player.setMousePower(player.getMousePower() + items[0].getMousePower());
						player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f);
					}
				}
                else if (!isMainScene && isShopScene && items[1].getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                {
                    if (player.getScore() >= items[1].getCost()) {
                        player.setScore(player.getScore() - items[1].getCost());
                        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
                        player.setCriticalChance(player.getCriticalChance() + items[1].getCriticalChance());
                        player.setCriticalChance(std::round(player.getCriticalChance() * 100.0f) / 100.0f);
                    }
                }
            }
            window.clear();
			if (isMainScene) {
				// Draw main scene
				window.draw(backgroundSprite);
				window.draw(gumballSprite);
				window.draw(upgradeButtonSprite);
				window.draw(shopButtonEnterSprite);
				textsMain.drawInGameTextsMain(&window, player.getScore(), game.getUpgradeCost(), player.getMousePower(), player.getCriticalChance());
			}
            else {
                window.draw(backgroundShopSprite);
                window.draw(shopButtonLeaveSprite);
                textsShop.drawInGameTextsShop(&window, items, player.getScore(), player.getMousePower(), player.getCriticalChance());
                for (size_t i = 0; i < items.size(); ++i) {
                    sf::Sprite& sprite = items[i].getSprite();
					if (i == 1)
						sprite.setPosition(450.0f + i * 250.0f, 400.0f);// banana
					else
                    sprite.setPosition(450.0f + i * 250.0f, 360.0f);
                    window.draw(sprite);
                }
            }
            window.display();
        }
    }

    return false;
}