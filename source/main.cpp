/*
TODO:
    FIX HITBOX
    ADD SOUND
    ADD PARENT TRANSFORMS IN DRAW() FUNCTION
    REWRITE NDL AS LIB or DLL
    DITCH VISUAL STUDIO
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

#define WQHD 2560, 1440
#define FHD 1920, 1080
#define HD 1280, 720
#define SD 640, 480

int main()
{
    Application *app = new Application({1231, 556}, "Application", false, false, true);

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
    object2d.setPositionWindow({0.5, 0.5}, app->getSize());

    Object2D exitButton = Object2D(vertices2d, app->getSize(), "../resources/textures/default.png", "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    exitButton.setScale({0.1, 0.1});
    exitButton.setPositionWindow({1, 1}, app->getSize());

    int frames = 0;
    double start = glfwGetTime();

    app->addObject2D(object2d);
    app->addObject2D(exitButton);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isKeyPressed(KEY_W))
            app->getObject2D(1)->transformPosition({0, 0.0001});

        if (app->isKeyPressed(KEY_S))
            app->getObject2D(1)->transformPosition({0, -0.0001});

        if (app->isKeyPressed(KEY_A))
            app->getObject2D(1)->transformPosition({-0.0001, 0});

        if (app->isKeyPressed(KEY_D))
            app->getObject2D(1)->transformPosition({0.0001, 0});

        if (app->isKeyPressed(KEY_Q))
            app->getObject2D(1)->transformRotation(0.01);

        if (app->isKeyPressed(KEY_E))
            app->getObject2D(1)->transformRotation(-0.01);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D(1)->inHitbox(app->getMousePositionWorld()))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isMousePressed(MOUSE_RIGHT))
            app->getObject2D(1)->getPositionWorld().print();

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