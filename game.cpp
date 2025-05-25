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
    gumballSprite.setPosition(WINDOW_WIDTH / 2.0f - 69.0f, WINDOW_HEIGHT / 2.0f - 69.0f);

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

std::vector<Item> Game::getItems() {
	std::vector<Item> items;

	// Textures for items
    sf::Texture rmtTexture;
	sf::Texture bananaTexture;
	sf::Texture rubberDuckTexture;

    if (!rmtTexture.loadFromFile("textures/rmt.png")) {
        std::cerr << "Failed to load RMT texture.";
		return std::vector<Item>(); // Return empty vector on failure
    }

    if (!bananaTexture.loadFromFile("textures/bananas.png")) {
        std::cerr << "Failed to load BANANAS texture.";
        return std::vector<Item>(); // Return empty vector on failure
    }

	if (!rubberDuckTexture.loadFromFile("textures/rubber_duck.png")) {
		std::cerr << "Failed to load Rubber Duck texture.";
		return std::vector<Item>(); // Return empty vector on failure
	}

	// Create items with textures and properties
	Item rmt(1.0f, "RMT", std::move(rmtTexture), 0.1f, 0.0f);
	//rmt.setTexture(rmtTexture); // Set texture for RMT item

	Item banana(1.0f, "Banana", std::move(bananaTexture), 0.2f, 0.0f);
	//banana.setTexture(bananaTexture); // Set texture for Banana item

	Item rubberDuck(1.0f, "Rubber Duck", std::move(rubberDuckTexture), 0.3f, 0.0f);
	//rubberDuck.setTexture(rubberDuckTexture); // Set texture for Rubber Duck item

	// Add items to the vector
	items.push_back(rmt);
	items.push_back(banana);
	items.push_back(rubberDuck);

    textsMain = TextsMain();
    if (!(loadTexturesMain() && textsMain.perfromSetupMain())) {
        std::cout << "ERROR: Couldn't perfrom main scene setup.";
        return std::vector<Item>();
    }

    textsShop = TextsShop();
    if (!(loadTexturesShop() && textsShop.perfromSetupTextShop(items))) {
        std::cout << "ERROR: Couldn't perfrom shop scene setup.";
        return std::vector<Item>();
    }

    return items;
}

void Game::drawMainScene(sf::RenderWindow &window, Player &player) {
    // Draw main scene
    window.draw(backgroundSprite);
    window.draw(gumballSprite);
    window.draw(upgradeButtonSprite);
    window.draw(shopButtonEnterSprite);
    textsMain.drawInGameTextsMain(&window, player.getScore(), getUpgradeCost(), player.getMousePower(), player.getCriticalChance(), level);
}

void Game::drawShopScene(sf::RenderWindow &window, Player &player, std::vector<Item> &items) {
    window.draw(backgroundShopSprite);
    window.draw(shopButtonLeaveSprite);

    int index = 0;
    for (Item &item : items) {
        item.getSprite().setPosition(150.0f + index * 250.0f, 250.0f);
        window.draw(item.getSprite());
        ++index;
    }

    textsShop.drawInGameTextsShop(&window, items, player.getScore(), player.getMousePower(), player.getCriticalChance());
}

// Upgrade mouse power function
void Game::upgradeMousePower(sf::RenderWindow& window, Player& player) {
    // Check if player has enough score to upgrade
    if (player.getScore() >= getUpgradeCost()) {
        // Deduct score
        player.setScore(player.getScore() - getUpgradeCost());
        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);

        // Increase mouse power
        player.setMousePower(player.getMousePower() + player.getMousePower() * UPGRADE_CONSTANT);
        player.setMousePower(std::round(player.getMousePower() * 100.0f) / 100.0f);

        // Update upgrade cost
        upgradeCost = std::ceil(getUpgradeCost() + 1.755f * getUpgradeCost() * UPGRADE_CONSTANT);

        // Increase level
        ++level;
    }
    else {
        // Not enough score, show message for half a second
        textsMain.upgrade.setString("Not enough score");
    }
}

void Game::gainScore(Player &player) {
    // Increment score by mousePower
    if (player.getCriticalChance() > static_cast<float>(rand() % 100) / 100.0f) {
        player.setScore(player.getScore() + player.getMousePower() * 2);// Critical hit
        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
        srand(static_cast<unsigned int>(time(0))); // Reset the random seed
    }
    else {
        player.setScore(player.getScore() + player.getMousePower());
        player.setScore(std::round(player.getScore() * 100.0f) / 100.0f);
    }
}

bool Game::runGame() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Gumballicker");
    Player player;
    sf::Clock clock;
    std::vector<Item> items = getItems();

	// Display items for debbugging purposes
	for (const auto& item : items) {
		std::cout << "Item: " << item.getName() << ", Cost: " << item.getCost()
			<< ", Mouse Power: " << item.getMousePower()
			<< ", Critical Chance: " << item.getCriticalChance() << std::endl;
	}

	if (items.empty()) {
		return false;
	}

    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window event
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check if we need to update the upgrade button text after a click
            if (clock.getElapsedTime().asSeconds() > 0.75 && textsMain.upgrade.getString() == "Not enough score") {
                textsMain.upgrade.setString("Upgrade");
            }

            // Mouse button pressed event
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // Get mouse position relative to the window
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if the upgrade button was clicked
                if (isMainScene && upgradeButtonSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					// Upgrade mouse power
                    upgradeMousePower(window, player);
                    clock.restart();
                }

				// Check if gumball was clicked
                if (isMainScene && gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
					// Gain score when gumball is clicked
					gainScore(player);
				}

				// Check if shop button was clicked
                if (isMainScene && shopButtonEnterSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 0;
                    isShopScene = 1;
                }
                else if (isShopScene && shopButtonLeaveSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    isMainScene = 1;
                    isShopScene = 0;
                }

				// Check if items were clicked using a for loop
				for (size_t i = 0; i < items.size(); ++i) {
					if (isShopScene && items[i].getSprite().getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
						std::cout << "Item " << i << " clicked: " << items[i].getName() << std::endl;
						player.buyItem(items[i]);
					}
				}

            }

            window.clear();

			if (isMainScene) {
                drawMainScene(window, player);
			}
            else {
				drawShopScene(window, player, items);
            }

            window.display();
        }
    }

    return false;
}