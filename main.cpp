#include <SFML/Graphics.hpp>

int main()
{
    // Create a window with title and dimensions
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test");

    // Main loop: keep window open until closed
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if user closes it
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen with blue color
        window.clear(sf::Color::Blue);

        // Display the updated window
        window.display();
    }

    return 0;
}
