// Copyright 2023 Thomas O'Connor
#include "Checkers.hpp"

int main(int argc, char* argv[]) {
    // Create game
    Checkers Game;
    // Rednder the window using the appropriate game dimensions
    sf::RenderWindow window
    (sf::VideoMode(TILE_SIZE * BOARD_DIMENSIONS + TILE_SIZE,
        TILE_SIZE * BOARD_DIMENSIONS + TILE_SIZE), "Checkers");
    window.setFramerateLimit(120);

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) window.close();
        }
        // Clear screen
        window.clear();
        // Draw the basic gameboard
        window.draw(Game);
        // Detect button press
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
            mouseInGameBounds(sf::Mouse::getPosition(window)))
            Game.selectPiece(sf::Mouse::getPosition(window));
        window.display();
        // Exit on (X) keypress
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) window.close();
        // Switch player turns
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) Game.switchTurn();
    }
    return 0;
}
