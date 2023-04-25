// Copyright 2023 Thomas O'Connor
#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using sf::Keyboard;
using std::cout;
using std::endl;
using std::pair;
using std::vector;

#define TILE_SIZE 64

enum Direction { UP, LEFT, DOWN, RIGHT };

class Sokoban : public sf::Drawable {
 public:
    // Constructors
    Sokoban() : _h(0), _w(0) {}
    Sokoban(int y, int x) : _h(y), _w(x) {}

    // Getters
    int getWidth() const { return _w; }
    int getHeight() const { return _h; }
    int getTurn() const { return turn; }

    // Display
    void drawElapsingTime(sf::RenderWindow &window, sf::Clock &clock);
    // Check and Display
    bool isWon() const;

    // Interactors
    void movePlayer(Direction dir);
    void restart(sf::Clock& clock);
    void undo();
    void playSound();

    // Overload extraction operator
    friend Sokoban& operator>>(Sokoban& game, std::ifstream& file);

 private:
    // Draw game in SFML
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    // Test for conditions
    bool noObstructions(Direction dir, int w, int h) const;
    bool canPushBox(Direction dir, int w, int h) const;
    // Push box if conditions are met
    void pushBox(Direction dir, int w, int h);

 private:
    // Game state stored in row-major order
    // Vector of 2D game states - 3rd dimension is time
    // Allows for "undo" actions
    vector<vector<vector<char>>> allGameStates;
    // Dimensions of the window/game (read from file)
    int _h, _w;
    // Turn number for keeping track of game states
    int turn = 0;
    // Direction the man faces
    vector<Direction> face;
};

// non-member helper functions
vector<vector<char>> deepCopy(const vector<vector<char>> &original);

#endif
