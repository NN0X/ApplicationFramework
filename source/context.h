#pragma once

#include <vector>

#include "object.h"

class Context
{
private:
    int currentCamera;
    std::vector<std::pair<int, int>> instances;
    std::vector<Camera> cameras;
    std::vector<Object2D> objects2d;
    std::vector<Object3D> objects3d;

public:
    Context();
    ~Context();

    void createParentage(int parent, int child);
    void destroyParentage(int parent, int child);

    void addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);
    void destroyObject2D(int index);

    void addObject3D(const Object3D &object);
    Object3D *getObject3D(int index);
    void destroyObject3D(int index);

    void addCamera(const Camera &camera);
    Camera *getCamera(int index);
    void destroyCamera(int index);

    void draw();
};