// Copyright 2023 Thomas O'Connor
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    // Command-line arguments
    int k = atoi(argv[1]);
    int l = atoi(argv[2]);

    // get all lines of refrence text
    string line, refrenceText;
    while (std::getline(std::cin, line))
        refrenceText.append(line);

    // create the RandWriter object
    RandWriter item(refrenceText, k);

    // output the internal state of the Markov model
    // cout << item;

    // generate an L sized output of text
    cout << item.generate(refrenceText.substr(0, k), l);

    return 0;
}
