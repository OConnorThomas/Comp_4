// Copyright 2023 Thomas O'Connor
#include <SFML/Graphics.hpp>

using sf::Keyboard;

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1024, 1024), "Man");
    window.setFramerateLimit(120);

    // Load a sprite to display
    sf::Texture textureBase;
    if (!textureBase.loadFromFile("sprite.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(textureBase);
    sprite.setPosition(200, 200);
    sprite.setScale(1, 1);

    // Load a circle to display
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // Declare offset variables
    int xOffset = 0, yOffset = 0;

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        // Process keystrokes
        if (Keyboard::isKeyPressed(Keyboard::Right)) xOffset = 1;
        if (Keyboard::isKeyPressed(Keyboard::Left)) xOffset = -1;
        if (Keyboard::isKeyPressed(Keyboard::Up)) yOffset = -1;
        if (Keyboard::isKeyPressed(Keyboard::Down)) yOffset = 1;

        if (Keyboard::isKeyPressed(Keyboard::Equal))
            sprite.scale(1.05, 1.05);
        if (Keyboard::isKeyPressed(Keyboard::Hyphen))
            sprite.scale(0.95, 0.95);

        // Offset the sprite
        sprite.move(xOffset, yOffset);

        // Draw the sprite
        window.draw(sprite);
        window.draw(shape);

        // Reset Offset values
        xOffset = 0; yOffset = 0;

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
