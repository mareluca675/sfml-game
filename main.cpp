#include <SFML/Graphics.hpp>
#include <iostream>

int score;

int main()
{
    // Create a window with title and dimensions
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    // Creating a font
    sf::Font font;

	// Load a font from a file
	if (!font.loadFromFile("fonts\\arial.ttf"))
	{
		std::cerr << "Error loading font" << std::endl;
		return -1;
	}

	// Creating a text object to display the score
	sf::Text text;

    // Set the string to the score
	text.setString("Score: " + std::to_string(score));

	// Set the font of the text
	text.setFont(font);

	// Set the character size
	text.setCharacterSize(24);

	// Set the color of the text
	text.setFillColor(sf::Color::White);

	// Set the position of the text
	text.setPosition(10, 10);

	// Set the text style
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Main loop: keep window open until closed
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if user closes it
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				// Update the score
                ++score;

				// Update the text with the new score
                text.setString("Score: " + std::to_string(score));
            }
        }

		// Clear the window with black color
		// so as the text is visible and
		// doesn't overlap with the previous frame
		window.clear(sf::Color::Black);

        // Display the score
		window.draw(text);

        // Display the updated window
        window.display();
    }

    return 0;
}
