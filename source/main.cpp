/*
TODO:
    ADD FONT
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
    Application *app = new Application({WQHD}, "Application", true, false, false);

    std::vector<double> vertices2d = {
        0.5, 0.5, 1.0, 1.0,   //
        0.5, -0.5, 1.0, 0.0,  //
        -0.5, 0.5, 0.0, 1.0,  //
        0.5, -0.5, 1.0, 0.0,  //
        -0.5, -0.5, 0.0, 0.0, //
        -0.5, 0.5, 0.0, 1.0   //
    };                        // has to be normalized to (-1, 1)

    Object2D exitButton = Object2D(vertices2d, app->getSize(), "../resources/textures/test.png", "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    exitButton.setScaleWorld({0.1, 0.1});
    exitButton.setPositionWindow({1, 1}, app->getSize());
    exitButton.transformPosition(Vector::multiply(exitButton.getScale(), {-0.5, -0.5}));

    int frames = 0;
    double start = glfwGetTime();

    app->addObject2D(exitButton);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D(0)->inHitbox(app->getMousePositionWorld()))
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