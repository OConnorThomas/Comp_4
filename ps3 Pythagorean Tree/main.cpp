// Copyright 2023 Thomas O'Connor
#include "PTree.hpp"

int main(int argc, char* argv[]) {
    // Command line arguments
    double lengthL = atof(argv[1]);
    int depthN = atoi(argv[2]);

    // Create tree and input values from cmd line args
    PTree tree(lengthL, depthN);

    // Rednder the window using the appropriate game dimensions
    sf::RenderWindow window(sf::VideoMode(tree.getLengthL() * 6, tree.getLengthL() * 4), "PTree");
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
        window.draw(tree);
        window.display();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) window.close();
    }
    return 0;
}
