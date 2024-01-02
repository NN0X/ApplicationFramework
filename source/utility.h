#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "vector.h"

namespace Utility
{
    void saveVertices2D(std::vector<double> vertices, std::string path);
    std::vector<double> loadVertices2D(std::string path);
}