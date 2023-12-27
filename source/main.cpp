/*
TODO:
    FIX COORDINATES BASED ON WINDOW SIZE
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
    Application *app = new Application({800, 800}, "Application", false, false, true);

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

    Object2D exitButton = Object2D(vertices2d, app->getSize(), "../resources/textures/default.png", "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    exitButton.setScale({0.1, 0.1});
    exitButton.setPosition({0.95, 0.95});

    int frames = 0;
    double start = glfwGetTime();

    app->addObject2D(object2d);
    app->addObject2D(exitButton);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isKeyPressed(KEY_W))
            app->getObject2D(0)->transformPosition({0, 0.001});

        if (app->isKeyPressed(KEY_S))
            app->getObject2D(0)->transformPosition({0, -0.001});

        if (app->isKeyPressed(KEY_A))
            app->getObject2D(0)->transformPosition({-0.001, 0});

        if (app->isKeyPressed(KEY_D))
            app->getObject2D(0)->transformPosition({0.001, 0});

        if (app->isKeyPressed(KEY_Q))
            app->getObject2D(0)->transformRotation(0.01);

        if (app->isKeyPressed(KEY_E))
            app->getObject2D(0)->transformRotation(-0.01);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D(1)->inHitbox(Vector::convertCoordinateSystem(Vector::clamp(app->getMousePosition(), {0, 0}, Vector::convert(app->getSize())), {0, 0}, Vector::convert(app->getSize()), {-2, 2}, {2, -2})))
            glfwSetWindowShouldClose(app->getWindow(), true);

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