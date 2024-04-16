#include <iostream>

#include <AF.h>

int main()
{
    Application *app = AF::init(AF_FHD, "Test", false, true, true, false);
    AF::Logs::setFlags(app, false, true, true);

    AF::loadContext(app, "resources/database/default.ndl");

    // dVector2(0.025, 0.025) is the offset so the position is from the right top corner (scale / dVector2(2, 1))
    // this should be done actually in window coordinate system so this is an approximation
    // uInt indexExit = AF::Object::create(app, AF::OBJECT2D, dVector2(1, 1) - dVector2(0.025, 0.05), dVector2(0.05, 0.05), 0.0, "resources/meshes/cube.msh", "resources/textures/default.png", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");
    // uInt indexText = AF::Object::create(app, "test", dVector2(0.5, 0.5), dVector2(0.05, 0.05), 0.0, "resources/fonts/arial/arial", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");

    while (AF::isRunning(app))
    {
        if (AF::Input::isKeyPressed(app, AF::Input::KEY_ESCAPE))
        {
            AF::setIsRunning(app, false);
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_W))
        {
            AF::Object::transformPosition(app, "text", dVector2(0, AF::getDeltaTime(app)));
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_S))
        {
            AF::Object::transformPosition(app, "text", dVector2(0, -AF::getDeltaTime(app)));
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_A))
        {
            AF::Object::transformPosition(app, "text", dVector2(-AF::getDeltaTime(app), 0));
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_D))
        {
            AF::Object::transformPosition(app, "text", dVector2(AF::getDeltaTime(app), 0));
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_E))
        {
            AF::Object::transformRotation(app, "text", AF::getDeltaTime(app) * 100);
        }

        if (AF::Input::isKeyPressed(app, AF::Input::KEY_Q))
        {
            AF::Object::transformRotation(app, "text", -AF::getDeltaTime(app) * 100);
        }

        if (AF::Object::isClicked(app, "exit"))
            AF::setIsRunning(app, false);

        AF::update(app);
    }

    AF::quit(app);
}