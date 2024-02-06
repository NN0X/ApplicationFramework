#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <chrono>

#include "vector.h"

namespace Utility
{
    void sleep(int milliseconds);

    void saveBinary(std::vector<double> doubles, std::string path);
    void saveBinary(std::vector<std::string> strings, std::string path);

    std::vector<double> loadBinaryDoubles(std::string path);
    std::vector<std::string> loadBinaryStrings(std::string path);
}