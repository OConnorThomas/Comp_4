# PS6: RandWriter

## Contact
Name:           Thomas O'Connor
Section:        202
Time to Complete:   5 hours


## Description
Takes in a refrence text and generates and L-sized output
based on kgrams (k-sized partitions of the refrence text)
and the following characters in an order proportional to their
appearance in the text.

### Features
Implimented an unordered map for speed purposes.
This map contains the kgrams as the keys, linking to a pair
which contains the frequency of that kgram in int, and a string
containing the probability dictionary of the k+1grams for that kgram

### Testing
My code passed all the tests I wrote
I used BOOST_REQUIRE_EQUAL, BOOST_REQUIRE_THROW, and BOOST_REQUIRE_NO_THROW to
check for invalid_argument and out_of_range exceptions, and static equivalency on
the test string "gagggagaggcgagaaa" given constant expressions of known output.

### Lambda
Used no lambda funcitons

### Issues
Fully functional
I had to create a special case for order zero but that was easily implimented

### Extra Credit
N/A

## Acknowledgements
N/A
