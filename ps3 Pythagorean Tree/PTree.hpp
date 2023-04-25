// Copyright 2023 Thomas O'Connor
#ifndef PTREE_HPP
#define PTREE_HPP

#include <cmath>
#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using std::cout;
using std::endl;
using std::pair;
using sf::RectangleShape;
using sf::Vector2f;

class PTree : public sf::Drawable, sf::Transformable {
 public:
    // Constructors
    PTree() : _L(0), _N(0) {}
    PTree(double L, int N);

    // Getters
    int getDepthN() const { return _N; }
    double getLengthL() const { return _L; }

 private:
    // Draw game in SFML
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    // Recursive draw function
    void pTree(sf::RenderTarget& target,
      pair<Vector2f, Vector2f> newPoints, int depthN,
      float angleR) const;
 private:
    double _L;
    int _N;
};

// Debugger functions
void drawIndicators(sf::RenderTarget& target, pair<Vector2f, Vector2f> newPoints);
void drawIndicator(sf::RenderTarget& target, Vector2f point);

#endif
