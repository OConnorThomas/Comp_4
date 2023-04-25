// Copyright 2023 Thomas O'Connor
#include "LogParser.hpp"

int main(int argc, char* argv[]) {
    // Command-line arguments
    string filePath = argv[1];

    // Open file and check for failure
    std::ifstream myLog;
    myLog.open(filePath);
    if (!myLog) exit(1);
    std::ofstream myRpt(filePath + ".rpt");
    if (!myRpt) exit(1);

    LogParser object(myLog, filePath);
    myRpt << object.generateRPT();

    myLog.close();
    myRpt.close();

    return 0;
}
