#ifndef FIB_LFSR
#define FIB_LFSR

#include <iostream>
#include <string>
#include <bitset>
#include <exception>

using namespace std;

class FibLFSR {
public:
    // Constructor to create LFSR with the given initial seed
    FibLFSR(string seed);

    // Simulate one step and return the new bit as 0 or 1
    int step();

    // Simulate k steps and return a k-bit integer
    int generate(int k);

    // Getters:
    string getState(void) const;
    const int* getTaps(void) const;

    // Helper functions:
    int XOR(int a, int b);
    bool notZeroOne(const string seed);

private:
    const int TAPS[4] = {15, 13, 12, 10};
    bitset<16> state;
};
ostream& operator<<(ostream& out, const FibLFSR& lfsr);

#endif