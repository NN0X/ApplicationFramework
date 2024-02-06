/*
TODO:
    FIX BUG WHERE FONT TEXTURE IS SOMETIMES WRONG WHEN TEXT IS TOO LONG
    DEVELOP FONT
    ADD SOUND
    FIX INSTANCING
    ADD PARENT TRANSFORMS IN DRAW() FUNCTION
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

#include <NDS/nds.h>

#include "utility.h"
#include "application.h"

#define WQHD 2560, 1440
#define FHD 1920, 1080
#define HD 1280, 720
#define SD 640, 480

#define VERTEX_PATH "../resources/shaders/default2dVertex.glsl"
#define FRAGMENT_PATH "../resources/shaders/default2dFragment.glsl"

#define ASCII " !#$%&'()*+,-./\n0123456789\n:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\n[]^_`abcdefghijklmnopqrstuvwxyz{|}~"

int main()
{
    Application *app = new Application({WQHD}, "Application", true, false, false);

    std::vector<double> vertices2d = Utility::loadBinaryDoubles("../resources/meshes/cube.msh"); // has to be normalized to (-1, 1)

    Object2D exitButton = Object2D(vertices2d, app->getSize(), "../resources/textures/test.png", VERTEX_PATH, FRAGMENT_PATH);
    exitButton.setScaleWorld({0.05, 0.05});
    exitButton.setPositionWindow({1, 1}, app->getSize());
    exitButton.transformPosition(Vector::multiply(exitButton.getScale(), {-1, -1}));

    Font font = Font(ASCII, "../resources/fonts/arial/arial", app->getSize(), VERTEX_PATH, FRAGMENT_PATH);

    font.setScaleWorld({0.05, 0.05});
    font.setPositionWindow({0, 1}, app->getSize());
    font.transformPosition(Vector::multiply(font.getScale(), {-1, -1}));

    int frames = 0;
    double start = glfwGetTime();

    int buttonIndex = app->addObject2D(exitButton);
    int fontIndex = app->addFont(font);

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D(buttonIndex)->inHitbox(app->getMousePositionWorld()))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isKeyPressed(KEY_W))
            app->getFont(fontIndex)->transformPosition({0, 0.001});

        if (app->isKeyPressed(KEY_S))
            app->getFont(fontIndex)->transformPosition({0, -0.001});

        if (app->isKeyPressed(KEY_A))
            app->getFont(fontIndex)->transformPosition({-0.001, 0});

        if (app->isKeyPressed(KEY_D))
            app->getFont(fontIndex)->transformPosition({0.001, 0});

        if (app->isKeyPressed(KEY_R))
        {
            app->clearInstances();
        }

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