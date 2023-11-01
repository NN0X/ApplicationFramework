/*
TODO:
    ADD GUI INPUT
    ADD SOUND
    ADD PARENT TRANSFORMS IN DRAW() FUNCTION
    REWRITE NDL AS LIB or DLL
    DITCH VISUAL STUDIO
    SETUP GITHUB
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include "utility.h"
#include "application.h"

int main()
{
    Application *app = new Application({1000, 1000}, "Application", false, false, true);

    std::vector<double> vertices2d = {
        0.5, 0.5, 1.0, 1.0,   //
        0.5, -0.5, 1.0, 0.0,  //
        -0.5, 0.5, 0.0, 1.0,  //
        0.5, -0.5, 1.0, 0.0,  //
        -0.5, -0.5, 0.0, 0.0, //
        -0.5, 0.5, 0.0, 1.0   //
    };

    Object2D object2d = Object2D(vertices2d, app->getSize(), "../resources/textures/logo.png", "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    object2d.setScale({0.5, 0.5});
    object2d.setPosition({0.5, 0});

    std::vector<double> vertices3d;

    vertices3d = Utility::loadOBJ("../resources/meshes/cube.obj");

    Object3D object3d = Object3D(vertices3d, "../resources/textures/logo.png", "../resources/shaders/default3dVertex.glsl", "../resources/shaders/default3dFragment.glsl");
    object3d.setPosition({0.5, 0, 0});
    object3d.setScale({0.25, 0.25, 0.25});

    // FIX
    Camera camera = Camera({0, 0, 0}, {0, 0, 0}, 45, 1, 0.1, 1000);
    // FIX

    int frames = 0;
    double start = glfwGetTime();

    // app->addCamera(camera);
    app->addObject2D(object2d);
    // app->addObject3D(object3d);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        // app->getObject3D(0)->transformRotation({0.001, 0.001, 0.001});
        app->update();
        frames++;
    }

    double end = glfwGetTime();
    double sum = end - start;

    app->destroyWindow();

    std::cout << "Total Frames:    " << frames << "\n";
    std::cout << "Total Time:      " << sum << "s\n";
    std::cout << "Average FPS:     " << frames / sum << "\n";
    std::cin.get();
}