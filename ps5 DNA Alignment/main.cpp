// Copyright 2023 Thomas O'Connor
#include "EDistance.hpp"

int main(int argc, char* argv[]) {
    string stringA, stringB;
    std::cin >> stringA;
    std::cin >> stringB;
    // start a clock before edit distance is computed
    sf::Clock clock;
    sf::Time t;
    // create the object and compute the distance
    EDistance a(stringA, stringB);
    cout << "Edit distance = " << a.optDistance() << endl;
    cout << a.alignment();
    // a.printMatrix();
    // print elapsed time
    t = clock.getElapsedTime();
    cout << "Execution time is " << t.asSeconds() << " seconds \n";

    return 0;
}
