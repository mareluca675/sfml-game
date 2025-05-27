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
    items.reserve(3);   // ← prevent reallocations

    sf::Texture rmtTexture, bananaTexture, rubberDuckTexture;
    if (!rmtTexture.loadFromFile("textures/rmt.png") ||
        !bananaTexture.loadFromFile("textures/bananas.png") ||
        !rubberDuckTexture.loadFromFile("textures/rubber_duck.png"))
    {
        std::cerr << "Failed to load an item texture\n";
        return {};
    }

    // Now each emplace_back goes directly into its final slot.
    items.emplace_back(1.0f, "RMT", std::move(rmtTexture), 0.1f, 0.0f);
    items.emplace_back(1.0f, "Banana", std::move(bananaTexture), 0.2f, 0.00025f);
    items.emplace_back(1.0f, "Rubber Duck", std::move(rubberDuckTexture), 0.3f, 0.005f);

    // Now set up scenes
    textsMain = TextsMain();
    if (!(loadTexturesMain() && textsMain.perfromSetupMain())) {
        std::cerr << "ERROR: Couldn't perform main scene setup.\n";
        return {};
    }

    textsShop = TextsShop();
    if (!(loadTexturesShop() && textsShop.perfromSetupTextShop(items))) {
        std::cerr << "ERROR: Couldn't perform shop scene setup.\n";
        return {};
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
        // Not enough score
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
    if (items.empty()) return false;

    while (window.isOpen()) {
        // 1) Process ALL events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }

            // Reset "Not enough score" text after 0.75s
            if (clock.getElapsedTime().asSeconds() > 0.75f &&
                textsMain.upgrade.getString() == "Not enough score") {
                textsMain.upgrade.setString("Upgrade");
            }

            // Mouse-click handling
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {

                sf::Vector2f mp = window.mapPixelToCoords(
                    { event.mouseButton.x, event.mouseButton.y });

                if (isMainScene && upgradeButtonSprite.getGlobalBounds().contains(mp)) {
                    upgradeMousePower(window, player);
                    clock.restart();
                }
                else if (isMainScene && gumballSprite.getGlobalBounds().contains(mp)) {
                    gainScore(player);
                }
                else if (isMainScene && shopButtonEnterSprite.getGlobalBounds().contains(mp)) {
                    isMainScene = false;
                    isShopScene = true;
                }
                else if (isShopScene && shopButtonLeaveSprite.getGlobalBounds().contains(mp)) {
                    isMainScene = true;
                    isShopScene = false;
                }
                else if (isShopScene) {
                    for (auto& item : items) {
                        if (item.getSprite().getGlobalBounds().contains(mp) &&
                            player.getScore() >= item.getCost()) {
                            player.buyItem(item);
                        }
                    }
                }
            }
        }

        // 2) Clear, draw, display *every frame* (outside pollEvent)
        window.clear();
        if (isMainScene)
            drawMainScene(window, player);
        else
            drawShopScene(window, player, items);
        window.display();
    }

    return true;
}