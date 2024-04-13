#ifndef UTILITY_H
#define UTILITY_H

#include "include.h"
#include "defines.h"
#include "log.h"

namespace Utility
{
    void wait(uInt milliseconds);

    void saveBinary(std::vector<double> doubles, std::string path);
    void saveBinary(std::vector<std::string> strings, std::string path);

    std::vector<double> loadBinaryDoubles(std::string path);
    std::vector<std::string> loadBinaryStrings(std::string path);

    void genFontFiles();
}

#endif // UTILITY_H