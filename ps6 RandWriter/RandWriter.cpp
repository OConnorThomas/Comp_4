// Copyright 2023 Thomas O'Connor
#include "RandWriter.hpp"

// Constructor:
RandWriter::RandWriter(string text, int k) : _K(k) {
    // if order 0, the text IS the dictionary of probabilities
    if (!k) {
        MarkovModel[ORDERZERO].second.assign(text);
        MarkovModel[ORDERZERO].first = static_cast<int>(text.size());
    }
    // else
    // Append the first k+1 characters to the end of the text
    string kgram = text.substr(0, k+1);
    text.append(kgram);
    kgram.pop_back();
    // for each char in the text, generate a kgram
    // starting with the first k-characters:
    for (size_t i = k; i < text.size()-1; i++) {
        // at this kgram push back the following char
        // into the personal dictionary for that kgram
        MarkovModel[kgram].first++;
        MarkovModel[kgram].second.push_back(text[i]);
        // generate new kgram
        cycleString(kgram, text[i]);
    }
    // the MarkovModel is now full of kgrams
    // and personal probability dictionaries
}

// Number of occurences of kgram in text
// Throw an exception if kgram is not length k
int RandWriter::freq(string kgram) const {
    if (kgram.size() != static_cast<size_t>(_K)) {
        throw std::invalid_argument("String length != k in FREQ");
    } else {
        if (!_K) kgram = ORDERZERO;
        return MarkovModel.at(kgram).first;
    }
}

// Number of times that character c follows kgram
// if order=0, return num of times that char c appears
// (throw an exception if kgram is not of length k)
int RandWriter::freq(string kgram, char c) const {
    if (kgram.size() != static_cast<size_t>(_K)) {
        throw std::invalid_argument("String length != k in FREQ");
    } else {
        if (!_K) kgram = ORDERZERO;
        return std::count(MarkovModel.at(kgram).second.begin(),
                          MarkovModel.at(kgram).second.end(), c);
    }
}

// Random character following given kgram
// (throw an exception if kgram is not of length k)
// (throw an exception if no such kgram)
char RandWriter::kRand(string kgram) {
    if (kgram.size() != static_cast<size_t>(_K)) {
        throw std::invalid_argument("String length != k in KRAND");
    } else {
        // check for order zero
        if (!_K) kgram = ORDERZERO;
        // get bounds of dictionary
        int lengthOfDictionary = MarkovModel.at(kgram).second.size() - 1;
        // set randomizing variables
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, lengthOfDictionary);
        return MarkovModel.at(kgram).second[distrib(gen)];
    }
}

// Generate a string of length L characters by simulating a trajectory
// through the corresponding Markov chain. The first k characters of
// the newly generated string should be the argument kgram.
// Throw an excpetion if kgram is not of length k.
// Assume that L is at least k
string RandWriter::generate(string kgram, int L) {
    if (kgram.size() != static_cast<size_t>(_K)) {
        throw std::invalid_argument("String length != k in GENERATE " + kgram);
    }
    string outputString;
    char newItem;
    for (int i = 0; i < L; i++) {
        newItem = kRand(kgram);
        outputString.push_back(newItem);
        cycleString(kgram, newItem);
    }
    outputString.push_back('\n');
    return outputString;
}

// Overload the stream insertion operator << and display the internal state
// of the Markov model. Print out the order, alphabet, and the frequencies
// of the k-grams and k+1-grams
std::ostream& operator<<(std::ostream& out, RandWriter& obj) {
    out << "Order: " << obj.orderK() << endl;
    for (auto const &outerMap : obj.MarkovModel) {
        cout << "Kgram:  " << outerMap.first << "  Frequency:  " << outerMap.second.first;
        cout << "  Dictionary:  " << outerMap.second.second << endl;
        list<char> usedChars;
        for (char kp1gram : outerMap.second.second) {
            // if it could not find the element in the used chars list, create a k+1 gram
            if (std::find(usedChars.begin(), usedChars.end(), kp1gram) == usedChars.end()) {
                cout << "|\tK+1gram:  " << outerMap.first << kp1gram << "  Frequency:  " <<
                    std::count(outerMap.second.second.begin(),
                    outerMap.second.second.end(), kp1gram)
                    << endl;
                usedChars.push_back(kp1gram);
            }
        }
    }
    return out;
}

// helper funcion
void cycleString(string& str, char item) {
    if (!str.size()) return;
    str.erase(0, 1);
    str.push_back(item);
}
