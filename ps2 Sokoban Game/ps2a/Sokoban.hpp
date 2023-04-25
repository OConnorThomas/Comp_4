// Copyright 2023 Thomas O'Connor
#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::endl;

#define TILE_SIZE 64

class Sokoban : public sf::Drawable {
 public:
    // Constructors
    Sokoban() : _h(0), _w(0) {}
    Sokoban(int y, int x) : _h(y), _w(x) {}

    // Getters
    int getWidth() const { return _w; }
    int getHeight() const { return _h; }
    void getGameState() const;

    // Display
    void drawElapsingTime(sf::RenderWindow &window, sf::Clock &clock);

    // Interactors
    void movePlayer(Sokoban &game, sf::Keyboard::Key key);

    // Overload extraction operator
    friend Sokoban& operator>>(Sokoban& game, std::ifstream& file);

 private:
    // Draw game in SFML
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

 private:
    // Game state stored in row-major order
    std::vector<std::vector<char>> gameState;
    // Dimensions of the window/game (read from file)
    int _h, _w;
};
#endif
