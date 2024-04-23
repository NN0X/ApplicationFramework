#include <iostream>

#include <AF.h>

int main()
{
    AF::Log::init("logs", true, "txt", false, true, true);
    Application *app = AF::init(AF::FHD, "Test", false, true, true, false);

    AF::addLabel(app, AF::loadContext(app, "resources/database/default.ndl"), "default");
    AF::setCurrentContext(app, "default");

    AF::addLabel(app, AF::Object::createObject2D(app, {0.5, 0.5}, {0.5, 0.5}, 0, "resources/meshes/rectangle.msh", "resources/textures/logo.png", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl"), "child");
    AF::Object::addChild(app, "text", "child");

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