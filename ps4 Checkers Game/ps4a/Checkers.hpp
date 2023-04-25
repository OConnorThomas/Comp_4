// Copyright 2023 Thomas O'Connor
#ifndef CHECKERS_HPP
#define CHECKERS_HPP

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::endl;
using std::vector;
using sf::Vector2f;

#define TILE_SIZE 64
#define BOARD_DIMENSIONS 8

class Checkers : public sf::Drawable {
 public:
  // Constructors
  Checkers() { initializeBase(); }

  // Interactors
  void selectPiece(sf::Vector2i mouseLocation);
  void switchTurn(void) { playerTurn = !playerTurn; }
 private:
  // Draw game in SFML
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  // Initialize game storage vectors
  void initializeBase();
 private:
  vector<vector<char>> currentGameState;
  bool playerTurn = 0;
};

// Helper functions
bool mouseInGameBounds(sf::Vector2i mouseLocation);

#endif
