// Copyright 2023 Thomas O'Connor
#include "Checkers.hpp"

int main(int argc, char* argv[]) {
    // Create game
    Checkers Game;
    bool performWinConditionOnce = 1;
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
        if (!Game.isWon()) {
            // Get Keyboard input and impliment correct movement
            window.clear();
            // Detect button press
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                mouseInGameBounds(sf::Mouse::getPosition(window))) {
                if (Game.nothingSelected())
                    Game.selectPiece(sf::Mouse::getPosition(window));
                else
                    Game.movePiece(sf::Mouse::getPosition(window));
            }
            // Deselect piece
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
                mouseInGameBounds(sf::Mouse::getPosition(window)))
                Game.deselectPiece();
            // Draw the basic gameboard
            window.draw(Game);
            // if piece selected, draw move assist
            if (!Game.nothingSelected())
                Game.visualMoveAssist(window);
            window.display();
        // if you've won, perform win fanfare
        } else if (performWinConditionOnce) {
            // Draw the win state
            std::string winString;
            if (Game.getWinner())
                winString = "Red wins";
            else
                winString = "Black wins";
            sf::Font font;
            font.loadFromFile("checkers/arial.ttf");
            sf::Text winText(winString, font, 30);
            winText.setFillColor(sf::Color::White);
            // Centers text to middle of screen
            winText.setPosition(sf::Vector2f(TILE_SIZE * 3.5, TILE_SIZE * 3.9));
            window.draw(winText);
            window.display();
            // Play win sound after screen display
            Game.playSound();
            // Ensures win sound is only performed once
            performWinConditionOnce = 0;
        }
        // Exit on (X) keypress
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) window.close();
        // Restart game on (R) keypress
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) Game.restart(performWinConditionOnce);
    }
    return 0;
}
