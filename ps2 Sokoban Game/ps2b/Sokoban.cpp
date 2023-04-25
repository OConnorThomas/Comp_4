// Copyright 2023 Thomas O'Connor
#include "Sokoban.hpp"

// Extract the entire gameState into the Sokoban object
Sokoban& operator>>(Sokoban& game, std::ifstream& file) {
    file >> game._h; file >> game._w;
    game.face.resize(game.turn + 1);
    game.face[0] = DOWN;
    game.allGameStates.resize(game.turn + 1);
    // Given game dimensions, resize 2D vector and input from file
    game.allGameStates[game.turn].resize(game._h);
    for (int i = 0; i < game._h; i++) {
        game.allGameStates[game.turn][i].resize(game._w);
        for (int j = 0; j < game._w; j++) {
            file >> game.allGameStates[game.turn][i][j];
        }
    }
    return game;
}

bool Sokoban::isWon() const {
    auto it = std::find_if(allGameStates[turn].begin(), allGameStates[turn].end(),
        [](const std::vector<char>& row) { return std::any_of(row.begin(), row.end(),
        [](char c) { return c == 'A' || c == '2'; });
    });
    if (it != allGameStates[turn].end()) return false;
    else
    return true;
}

// Moves the player given a direction
void Sokoban::movePlayer(Direction dir) {
    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            // When find player, check for no obstructions and execute action
            if (allGameStates[turn][i][j] == '@' || allGameStates[turn][i][j] == '2') {
                if (noObstructions(dir, j, i)) {
                    // If no obstructions, create a new turn and a new game state
                    turn++;
                    allGameStates.resize(turn + 1);
                    allGameStates[turn] = deepCopy(allGameStates[turn - 1]);
                    face.resize(turn + 1);
                    face[turn] = dir;
                    if (allGameStates[turn][i][j] == '2') allGameStates[turn][i][j] = 'a';
                    else
                    allGameStates[turn][i][j] = '.';
                    if (canPushBox(dir, j, i)) pushBox(dir, j, i);
                    switch (dir) {
                        // UP
                        case 0:
                         if (allGameStates[turn][i-1][j] == 'a') allGameStates[turn][i-1][j] = '2';
                         else
                         allGameStates[turn][i-1][j] = '@';
                         break;
                        // LEFT
                        case 1:
                         if (allGameStates[turn][i][j-1] == 'a') allGameStates[turn][i][j-1] = '2';
                         else
                         allGameStates[turn][i][j-1] = '@';
                         break;
                        // DOWN
                        case 2:
                         if (allGameStates[turn][i+1][j] == 'a') allGameStates[turn][i+1][j] = '2';
                         else
                         allGameStates[turn][i+1][j] = '@';
                         break;
                        // RIGHT
                        case 3:
                         if (allGameStates[turn][i][j+1] == 'a') allGameStates[turn][i][j+1] = '2';
                         else
                         allGameStates[turn][i][j+1] = '@';
                         break;
                    }
                    return;
                }
            }
        }
    }
}

// Restarts the game when 'R' is pressed
void Sokoban::restart(sf::Clock& clock) {
    turn = 0;
    clock.restart();
    }

// Reverts back to the previous game state
void Sokoban::undo() { if (turn) turn--; }

void Sokoban::playSound() {
    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            if (allGameStates[turn][i][j] == 'A' || allGameStates[turn][i][j] == '2') return;
        }
    }
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("sokoban/victory.wav")) exit(1);
    sf::Sound sound(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing) {
        // Wait for the sound to finish playing
    }
}

// Check if there is a wall or double boxes
bool Sokoban::noObstructions(Direction dir, int w, int h) const {
    switch (dir) {
        // UP
        case 0:
         // Out of game bounds
         if (!h) return false;
         // Wall
         if (allGameStates[turn][h-1][w] == '#') return false;
         // Full Storage
         if (allGameStates[turn][h-1][w] == '1') return false;
         // Double boxes / Box - wall / Box - storage / Box - EOL
         if (allGameStates[turn][h-1][w] == 'A' && (h == 1)) return false;
         if (allGameStates[turn][h-1][w] == 'A' && (
             allGameStates[turn][h-2][w] == 'A' ||
             allGameStates[turn][h-2][w] == '#' ||
             allGameStates[turn][h-2][w] == '1')) return false;
         break;
        // LEFT
        case 1:
         // Out of game bounds
         if (!w) return false;
         // Full Storage
         if (allGameStates[turn][h][w-1] == '1') return false;
         // Check for wall
         if (allGameStates[turn][h][w-1] == '#') return false;
         // Double boxes / Box - wall / Box - storage / Box - EOL
         if (allGameStates[turn][h][w-1] == 'A' && (
             allGameStates[turn][h][w-2] == 'A' ||
             allGameStates[turn][h][w-2] == '#' ||
             allGameStates[turn][h][w-2] == '1' ||
             (w == 1))) return false;
         break;
        // DOWN
        case 2:
         // Out of game bounds
         if (!(_h-h-1)) return false;
         // Full Storage
         if (allGameStates[turn][h+1][w] == '1') return false;
         // Wall
         if (allGameStates[turn][h+1][w] == '#') return false;
         // Double boxes / Box - wall / Box - storage / Box - EOL
         if (allGameStates[turn][h+1][w] == 'A' && (h+2 == _h)) return false;
         if (allGameStates[turn][h+1][w] == 'A' && (
             allGameStates[turn][h+2][w] == 'A' ||
             allGameStates[turn][h+2][w] == '#' ||
             allGameStates[turn][h+2][w] == '1')) return false;
         break;
        // RIGHT
        case 3:
         // Out of game bounds
         if (!(_w-w-1)) return false;
         // Full Storage
         if (allGameStates[turn][h][w+1] == '1') return false;
         // Wall
         if (allGameStates[turn][h][w+1] == '#') return false;
         // Double boxes / Box - wall / Box - storage / Box - EOL
         if (allGameStates[turn][h][w+1] == 'A' && (
             allGameStates[turn][h][w+2] == 'A' ||
             allGameStates[turn][h][w+2] == '#' ||
             allGameStates[turn][h][w+2] == '1' ||
             (w+2 == _w))) return false;
         break;
    }
    return true;
}

bool Sokoban::canPushBox(Direction dir, int w, int h) const {
    switch (dir) {
        // UP
        case 0:
         // Box - empty / Box - storage
         if (allGameStates[turn][h-1][w] == 'A' && (
             allGameStates[turn][h-2][w] == '.' ||
             allGameStates[turn][h-2][w] == 'a')) return true;
         break;
        // LEFT
        case 1:
         // Box - empty / Box - storage
         if (allGameStates[turn][h][w-1] == 'A' && (
             allGameStates[turn][h][w-2] == '.' ||
             allGameStates[turn][h][w-2] == 'a')) return true;
         break;
        // DOWN
        case 2:
         // Box - empty / Box - storage
         if (allGameStates[turn][h+1][w] == 'A' && (
             allGameStates[turn][h+2][w] == '.' ||
             allGameStates[turn][h+2][w] == 'a')) return true;
         break;
        // RIGHT
        case 3:
         // Box - empty / Box - storage
         if (allGameStates[turn][h][w+1] == 'A' && (
             allGameStates[turn][h][w+2] == '.' ||
             allGameStates[turn][h][w+2] == 'a')) return true;
         break;
    }
    return false;
}

void Sokoban::pushBox(Direction dir, int w, int h) {
    switch (dir) {
        // UP
        case 0:
         if (allGameStates[turn][h-2][w] == '.') allGameStates[turn][h-2][w] = 'A';
         if (allGameStates[turn][h-2][w] == 'a') allGameStates[turn][h-2][w] = '1';
         break;
        // LEFT
        case 1:
         if (allGameStates[turn][h][w-2] == '.') allGameStates[turn][h][w-2] = 'A';
         if (allGameStates[turn][h][w-2] == 'a') allGameStates[turn][h][w-2] = '1';
         break;
        // DOWN
        case 2:
         if (allGameStates[turn][h+2][w] == '.') allGameStates[turn][h+2][w] = 'A';
         if (allGameStates[turn][h+2][w] == 'a') allGameStates[turn][h+2][w] = '1';
         break;
        // RIGHT
        case 3:
         if (allGameStates[turn][h][w+2] == '.') allGameStates[turn][h][w+2] = 'A';
         if (allGameStates[turn][h][w+2] == 'a') allGameStates[turn][h][w+2] = '1';
         break;
        return;
    }
}

// Overload the virtual draw function:
// Load required textures and display in window at prescribed locations
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Texture Wall, Box, WinBox, Empty, Storage, ManDown, ManUp, ManLeft, ManRight;
    if (!Wall.loadFromFile("sokoban/block_06.png")) exit(1);
    if (!Box.loadFromFile("sokoban/crate_03.png")) exit(1);
    if (!WinBox.loadFromFile("sokoban/crate_04.png")) exit(1);
    if (!Empty.loadFromFile("sokoban/ground_01.png")) exit(1);
    if (!Storage.loadFromFile("sokoban/environment_03.png")) exit(1);
    if (!ManDown.loadFromFile("sokoban/player_05.png")) exit(1);
    if (!ManUp.loadFromFile("sokoban/player_08.png")) exit(1);
    if (!ManLeft.loadFromFile("sokoban/player_20.png")) exit(1);
    if (!ManRight.loadFromFile("sokoban/player_17.png")) exit(1);

    for (int i = 0; i < _h; i++) {
        for (int j = 0; j < _w; j++) {
            sf::RectangleShape tile;
            tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
            // Draw wall tile
            if (allGameStates[turn][i][j] == '#') {
                tile.setTexture(&Wall);
            // Draw empty tile
            } else if (allGameStates[turn][i][j] == '.') {
                tile.setTexture(&Empty);
            // Draw background tile and overlay
            } else {
                sf::RectangleShape backTile;
                backTile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                backTile.setPosition(j * TILE_SIZE, i * TILE_SIZE);
                backTile.setTexture(&Empty);
                target.draw(backTile);
                switch (allGameStates[turn][i][j]) {
                    case 'a':
                     tile.setTexture(&Storage);
                     break;
                    case 'A':
                     tile.setTexture(&Box);
                     break;
                    case '1':
                     tile.setTexture(&WinBox);
                     break;
                    default:
                     // Based on face turn, select appropriate texture
                     if (face[turn] == DOWN) tile.setTexture(&ManDown);
                     if (face[turn] == UP) tile.setTexture(&ManUp);
                     if (face[turn] == LEFT) tile.setTexture(&ManLeft);
                     if (face[turn] == RIGHT) tile.setTexture(&ManRight);
                     break;
                }
            }
            target.draw(tile);
        }
    }
}

// Function that displays time in upper-left corner
void Sokoban::drawElapsingTime(sf::RenderWindow &window, sf::Clock &clock) {
    sf::Time elapsed = clock.getElapsedTime();
    int minutes = elapsed.asSeconds() / 60;
    int seconds = static_cast<int>(elapsed.asSeconds()) % 60;

    std::string timeString = std::to_string(minutes) + ":" +
    (seconds < 10 ? "0" : "") + std::to_string(seconds);

    sf::Font font;
    font.loadFromFile("sokoban/arial.ttf");
    sf::Text timeText(timeString, font, 30);
    timeText.setFillColor(sf::Color::White);

    window.draw(timeText);
}

// non-member helper functions:
// performs a deep copy of the game state
vector<vector<char>> deepCopy(const vector<vector<char>> &original) {
    vector<vector<char>> copy;
    for (const auto &row : original) copy.push_back(row);
    return copy;
}
