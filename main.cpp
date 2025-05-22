#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include <sstream>

// Constants
const float UPGRADE_CONSTANT = 0.2f;
const unsigned int WINDOW_WIDTH = 1280;
const unsigned int WINDOW_HEIGHT = 720;
const unsigned int FRAME_RATE_LIMIT = 60;

// Function to format float to two decimal places
std::string formatFloat(float value) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(2) << value;
    return out.str();
}

int main() {
    // Initialize game variables
    float score = 0.0f;
    float mousePower = 1.0f;
    float upgradeCost = 1.0f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Idle Clicker");
    window.setFramerateLimit(FRAME_RATE_LIMIT);

    // Load button texture
    sf::Texture buttonTexture;
    if (!buttonTexture.loadFromFile("textures/button.png")) {
        std::cerr << "Error loading button texture" << std::endl;
        return -1;
    }

    // Create button sprite
    sf::Sprite buttonSprite;
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setPosition(10.0f, 100.0f);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }
    
    // Create a backround texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("textures/background.png")) {
        std::cerr << "Error loading background texture" << std::endl;
    }

	// Create a sprite for the background
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setPosition(0.0f, 0.0f);

    // Create a gumball texture
    sf::Texture gumballTexture;
    if (!gumballTexture.loadFromFile("textures/gumball.png")) {
        std::cerr << "Error loading background texture" << std::endl;
    }

    // Create a gumball sprite
    sf::Sprite gumballSprite;
    gumballSprite.setTexture(gumballTexture);
    gumballSprite.setPosition((WINDOW_WIDTH / 2) - 60, (WINDOW_HEIGHT / 2) - 50);

    // Create score text
    sf::Text textScore;
    textScore.setFont(font);
    textScore.setCharacterSize(24);
    textScore.setFillColor(sf::Color::Red);
    textScore.setPosition(10.0f, 10.0f);
    textScore.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textScore.setString("Score: 0");

    // Create upgrade cost text
	sf::Text textUpgradeCost;
	textUpgradeCost.setFont(font);
	textUpgradeCost.setCharacterSize(24);
	textUpgradeCost.setFillColor(sf::Color::Red);
	textUpgradeCost.setPosition(10.0f, WINDOW_HEIGHT - 50.0f);
	textUpgradeCost.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textUpgradeCost.setString("Upgrade Cost: " + formatFloat(upgradeCost));

	// Create mouse power text
	sf::Text textMousePower;
	textMousePower.setFont(font);
	textMousePower.setCharacterSize(24);
	textMousePower.setFillColor(sf::Color::Red);
    textMousePower.setPosition(10.0f, WINDOW_HEIGHT - 80.0f);
	textMousePower.setStyle(sf::Text::Bold | sf::Text::Underlined);
	textMousePower.setString("Mouse Power: " + formatFloat(mousePower));

    // Create FPS text
    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::Red);
    fpsText.setPosition(WINDOW_WIDTH - 100.0f, 10.0f); // Temporary position

    // Clock for measuring frame time
    sf::Clock frameClock;
    sf::Clock fpsUpdateClock;
    float fps = 0.0f;

    // Main loop
    while (window.isOpen()) {
        // Measure time since last frame
        float deltaTime = frameClock.restart().asSeconds();

        // Update FPS every 0.5 seconds
        if (fpsUpdateClock.getElapsedTime().asSeconds() >= 0.5f) {
            fps = 1.0f / deltaTime;
            fpsText.setString("FPS: " + formatFloat(fps));
            fpsText.setPosition(WINDOW_WIDTH - fpsText.getLocalBounds().width - 10.0f, 10.0f);
            fpsUpdateClock.restart();
        }

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
						textMousePower.setString("Mouse Power: " + formatFloat(mousePower));
                        upgradeCost = std::ceil(upgradeCost + 1.755f * upgradeCost * UPGRADE_CONSTANT);
                        textUpgradeCost.setString("Upgrade Cost: " + formatFloat(upgradeCost));
                    }
                }
                else if (gumballSprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    // Increment score by mousePower
                    score += mousePower;
                    score = std::round(score * 100.0f) / 100.0f;
                }

                // Update score text
                textScore.setString("Score: " + formatFloat(score));
            }
        }

        // Clear the window
        window.clear(sf::Color::Red);

        // Draw elements
        window.draw(backgroundSprite);
        window.draw(fpsText);
        window.draw(textScore);
		window.draw(textUpgradeCost);
		window.draw(textMousePower);
        window.draw(buttonSprite);
        window.draw(gumballSprite);
        
        // Display the contents of the window
        window.display();
    }

    return 0;
}
