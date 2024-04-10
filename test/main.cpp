#include <iostream>

#include <AF.h>

int main()
{
    Application *app = AF::init(AF_FHD, "Test", false, true, true, false);

    // app->loadContext("../resources/database/default.ndl");

    // dVector2(0.025, 0.025) is the offset so the position is from the right top corner (scale / dVector2(2, 1))
    // this should be done actually in window coordinate system so this is an approximation
    uInt index2D = AF::Object::create2D(app, dVector2(1, 1) - dVector2(0.025, 0.05), dVector2(0.05, 0.05), 0.0, "resources/meshes/cube.msh", "resources/textures/default.png", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");
    uInt indexText = AF::Object::createText(app, "test", dVector2(0.5, 0.5), dVector2(0.05, 0.05), 0.0, "resources/fonts/arial/arial", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");

    while (AF::isRunning(app))
    {
        if (AF::Input::isKeyPressed(app, AF::Input::KEY_ESCAPE))
        {
            AF::Logs::log("Escape key pressed"); // should be in AF.cpp in function isKeyPressed
            AF::setIsRunning(app, false);
        }

        if (AF::Object::isClicked(app, index2D))
            AF::setIsRunning(app, false);

        AF::update(app);
    }

    AF::quit(app);

    std::cin.get();
}