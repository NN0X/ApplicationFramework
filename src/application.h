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
    std::vector<Context *> contexts;
    InputManager *inputManager;
    LogManager *logManager;
    uInt currentContextIndex;
    double startTime;
    double previousTime;
    double currentTime;
    int frames;
    bool isRunningInternal;

public:
    Application();
    Application(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync);

    ~Application();

    void update();
    bool isRunning();

    void setIsRunning(bool isRunning);

    uInt createContext();
    void setCurrentContext(uInt index);
    void setCurrentContext(const std::string &label); // temporary solution
    void loadContext(const std::string &path);        // WiP
    void destroyContext(uInt index);
    void destroyContext(const std::string &label);
    void clearContexts();

    InputManager *getInput();
    LogManager *getLog();

    ObjectID getObjectID(uInt index);
    ObjectID getObjectID(const std::string &label);

    bool inObject2DHitbox(uInt index, const dVector2 &position);
    bool inTextHitbox(uInt index, const dVector2 &position);

    uInt createObject2D(dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    Object2D *getObject2D(uInt index);
    void destroyObject2D(uInt index);
    void clearObjects2D();

    uInt createText(const std::string &text, dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    Text *getText(uInt index);
    void destroyText(uInt index);
    void clearTexts();

    std::string getWindowTitle();
    iVector2 getWindowSize();
    uInt getCurrentContextIndex();

    double getTime();
    double getDeltaTime();
};

#endif // APPLICATION_H