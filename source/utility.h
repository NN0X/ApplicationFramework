#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "vector.h"

namespace Utility
{
    std::vector<double> loadOBJ(std::string path);

    dVector2 getCenter2(const std::vector<double> &vertices);
    dVector3 getCenter3(const std::vector<double> &vertices);
}