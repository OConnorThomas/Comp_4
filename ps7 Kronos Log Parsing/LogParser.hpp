// Copyright 2023 Thomas O'Connor
#ifndef LOGPARSER_HPP
#define LOGPARSER_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <SFML/System.hpp>

#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

using std::string;
using boost::posix_time::ptime;
using boost::posix_time::time_from_string;

class LogParser {
 public:
  // Constructor
  explicit LogParser(std::ifstream& log, const string& filePath) :
                      _referenceLog(log), _path(filePath) {}
  // generator function
  const string generateRPT() const;

 private:
  // log file
  std::ifstream& _referenceLog;
  // file path
  string _path;
};

#endif
