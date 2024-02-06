#pragma once

#include <vector>

#include "object.h"

enum Type
{
    OBJECT2D = 2,
    FONT = 3
};
class Context
{
private:
    std::vector<std::pair<int, int>> instances;
    std::vector<Object2D> objects2d;
    std::vector<Font> fonts;

public:
    Context();
    ~Context();

    void createParentage(int parent, int child);
    void destroyParentage(int parent, int child);

    int addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);

    int addFont(const Font &font);
    Font *getFont(int index);

    void destroyInstance(int index);
    void clearInstances();
    std::vector<std::pair<int, int>> getInstances();

    void draw();
};