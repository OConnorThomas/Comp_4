// Copyright 2023 Thomas O'Connor
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    // Command line arguments
    std::string inputFileName = argv[1];
    // Open file and check for failure
    std::ifstream myLevel;
    myLevel.open(inputFileName);
    if (!myLevel) exit(1);

    // Create game and input values from file
    Sokoban Game;
    Game >> myLevel;

    // Rednder the window using the appropriate game dimensions
    sf::RenderWindow window
    (sf::VideoMode(TILE_SIZE * Game.getWidth(),
    TILE_SIZE * Game.getHeight()), "Sokoban");
    window.setFramerateLimit(120);
    sf::Clock clock;

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) window.close();
        }
        // Clear screen
        window.clear();
        // Draw the basic arena
        window.draw(Game);
        Game.drawElapsingTime(window, clock);
        window.display();
    }
    return 0;
}
