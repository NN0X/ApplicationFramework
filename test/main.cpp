#include <iostream>

#include <AF.h>

int main()
{
    Application *app = AF::init(AF_FHD, "Test", false, true, true, 0);
    // Application *app = new Application();

    int frames = 0;
    double start = AF::getTime(app);

    // app->loadContext("../resources/database/default.ndl");

    // dVector2(0.025, 0.025) is the offset so the position is from the center of the object (scale / 2)
    AF::Object::create2D(app, dVector2(1, 1) - dVector2(0.025, 0.025), dVector2(0.05, 0.05), 0.0, "resources/meshes/cube.msh", "resources/textures/default.png", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");
    // for some reason the first letter is not being drawn
    AF::Object::createText(app, "test", dVector2(0.5, 0.5), dVector2(0.05, 0.05), 0.0, "resources/fonts/arial/arial", "resources/shaders/default2dVertex.glsl", "resources/shaders/default2dFragment.glsl");

    while (AF::isRunning(app))
    {
        if (AF::Input::isKeyPressed(app, AF::Input::KEY_ESCAPE))
            AF::setIsRunning(app, false);

        AF::update(app);
        frames++;
    }

    double end = AF::getTime(app);
    double sum = end - start;

    AF::quit(app);

    std::cout << "Total Frames:    " << frames << "\n";
    std::cout << "Total Time:      " << sum << "s\n";
    std::cout << "Average FPS:     " << frames / sum << "\n";
    std::cin.get();
}