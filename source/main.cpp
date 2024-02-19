/*
TODO:
    ADD SOUND
    DEVELOP FONT
    CLEANUP INSTANCING
    ADD PARENT TRANSFORMS IN DRAW() FUNCTION
    DITCH VISUAL STUDIO AND USE CMAKE

BUGS:
    FONT TEXTURE IS SOMETIMES WRONG WHEN TEXT IS TOO LONG
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

#define ASCII " !#$%&'()*+,-./\n0123456789\n:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ\n[]^_`abcdefghijklmnopqrstuvwxyz{|}~"

int main()
{
    Application *app = new Application({WQHD}, "Application", true, false, false);

    int frames = 0;
    double start = glfwGetTime();

    app->createContext();
    app->loadContextNDL("../resources/database/default.ndl");

    while (!glfwWindowShouldClose(app->getWindow()))
    {
        if (app->isKeyPressed(KEY_ESCAPE))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isMousePressed(MOUSE_LEFT) && app->getObject2D("exit")->inHitbox(app->getMousePositionWorld()))
            glfwSetWindowShouldClose(app->getWindow(), true);

        if (app->isKeyPressed(KEY_W))
            app->getFont("font")->transformPosition({0, 0.001});

        if (app->isKeyPressed(KEY_S))
            app->getFont("font")->transformPosition({0, -0.001});

        if (app->isKeyPressed(KEY_A))
            app->getFont("font")->transformPosition({-0.001, 0});

        if (app->isKeyPressed(KEY_D))
            app->getFont("font")->transformPosition({0.001, 0});

        if (app->isKeyPressed(KEY_R))
        {
            app->clearInstances();
            app->loadContextNDL("../resources/database/default.ndl");
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