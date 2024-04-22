#ifndef APPLICATION_H
#define APPLICATION_H

#include "include.h"
#include "context.h"
#include "input.h"
#include "object.h"
#include "vector.h"
#include "log.h"

class Application
{
private:
    GLFWwindow *window;
    std::string windowTitle;
    iVector2 windowSize;

    std::unordered_map<std::string, uInt> labels;

    std::unordered_map<uInt, Context *> contexts;
    uInt currentContextID;

    InputManager *inputManager;

    double startTime;
    double previousTime;
    double applicationTime;
    int frames;

    bool isRunningInternal;

public:
    Application(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync);
    ~Application();

    void update();
    bool isRunning();

    void setIsRunning(bool isRunning);

    uInt createContext();
    void setCurrentContext(uInt id);
    uInt loadContext(const std::string &path);
    void destroyContext(uInt id);
    void clearContexts();

    Context *getCurrentContext();
    Context *getContext(uInt id);
    InputManager *getInputManager();

    void addLabel(const std::string &label, uInt id);
    void removeLabel(uInt id);
    void clearLabels();
    uInt getID(const std::string &label);

    std::string getWindowTitle();
    iVector2 getWindowSize();

    double getApplicationTime();
    double getDeltaTime();
    double getFPS();
};

#endif // APPLICATION_H