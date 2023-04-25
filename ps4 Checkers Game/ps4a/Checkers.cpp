// Copyright 2023 Thomas O'Connor
#include "Checkers.hpp"

// Interactors
void Checkers::selectPiece(sf::Vector2i mouseLocation) {
    // calculate the coordiate pair in relation to the 2D char array
    int R = 0, B = 0;
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < BOARD_DIMENSIONS; i++) {
            for (int j = 0; j < BOARD_DIMENSIONS; j++) {
                if (k == 0) {
                    if (currentGameState[i][j] == 'r') R++;
                    if (currentGameState[i][j] == 'b') B++;
                } else {
                    if (currentGameState[i][j] == 'w' && R == 11) {
                        currentGameState[i][j] = 'r';
                        break;
                    } else if (currentGameState[i][j] == 'w' && B == 11) {
                        currentGameState[i][j] = 'b';
                        break;
                    }
                }
            }
        }
    }
    sf::Vector2i arenaLocation((mouseLocation.x - 32) / 64, (mouseLocation.y - 32) / 64);
    if (playerTurn) {
        // red turn
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'r') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'w';
            return;
        }
    } else {
        // black turn
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'b') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'w';
            return;
        }
    }
}

// Draw game in SFML
void Checkers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Load piece textures
    sf::Texture blackPiece, redPiece, whitePiece, woodBacking;
    if (!blackPiece.loadFromFile("checkers/blackpawn.png")) exit(1);
    if (!redPiece.loadFromFile("checkers/redpawn.png")) exit(1);
    if (!whitePiece.loadFromFile("checkers/whitepawn.png")) exit(1);
    if (!woodBacking.loadFromFile("checkers/wood_texture.png")) exit(1);
    sf::Sprite WB;
    WB.setTexture(woodBacking);
    WB.setScale(1, 1.2);
    target.draw(WB);
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        for (int j = 0; j < BOARD_DIMENSIONS; j++) {
            // Draw states stored in currentGameState
            switch (currentGameState[i][j]) {
                case '.':
                {
                    sf::RectangleShape R;
                    R.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
                    R.setFillColor(sf::Color::Red);
                    R.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(R);
                    break;
                }
                case 'p':
                {
                    sf::RectangleShape B;
                    B.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
                    B.setFillColor(sf::Color::Black);
                    B.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(B);
                    break;
                }
                case 'r':
                {
                    sf::RectangleShape B;
                    B.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
                    B.setFillColor(sf::Color::Black);
                    B.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(B);
                    sf::Sprite RP;
                    RP.setTexture(redPiece);
                    RP.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(RP);
                    break;
                }
                case 'b':
                {
                    sf::RectangleShape B;
                    B.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
                    B.setFillColor(sf::Color::Black);
                    B.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(B);
                    sf::Sprite BP;
                    BP.setTexture(blackPiece);
                    BP.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(BP);
                    break;
                }
                case 'w':
                {
                    sf::RectangleShape B;
                    B.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
                    B.setFillColor(sf::Color::Black);
                    B.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(B);
                    sf::Sprite WP;
                    WP.setTexture(whitePiece);
                    WP.setScale(0.6, 0.6);
                    WP.setPosition(j * TILE_SIZE + TILE_SIZE/2, i * TILE_SIZE + TILE_SIZE/2);
                    target.draw(WP);
                    break;
                }
            }
        }
    }
    sf::Font font;
    font.loadFromFile("checkers/arial.ttf");
    sf::Text turnText("", font, 40);
    turnText.setFillColor(sf::Color::White);
    turnText.setPosition(Vector2f(10, 0));
    if (playerTurn) {
        // Red turn
        turnText.setString("R");
    } else {
        // Black turn
        turnText.setString("B");
    }
    target.draw(turnText);
}

// Initialize game storage vectors
void Checkers::initializeBase() {
    currentGameState.resize(BOARD_DIMENSIONS);
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        currentGameState[i].resize(BOARD_DIMENSIONS);
        for (int j = 0; j < BOARD_DIMENSIONS; j++) {
            // Draw red background tiles
            if (((j + (i%2))%2)) {
                if (i <= 2) {
                    // Black piece represented as 'b' (black)
                    currentGameState[i][j] = 'b';
                } else if (i >= 5) {
                    // Red piece represented as 'r' (red)
                    currentGameState[i][j] = 'r';
                } else {
                    // Black background tile represented 'p' (playable)
                    currentGameState[i][j] = 'p';
                }
            } else {
                // Red background tile represented as '.' (invalid)
                currentGameState[i][j] = '.';
            }
        }
    }
}

bool mouseInGameBounds(sf::Vector2i mouseLocation) {
    if ((mouseLocation.x >= 32 && mouseLocation.x <= TILE_SIZE * 8 + 32) &&
    (mouseLocation.y >= 32 && mouseLocation.y <= TILE_SIZE * 8 + 32)) return 1;
    return 0;
}
