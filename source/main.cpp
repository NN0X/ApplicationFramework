/*
TODO:
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

    int frames = 0;
    double start = glfwGetTime();

    app->addObject2D(object2d);

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

        if (app->isMousePressed(MOUSE_LEFT))
            app->getObject2D(0)->inHitbox(Vector::convertCoordinateSystem(Vector::clamp(app->getMousePosition(), {0, 0}, {800, 800}), {0, 0}, {800, 800}, {-2, 2}, {2, -2}));

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