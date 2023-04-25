# PS1: LFSR

## Contact
Name:               Thomas O'Connor
Section:            202
Time to Complete:   6 hours

## Description
A class FibLFSR that creates a bitset of 16 bits for generating
pseudo-random strings

### Features
I used a bitset because it is an easy to use, low impact structure
with easy bit shifting and accessor functions. 

### Issues
No issues, proper exception throwing for edge cases

### Tests
Test 3 length_error - parameter length != 16
Test 4 invalid_argument - parameter contains !1 && !0
Test 5 Both length_error and invalid_argument

## Acknowledgements
Website for bitsets: https://en.cppreference.com/w/cpp/utility/bitset