#include <iostream>

#include "AF.h"

int main()
{
    Application *app = AF::init();
    // Application *app = new Application();

    int frames = 0;
    double start = AF::getTime(app);

    // app->loadContext("../resources/database/default.ndl");

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