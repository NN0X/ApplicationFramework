/*
TODO:
    ADD GUI INPUT
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

        if (app->getObject2D(0)->getPosition().x > 2 + app->getObject2D(0)->getScale().x)
            app->getObject2D(0)->setPosition({-2 - app->getObject2D(0)->getScale().x, app->getObject2D(0)->getPosition().y});

        if (app->getObject2D(0)->getPosition().x < -2 - app->getObject2D(0)->getScale().x)
            app->getObject2D(0)->setPosition({2 + app->getObject2D(0)->getScale().x, app->getObject2D(0)->getPosition().y});

        if (app->getObject2D(0)->getPosition().y > 2 + app->getObject2D(0)->getScale().y)
            app->getObject2D(0)->setPosition({app->getObject2D(0)->getPosition().x, -2 - app->getObject2D(0)->getScale().y});

        if (app->getObject2D(0)->getPosition().y < -2 - app->getObject2D(0)->getScale().y)
            app->getObject2D(0)->setPosition({app->getObject2D(0)->getPosition().x, 2 + app->getObject2D(0)->getScale().y});

        if (app->isKeyPressed(KEY_I))
            app->getObject2D(0)->getPosition().print();

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