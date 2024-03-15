#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <NDS/nds.h>

#include "vector.h"
#include "context.h"
#include "input.h"

const iVector2 WQHD = {2560, 1440};
const iVector2 FHD = {1920, 1080};
const iVector2 HD = {1280, 720};
const iVector2 SD = {640, 480};

class Application
{
private:
    GLFWwindow *window;
    std::string title;
    iVector2 size;
    std::vector<Context> contexts;
    Input input;
    int currentContext;

public:
    Application(iVector2 size, std::string title, bool fullscreen, bool resizable, bool decorated);

    void update();

    bool isKeyPressed(int key);
    bool wasKeyReleased(int key);

    bool isMousePressed(int button);
    bool wasMouseReleased(int button);

    dVector2 getMousePositionScreen();
    dVector2 getMousePositionWindow();
    dVector2 getMousePositionWorld();

    int addObject2D(const Object2D &object);
    Object2D *getObject2D(int index);
    Object2D *getObject2D(std::string label);

    int addFont(const Font &font);
    Font *getFont(int index);
    Font *getFont(std::string label);

    void destroyInstance(int index);
    void clearInstances();

    void draw();

    GLFWwindow *getWindow();
    void destroyWindow();

    void createContext();
    void setCurrentContext(int index);
    void addContext(const Context &context);
    void loadContextNDL(std::string path);
    Context *getContext(int index);
    void destroyContext(int index);
    std::vector<std::pair<int, int>> getInstances();

    Input *getInput();
    iVector2 getSize();
};