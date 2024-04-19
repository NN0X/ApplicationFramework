#ifndef UTILITY_H
#define UTILITY_H

#include "include.h"
#include "defines.h"
#include "log.h"

namespace Utility
{
    void wait(uInt milliseconds);

    uInt genID();
    uInt genUniqueID();

    void saveBinary(const std::vector<double> &doubles, const std::string &path);
    void saveBinary(const std::vector<std::string> &strings, const std::string &path);

    std::vector<double> loadBinaryDoubles(const std::string &path);
    std::vector<std::string> loadBinaryStrings(const std::string &path);

    void genFontFiles();
}

#endif // UTILITY_H