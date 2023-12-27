#include "context.h"

/*types:
    0 - camera
    2 - object2d
    3 - object3d
*/

Context::Context()
{
    currentCamera = 0;
}

Context::~Context()
{
    instances.clear();
    objects2d.clear();
}

void Context::createParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case 2:
        objects2d[instances[child].second].setParent(parent);
        break;
    }

    switch (instances[parent].first)
    {
    case 2:
        objects2d[instances[parent].second].addChild(child);
        break;
    }
}

void Context::destroyParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case 2:
        objects2d[instances[child].second].setParent(-1);
        break;
    }

    switch (instances[parent].first)
    {
    case 2:
        objects2d[instances[parent].second].removeChild(child);
        break;
    }
}

void Context::addObject2D(const Object2D &object)
{
    objects2d.push_back(object);
    instances.push_back({2, int(objects2d.size()) - 1});
    objects2d[objects2d.size() - 1].setIndex(instances.size() - 1);
}

Object2D *Context::getObject2D(int index)
{
    return &objects2d[index];
}

void Context::destroyObject2D(int index)
{
    objects2d.erase(objects2d.begin() + index);
}

void Context::draw()
{
    for (Object2D &object : objects2d)
        object.draw();
}
