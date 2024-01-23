/*
TODO:
    DEVELOP FONT
    ADD SOUND
    CREATE GUI LANGUAGE OR FINISH NDL AND USE IT INSTEAD
    ADD PARENT TRANSFORMS IN DRAW() FUNCTION
    REWRITE NDL AS LIB or DLL
    DITCH VISUAL STUDIO AND USE CMAKE
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

    std::vector<double> vertices2d = Utility::loadBinaryDoubles("../resources/meshes/cube.msh"); // has to be normalized to (-1, 1)

    Object2D exitButton = Object2D(vertices2d, app->getSize(), "../resources/textures/test.png", "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    exitButton.setScaleWorld({0.05, 0.05});
    exitButton.setPositionWindow({1, 1}, app->getSize());
    exitButton.transformPosition(Vector::multiply(exitButton.getScale(), {-1, -1}));

    Font font = Font("1234567890\nqwertyuiop[]\nasdfghjkl;'\nzxcvbnm,./", "../resources/fonts/arial/arial", app->getSize(), "../resources/shaders/default2dVertex.glsl", "../resources/shaders/default2dFragment.glsl");
    font.setScaleWorld({0.05, 0.05});
    font.setPositionWindow({0, 1}, app->getSize());
    font.transformPosition(Vector::multiply(font.getScale(), {-1, -1}));

    int frames = 0;
    double start = glfwGetTime();

    app->addObject2D(exitButton);
    app->addFont(font);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D(0)->inHitbox(app->getMousePositionWorld()))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isKeyPressed(KEY_W))
            app->getFont(0)->transformPosition({0, 0.001});

        if (app->isKeyPressed(KEY_S))
            app->getFont(0)->transformPosition({0, -0.001});

        if (app->isKeyPressed(KEY_A))
            app->getFont(0)->transformPosition({-0.001, 0});

        if (app->isKeyPressed(KEY_D))
            app->getFont(0)->transformPosition({0.001, 0});

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