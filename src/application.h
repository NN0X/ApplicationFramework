#ifndef APPLICATION_H
#define APPLICATION_H

#include "include.h"
#include "context.h"
#include "input.h"
#include "object.h"
#include "vector.h"

class Application
{
private:
    GLFWwindow *window;
    std::string windowTitle;
    iVector2 windowSize;
    std::vector<Context> contexts;
    InputManager inputManager;
    uInt currentContextIndex;
    bool isRunningInternal;

public:
    Application();
    Application(iVector2 windowSize, std::string windowTitle, bool fullscreen, bool resizable, bool decorated, uInt fpsMax);

    ~Application();

    void update();
    bool isRunning();

    void setIsRunning(bool isRunning);

    uInt createContext();
    void setCurrentContext(uInt index);
    void setCurrentContext(std::string label); // WiP
    void loadContext(std::string path);        // WiP
    void destroyContext(uInt index);
    void destroyContext(std::string label);
    void clearContexts();

    InputManager *getInput();

    uInt createObject2D(); // WiP
    Object2D *getObject2D(uInt index);
    Object2D *getObject2D(std::string label);
    void destroyObject2D(uInt index);
    void destroyObject2D(std::string label);
    void clearObjects2D();

    uInt createText(); // WiP
    Text *getText(uInt index);
    Text *getText(std::string label);
    void destroyText(uInt index);
    void destroyText(std::string label);
    void clearTexts();

    std::string getWindowTitle();
    iVector2 getWindowSize();
    uInt getCurrentContextIndex();

    double getTime();
};

#endif // APPLICATION_H