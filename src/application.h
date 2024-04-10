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
    int frames;
    bool isRunningInternal;

public:
    Application();
    Application(iVector2 windowSize, std::string windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync);

    ~Application();

    void update();
    bool isRunning();

    void setIsRunning(bool isRunning);

    uInt createContext();
    void setCurrentContext(uInt index);
    void setCurrentContext(std::string label); // temporary solution
    void loadContext(std::string path);        // WiP
    void destroyContext(uInt index);
    void destroyContext(std::string label);
    void clearContexts();

    InputManager *getInput();

    bool inObjectHitbox(uInt index, dVector2 position);
    bool inObjectHitbox(std::string label, dVector2 position);

    uInt createObject2D(dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string verticesPath, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    Object2D *getObject2D(uInt index);
    Object2D *getObject2D(std::string label);
    void destroyObject2D(uInt index);
    void destroyObject2D(std::string label);
    void clearObjects2D();

    uInt createText(std::string text, dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath);
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