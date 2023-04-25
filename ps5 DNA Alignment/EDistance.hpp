// Copyright 2023 Thomas O'Connor
#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <list>
#include <utility>
#include <SFML/System.hpp>

using std::cout;
using std::endl;
using std::pair;
using std::setw;
using std::string;

class EDistance {
 public:
  // Constructor + Destructor
  EDistance(const string& lOp, const string& rOp);
  ~EDistance () { delete [] matrix; }

  // interactor functions
  int penalty(char a, char b) const { return a != b; }
  int min(int a, int b, int c) const;
  int optDistance();
  string alignment();

  // debug functions
  void printMatrix();

 private:
  int* matrix;
  std::list<pair<int, int>> optPath;
  // dimensions of the matrix, string.size()+1; N = x; M = y;
  int _M, _N;
  string _MString, _NString;
};

#endif
