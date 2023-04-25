// Copyright 2023 Thomas O'Connor
#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <SFML/System.hpp>

#define ORDERZERO "refrence_text"

using std::cout;
using std::endl;
using std::list;
using std::pair;
using std::string;
using std::unordered_map;

class RandWriter {
 public:
  // Create a Markov model of order k from given text
  // Assume that text has length at least k.
  RandWriter(string text, int k);

  // Order k of Markov model
  int orderK() const { return _K; }

  // Number of occurences of kgram in text
  // Throw an exception if kgram is not length k
  int freq(string kgram) const;

  // Number of times that character c follows kgram
  // if order=0, return num of times that char c appears
  // (throw an exception if kgram is not of length k)
  int freq(string kgram, char c) const;

  // Random character following given kgram
  // (throw an exception if kgram is not of length k)
  // (throw an exception if no such kgram)
  char kRand(string kgram);

  // Generate a string of length L characters by simulating a trajectory
  // through the corresponding Markov chain. The first k characters of
  // the newly generated string should be the argument kgram.
  // Throw an excpetion if kgram is not of length k.
  // Assume that L is at least k
  string generate(string kgram, int L);

  // Overload the stream insertion operator << and display the internal state
  // of the Markov model. Print out the order, alphabet, and the frequencies
  // of the k-grams and k+1-grams
  friend std::ostream& operator<<(std::ostream& out, RandWriter& obj);

 private:
  int _K;
  // key is kgram, data is frequency of that kgram
  // and probability alphabet/dictionary of kgram
  unordered_map<string, pair<int, string>> MarkovModel;
};

// helper function
void cycleString(string& str, char item);

#endif
