#pragma once

#include <vector>

#include "object.h"

class Context
{
private:
    std::vector<std::pair<int, int>> instances;
    std::vector<Object2D> objects2d;

public:
    Context();
    ~Context();

    void createParentage(int parent, int child);
    void destroyParentage(int parent, int child);

    void addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);
    void destroyObject2D(int index);

    void draw();
};