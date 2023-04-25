// Copyright 2023 Thomas O'Connor
#include "Checkers.hpp"

// Getter
bool Checkers::isWon(void) {
    if (setWinTrue) return 1;
    bool r = 0, b = 0;
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        for (int j = 0; j < BOARD_DIMENSIONS; j++) {
            if (currentGameState[i][j] == 'r' ||
                currentGameState[i][j] == 'R')
                r = 1;
            if (currentGameState[i][j] == 'b' ||
                currentGameState[i][j] == 'B')
                b = 1;
            if ((r && b) || stillPlaying) return 0;
        }
    }
    return 1;
}

// Getter (ONLY CALL AFTER ISWON IS CONFIRMED)
bool Checkers::getWinner(void) {
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        for (int j = 0; j < BOARD_DIMENSIONS; j++) {
            // if a red piece exists, red wins
            if (currentGameState[i][j] == 'r' ||
                currentGameState[i][j] == 'R')
                return 1;
        }
    }
    // else black wins
    return 0;
}

// Interactor
void Checkers::selectPiece(sf::Vector2i mouseLocation) {
    // calculate the coordiate pair in relation to the 2D char array
    sf::Vector2i arenaLocation((mouseLocation.x - BOARD_OFFSET) / TILE_SIZE,
                (mouseLocation.y - BOARD_OFFSET) / TILE_SIZE);
    if (playerTurn) {
        // red turn
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'r') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'w';
            stillPlaying = 1;
            return;
        }
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'R') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'W';
            stillPlaying = 1;
            return;
        }
    } else {
        // black turn
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'b') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'w';
            stillPlaying = 1;
            return;
        }
        if (currentGameState[arenaLocation.y][arenaLocation.x] == 'B') {
            currentGameState[arenaLocation.y][arenaLocation.x] = 'W';
            stillPlaying = 1;
            return;
        }
    }
}

// Getter
sf::Vector2i Checkers::getSelectedPawn(void) {
    auto row_iter = std::find_if(currentGameState.begin(), currentGameState.end(),
        [](const vector<char>& row) {
        return std::find_if(row.begin(), row.end(), [](char c) {
            return (c == 'w' || c == 'W');
        }) != row.end();
    });
    if (row_iter != currentGameState.end()) {
        auto col_iter = std::find_if(row_iter->begin(), row_iter->end(), [](char c) {
            return (c == 'w' || c == 'W');
        });
        return sf::Vector2i(std::distance(currentGameState.begin(), row_iter),
                std::distance(row_iter->begin(), col_iter));
    } else {
        return sf::Vector2i();
    }
}

// Interactor
void Checkers::movePiece(sf::Vector2i mouseLocation) {
    // calculate the coordiate pair in relation to the 2D char array
    sf::Vector2i arenaLocation((mouseLocation.y - BOARD_OFFSET) / TILE_SIZE,
                (mouseLocation.x - BOARD_OFFSET) / TILE_SIZE);
    sf::Vector2i P = getSelectedPawn();
    if (P.x == 0 && P.y == 0) return;
    bool fourD = 0, moved = 0;
    if (currentGameState[P.x][P.y] == 'W') fourD = true;
    if (playerTurn) {
        // red pawn
        if (arenaLocation.x == P.x-1 && arenaLocation.y == P.y-1) {
            if (currentGameState[P.x-1][P.y-1] == 'p') {
                if (fourD) currentGameState[P.x-1][P.y-1] = 'R';
                else
                    currentGameState[P.x-1][P.y-1] = 'r';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x-1 && arenaLocation.y == P.y+1) {
            if (currentGameState[P.x-1][P.y+1] == 'p') {
                if (fourD) currentGameState[P.x-1][P.y+1] = 'R';
                else
                    currentGameState[P.x-1][P.y+1] = 'r';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x-2 && arenaLocation.y == P.y-2) {
            if ((currentGameState[P.x-1][P.y-1] == 'b' ||
                currentGameState[P.x-1][P.y-1] == 'B') &&
                currentGameState[P.x-2][P.y-2] == 'p') {
                if (fourD) currentGameState[P.x-2][P.y-2] = 'R';
                else
                    currentGameState[P.x-2][P.y-2] = 'r';
                currentGameState[P.x-1][P.y-1] = 'p';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x-2 && arenaLocation.y == P.y+2) {
            if ((currentGameState[P.x-1][P.y+1] == 'b' ||
                currentGameState[P.x-1][P.y+1] == 'B') &&
                currentGameState[P.x-2][P.y+2] == 'p') {
                if (fourD) currentGameState[P.x-2][P.y+2] = 'R';
                else
                    currentGameState[P.x-2][P.y+2] = 'r';
                currentGameState[P.x-1][P.y+1] = 'p';
                moved = 1;
            }
        }
        if (fourD) {
            if (arenaLocation.x == P.x+1 && arenaLocation.y == P.y-1) {
                if (currentGameState[P.x+1][P.y-1] == 'p') {
                    currentGameState[P.x+1][P.y-1] = 'R';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x+1 && arenaLocation.y == P.y+1) {
                if (currentGameState[P.x+1][P.y+1] == 'p') {
                    currentGameState[P.x+1][P.y+1] = 'R';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x+2 && arenaLocation.y == P.y-2) {
                if ((currentGameState[P.x+1][P.y-1] == 'b' ||
                    currentGameState[P.x+1][P.y-1] == 'B') &&
                    currentGameState[P.x+2][P.y-2] == 'p') {
                    currentGameState[P.x+2][P.y-2] = 'R';
                    currentGameState[P.x+1][P.y-1] = 'p';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x+2 && arenaLocation.y == P.y+2) {
                if ((currentGameState[P.x+1][P.y+1] == 'b' ||
                    currentGameState[P.x+1][P.y+1] == 'B') &&
                    currentGameState[P.x+2][P.y+2] == 'p') {
                    currentGameState[P.x+2][P.y+2] = 'R';
                    currentGameState[P.x+1][P.y+1] = 'p';
                    moved = 1;
                }
            }
        }
    } else {
        // black pawn
        if (arenaLocation.x == P.x+1 && arenaLocation.y == P.y-1) {
            if (currentGameState[P.x+1][P.y-1] == 'p') {
                if (fourD) currentGameState[P.x+1][P.y-1] = 'B';
                else
                    currentGameState[P.x+1][P.y-1] = 'b';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x+1 && arenaLocation.y == P.y+1) {
            if (currentGameState[P.x+1][P.y+1] == 'p') {
                if (fourD) currentGameState[P.x+1][P.y+1] = 'B';
                else
                    currentGameState[P.x+1][P.y+1] = 'b';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x+2 && arenaLocation.y == P.y-2) {
            if ((currentGameState[P.x+1][P.y-1] == 'r' ||
                currentGameState[P.x+1][P.y-1] == 'R') &&
                currentGameState[P.x+2][P.y-2] == 'p') {
                if (fourD) currentGameState[P.x+2][P.y-2] = 'B';
                else
                    currentGameState[P.x+2][P.y-2] = 'b';
                currentGameState[P.x+1][P.y-1] = 'p';
                moved = 1;
            }
        }
        if (arenaLocation.x == P.x+2 && arenaLocation.y == P.y+2) {
            if ((currentGameState[P.x+1][P.y+1] == 'r' ||
                currentGameState[P.x+1][P.y+1] == 'R') &&
                currentGameState[P.x+2][P.y+2] == 'p') {
                if (fourD) currentGameState[P.x+2][P.y+2] = 'B';
                else
                    currentGameState[P.x+2][P.y+2] = 'b';
                currentGameState[P.x+1][P.y+1] = 'p';
                moved = 1;
            }
        }
        if (fourD) {
            if (arenaLocation.x == P.x-1 && arenaLocation.y == P.y-1) {
                if (currentGameState[P.x-1][P.y-1] == 'p') {
                    currentGameState[P.x-1][P.y-1] = 'B';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x-1 && arenaLocation.y == P.y+1) {
                if (currentGameState[P.x-1][P.y+1] == 'p') {
                    currentGameState[P.x-1][P.y+1] = 'B';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x-2 && arenaLocation.y == P.y-2) {
                if ((currentGameState[P.x-1][P.y-1] == 'r' ||
                    currentGameState[P.x-1][P.y-1] == 'R') &&
                    currentGameState[P.x-2][P.y-2] == 'p') {
                    currentGameState[P.x-2][P.y-2] = 'B';
                    currentGameState[P.x-1][P.y-1] = 'p';
                    moved = 1;
                }
            }
            if (arenaLocation.x == P.x-2 && arenaLocation.y == P.y+2) {
                if ((currentGameState[P.x-1][P.y+1] == 'r' ||
                    currentGameState[P.x-1][P.y+1] == 'R') &&
                    currentGameState[P.x-2][P.y+2] == 'p') {
                    currentGameState[P.x-2][P.y+2] = 'B';
                    currentGameState[P.x-1][P.y+1] = 'p';
                    moved = 1;
                }
            }
        }
    }
    if (moved) {
        currentGameState[P.x][P.y] = 'p';
        finishLine();
        deselectPiece();
        switchTurn();
        stillPlaying = 0;
    }
}

// Interactor
void Checkers::deselectPiece(void) {
    sf::Vector2i P = getSelectedPawn();
    if (P.x == 0 && P.y == 0) return;
    if (playerTurn) {
        if (currentGameState[P.x][P.y] == 'W')
            currentGameState[P.x][P.y] = 'R';
        else
            currentGameState[P.x][P.y] = 'r';
        stillPlaying = 0;
        return;
    } else {
        if (currentGameState[P.x][P.y] == 'W')
            currentGameState[P.x][P.y] = 'B';
        else
            currentGameState[P.x][P.y] = 'b';
        stillPlaying = 0;
        return;
    }
}

// Interactor
void Checkers::restart(bool& winCondition) {
    initializeBase();
    playerTurn = 0;
    winCondition = 1;
    setWinTrue = 0;
    stillPlaying = 0;
}

// Performer
void Checkers::playSound(void) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("checkers/victory.wav")) exit(1);
    sf::Sound sound(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing) {
        // Wait for the sound to finish playing
    }
}

// Performer
void Checkers::visualMoveAssist(sf::RenderTarget &target) {
    sf::Texture star;
    if (!star.loadFromFile("checkers/star_icon.png")) exit(1);
    sf::Vector2i P = getSelectedPawn();
    if (P.x == 0 && P.y == 0) return;
    bool fourD = 0, moveable = 0;
    if (currentGameState[P.x][P.y] == 'W') fourD = true;
    if (playerTurn) {
        // red pawn
        if (P.x-1 >=0 && P.y-1 >=0) {
            if (currentGameState[P.x-1][P.y-1] == 'p') {
                drawStar(target, star, P.x-1, P.y-1);
                moveable = 1;
            }
        }
        if (P.x-2 >= 0 && P.y-2 >= 0) {
            if ((currentGameState[P.x-1][P.y-1] == 'b' ||
                currentGameState[P.x-1][P.y-1] == 'B') &&
                currentGameState[P.x-2][P.y-2] == 'p') {
                drawStar(target, star, P.x-2, P.y-2);
                moveable = 1;
            }
        }
        if (P.x-1 >=0 && P.y+1 < 8) {
            if (currentGameState[P.x-1][P.y+1] == 'p') {
                drawStar(target, star, P.x-1, P.y+1);
                moveable = 1;
            }
        }
        if (P.x-2 >= 0 && P.y+2 < 8) {
            if ((currentGameState[P.x-1][P.y+1] == 'b' ||
                currentGameState[P.x-1][P.y+1] == 'B') &&
                currentGameState[P.x-2][P.y+2] == 'p') {
                drawStar(target, star, P.x-2, P.y+2);
                moveable = 1;
            }
        }
        if (fourD) {
            if (P.x+1 < 8 && P.y-1 >=0) {
                if (currentGameState[P.x+1][P.y-1] == 'p') {
                    drawStar(target, star, P.x+1, P.y-1);
                    moveable = 1;
                }
            }
            if (P.x+2 < 8 && P.y-2 >= 0) {
                if ((currentGameState[P.x+1][P.y-1] == 'b' ||
                    currentGameState[P.x+1][P.y-1] == 'B') &&
                    currentGameState[P.x+2][P.y-2] == 'p') {
                    drawStar(target, star, P.x+2, P.y-2);
                    moveable = 1;
                }
            }
            if (P.x+1 < 8 && P.y+1 < 8) {
                if (currentGameState[P.x+1][P.y+1] == 'p') {
                    drawStar(target, star, P.x+1, P.y+1);
                    moveable = 1;
                }
            }
            if (P.x+2 < 8 && P.y+2 < 8) {
                if ((currentGameState[P.x+1][P.y+1] == 'b' ||
                    currentGameState[P.x+1][P.y+1] == 'B') &&
                    currentGameState[P.x+2][P.y+2] == 'p') {
                    drawStar(target, star, P.x+2, P.y+2);
                    moveable = 1;
                }
            }
        }
    } else {
        // black pawn
        if (P.x+1 < 8 && P.y-1 >=0) {
            if (currentGameState[P.x+1][P.y-1] == 'p') {
                drawStar(target, star, P.x+1, P.y-1);
                moveable = 1;
            }
        }
        if (P.x+2 < 8 && P.y-2 >= 0) {
            if ((currentGameState[P.x+1][P.y-1] == 'r' ||
                currentGameState[P.x+1][P.y-1] == 'R') &&
                currentGameState[P.x+2][P.y-2] == 'p') {
                drawStar(target, star, P.x+2, P.y-2);
                moveable = 1;
            }
        }
        if (P.x+1 < 8 && P.y+1 < 8) {
            if (currentGameState[P.x+1][P.y+1] == 'p') {
                drawStar(target, star, P.x+1, P.y+1);
                moveable = 1;
            }
        }
        if (P.x+2 < 8 && P.y+2 < 8) {
            if ((currentGameState[P.x+1][P.y+1] == 'r' ||
                currentGameState[P.x+1][P.y+1] == 'R') &&
                currentGameState[P.x+2][P.y+2] == 'p') {
                drawStar(target, star, P.x+2, P.y+2);
                moveable = 1;
            }
        }
        if (fourD) {
            if (P.x-1 >=0 && P.y-1 >=0) {
                if (currentGameState[P.x-1][P.y-1] == 'p') {
                    drawStar(target, star, P.x-1, P.y-1);
                    moveable = 1;
                }
            }
            if (P.x-2 >= 0 && P.y-2 >= 0) {
                if ((currentGameState[P.x-1][P.y-1] == 'r' ||
                    currentGameState[P.x-1][P.y-1] == 'R') &&
                    currentGameState[P.x-2][P.y-2] == 'p') {
                    drawStar(target, star, P.x-2, P.y-2);
                    moveable = 1;
                }
            }
            if (P.x-1 >=0 && P.y+1 < 8) {
                if (currentGameState[P.x-1][P.y+1] == 'p') {
                    drawStar(target, star, P.x-1, P.y+1);
                    moveable = 1;
                }
            }
            if (P.x-2 >= 0 && P.y+2 < 8) {
                if ((currentGameState[P.x-1][P.y+1] == 'r' ||
                    currentGameState[P.x-1][P.y+1] == 'R') &&
                    currentGameState[P.x-2][P.y+2] == 'p') {
                    drawStar(target, star, P.x-2, P.y+2);
                    moveable = 1;
                }
            }
        }
    }
    if (!moveable) {
        bool r = 0, b = 0;
        for (int i = 0; i < BOARD_DIMENSIONS; i++) {
            for (int j = 0; j < BOARD_DIMENSIONS; j++) {
                if (currentGameState[i][j] == 'r' ||
                    currentGameState[i][j] == 'R')
                    r = 1;
                if (currentGameState[i][j] == 'b' ||
                    currentGameState[i][j] == 'B')
                    b = 1;
            }
        }
        if (!(r && b)) setWinTrue = 1;
    }
}

// Performer
void Checkers::drawStar(sf::RenderTarget& target, sf::Texture star, int yc, int xc) {
    sf::Sprite icon;
    icon.setTexture(star);
    // -8 is an arbitrary offset to center the star on the tile
    icon.setOrigin(-8, -8);
    icon.setPosition(xc*TILE_SIZE+BOARD_OFFSET, yc*TILE_SIZE+BOARD_OFFSET);
    target.draw(icon);
}

// Draw game in SFML
void Checkers::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Load piece textures
    sf::Texture blackPiece, blackKing, redPiece, redKing, whitePiece, whiteKing, woodBacking;
    if (!blackPiece.loadFromFile("checkers/blackpawn.png")) exit(1);
    if (!redPiece.loadFromFile("checkers/redpawn.png")) exit(1);
    if (!whitePiece.loadFromFile("checkers/whitepawn.png")) exit(1);
    if (!blackKing.loadFromFile("checkers/blackking.png")) exit(1);
    if (!redKing.loadFromFile("checkers/redking.png")) exit(1);
    if (!whiteKing.loadFromFile("checkers/whiteking.png")) exit(1);
    if (!woodBacking.loadFromFile("checkers/wood_texture.png")) exit(1);
    sf::Sprite WB;
    WB.setTexture(woodBacking);
    // scale up wood textures
    WB.setScale(1, 1.2);
    // draw backing
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
                    R.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(R);
                    break;
                }
                case 'p':
                {
                    drawBackingRectangle(target, j, i);
                    break;
                }
                case 'r':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite RP;
                    RP.setTexture(redPiece);
                    RP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(RP);
                    break;
                }
                case 'b':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite BP;
                    BP.setTexture(blackPiece);
                    BP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(BP);
                    break;
                }
                case 'w':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite WP;
                    WP.setTexture(whitePiece);
                    // scale down white pieces to 64 x 64 pixels
                    WP.setScale(0.6, 0.6);
                    WP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(WP);
                    break;
                }
                case 'R':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite RP;
                    RP.setTexture(redKing);
                    RP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(RP);
                    break;
                }
                case 'B':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite BP;
                    BP.setTexture(blackKing);
                    BP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
                    target.draw(BP);
                    break;
                }
                case 'W':
                {
                    drawBackingRectangle(target, j, i);
                    sf::Sprite WP;
                    WP.setTexture(whiteKing);
                    // scale down white pieces to 64 x 64 pixels
                    WP.setScale(0.6, 0.6);
                    WP.setPosition(j * TILE_SIZE + BOARD_OFFSET, i * TILE_SIZE + BOARD_OFFSET);
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
void Checkers::initializeBase(void) {
    currentGameState.resize(BOARD_DIMENSIONS);
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        currentGameState[i].resize(BOARD_DIMENSIONS);
        for (int j = 0; j < BOARD_DIMENSIONS; j++) {
            // Draw red background tiles
            if (((j + (i%2))%2)) {
                if (i <= 2) {
                    // Black piece represented as 'b' (black)
                    // placed on lines 0 - 2
                    currentGameState[i][j] = 'b';
                } else if (i >= 5) {
                    // Red piece represented as 'r' (red)
                    // placed on lines 5 - 7
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

// Automatically king pawns at respective finish lines
void Checkers::finishLine(void) {
    for (int i = 0; i < BOARD_DIMENSIONS; i++) {
        if (!(i%2)) {
            // black pieces - 7 is last row
            if (currentGameState[7][i] == 'b') {
                currentGameState[7][i] = 'B';
                return;
            }
        } else {
            // red pieces - 0 is first row
            if (currentGameState[0][i] == 'r') {
                currentGameState[0][i] = 'R';
                return;
            }
        }
    }
}

// Helper function
bool mouseInGameBounds(sf::Vector2i mouseLocation) {
    if ((mouseLocation.x >= BOARD_OFFSET && mouseLocation.x <=
        TILE_SIZE * BOARD_DIMENSIONS + BOARD_OFFSET) &&
        (mouseLocation.y >= BOARD_OFFSET && mouseLocation.y <=
        TILE_SIZE * BOARD_DIMENSIONS + BOARD_OFFSET)) return 1;
    return 0;
}

// Performing helper function
void drawBackingRectangle(sf::RenderTarget& target, int x, int y) {
    sf::RectangleShape B;
    B.setSize(Vector2f(TILE_SIZE, TILE_SIZE));
    B.setFillColor(sf::Color::Black);
    B.setPosition(x * TILE_SIZE + BOARD_OFFSET, y * TILE_SIZE + BOARD_OFFSET);
    target.draw(B);
}
