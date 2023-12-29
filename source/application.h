#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vector.h"
#include "context.h"
#include "input.h"

class Application
{
private:
    GLFWwindow *window;
    std::string title;
    iVector2 size;
    std::vector<Context> contexts;
    Input inputManager;
    int currentContext;

public:
    Application(iVector2 size, std::string title, bool fullscreen, bool resizable, bool decorated);

    void update();

    bool isKeyPressed(int key);
    bool wasKeyReleased(int key);

    bool isMousePressed(int button);
    bool wasMouseReleased(int button);

    dVector2 getMousePosition();
    dVector2 getMousePositionWindow();
    dVector2 getMousePositionWorld();

    void addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);
    void destroyObject2D(int index);

    void draw();

    GLFWwindow *getWindow();
    void destroyWindow();

    void createContext();
    void setCurrentContext(int index);
    Context *getContext(int index);
    void destroyContext(int index);

    Input *getInputManager();

    iVector2 getSize();
};