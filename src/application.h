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
    std::unordered_map<std::string, uInt> contextLabels;
    std::unordered_map<uInt, Context *> contexts;
    InputManager *inputManager;
    LogManager *logManager;
    uInt currentContextID;
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
    void setContextLabel(uInt id, const std::string &label);
    void setCurrentContext(uInt id);
    void setCurrentContext(const std::string &label);
    void loadContext(const std::string &path);
    void destroyContext(uInt id);
    void destroyContext(const std::string &label);
    void clearContexts();

    InputManager *getInput();
    LogManager *getLog();

    ObjectPtr getObject(uInt id);
    ObjectPtr getObject(const std::string &label);

    bool inObjectHitbox(uInt id, const dVector2 &position);
    bool inObjectHitbox(const std::string &label, const dVector2 &position);

    uInt createObject2D(dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    uInt createText(const std::string &text, dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    void destroyObject(uInt id);
    void clearObjects();
    void clearObjects2D();
    void clearTexts();

    std::string getWindowTitle();
    iVector2 getWindowSize();
    uInt getCurrentContextID();

    double getTime();
    double getDeltaTime();
    double getFPS();
};

#endif // APPLICATION_H