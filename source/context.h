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

    // all object types should be merged into single functions

    int addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);
    Object2D *getObject2D(std::string label);

    int addFont(const Font &font);
    Font *getFont(int index);
    Font *getFont(std::string label);

    void destroyInstance(int index);
    void clearInstances();
    std::vector<std::pair<int, int>> getInstances();

    void draw();
};