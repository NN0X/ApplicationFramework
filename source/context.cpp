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
    cameras.clear();
    objects2d.clear();
    objects3d.clear();
}

void Context::createParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case 0:
        cameras[instances[child].second].setParent(parent);
        break;
    case 2:
        objects2d[instances[child].second].setParent(parent);
        break;
    case 3:
        objects3d[instances[child].second].setParent(parent);
        break;
    }

    switch (instances[parent].first)
    {
    case 0:
        cameras[instances[parent].second].addChild(child);
        break;
    case 2:
        objects2d[instances[parent].second].addChild(child);
        break;
    case 3:
        objects3d[instances[parent].second].addChild(child);
        break;
    }
}

void Context::destroyParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case 0:
        cameras[instances[child].second].setParent(-1);
        break;
    case 2:
        objects2d[instances[child].second].setParent(-1);
        break;
    case 3:
        objects3d[instances[child].second].setParent(-1);
        break;
    }

    switch (instances[parent].first)
    {
    case 0:
        cameras[instances[parent].second].removeChild(child);
        break;
    case 2:
        objects2d[instances[parent].second].removeChild(child);
        break;
    case 3:
        objects3d[instances[parent].second].removeChild(child);
        break;
    }
}

void Context::addCamera(const Camera &camera)
{
    cameras.push_back(camera);
    instances.push_back({0, int(cameras.size()) - 1});
    cameras[cameras.size() - 1].setIndex(instances.size() - 1);
}

Camera *Context::getCamera(int index)
{
    return &cameras[index];
}

void Context::destroyCamera(int index)
{
    cameras.erase(cameras.begin() + index);
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

void Context::addObject3D(const Object3D &object)
{
    objects3d.push_back(object);
    instances.push_back({3, int(objects3d.size()) - 1});
    objects3d[objects3d.size() - 1].setIndex(instances.size() - 1);
}

Object3D *Context::getObject3D(int index)
{
    return &objects3d[index];
}

void Context::destroyObject3D(int index)
{
    objects3d.erase(objects3d.begin() + index);
}

void Context::draw()
{
    for (Object2D &object : objects2d)
        object.draw();
    for (Object3D &object : objects3d)
        object.draw(cameras[currentCamera].getCameraMatrix());
}
