#include "application.h"

Application::Application()
{
    if (!glfwInit())
    {
        // log error
    }

    windowSize = FHD;
    windowTitle = "Application";
    isRunningInternal = true;

    currentContextIndex = createContext();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.data(), NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();

    glViewport(0, 0, windowSize.x, windowSize.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    inputManager = InputManager();

    // log
}

Application::Application(iVector2 windowSize, std::string windowTitle, bool fullscreen, bool resizable, bool decorated, uInt fpsMax)
{
    glfwInit();

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    this->windowSize = windowSize;
    this->windowTitle = windowTitle;
    currentContextIndex = 0;
    isRunningInternal = true;

    createContext();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (fullscreen)
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    else
        monitor = NULL;
    if (resizable)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    if (decorated)
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    else
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(windowSize.x, windowSize.y, windowTitle.data(), monitor, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(fpsMax);
    gladLoadGL();

    glViewport(0, 0, windowSize.x, windowSize.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    inputManager = InputManager();

    // log
}

Application::~Application()
{
    // log
    // save log file
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::update()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    contexts[currentContextIndex].draw();

    glfwSwapBuffers(window);

    inputManager.update(window);
}

bool Application::isRunning()
{
    return isRunningInternal;
}

void Application::setIsRunning(bool isRunning)
{
    isRunningInternal = isRunning;
}

uInt Application::createContext()
{
    contexts.push_back(Context());

    return contexts.size() - 1;
}

void Application::setCurrentContext(uInt index)
{
    if (index < contexts.size())
        currentContextIndex = index;
    else
        ; // log error
}

void Application::setCurrentContext(std::string label) // temporary solution
{
    for (int i = 0; i < contexts.size(); i++)
    {
        if (contexts[i].getLabel() == label)
        {
            currentContextIndex = i;
            return;
        }
    }
    // log error
}

void Application::loadContext(std::string path) // WiP
{
    NDS nds(path);
    nds.loadNDL();

    for (std::string group : nds.getGroupNames())
    {
        std::string type = nds.getString("type", group);
        if (type == "Object2D")
        {
            // WiP
        }
        else if (type == "Text")
        {
            // WiP
        }
        else
        {
            // log error
        }
    }
}

void Application::destroyContext(uInt index)
{
    if (index != currentContextIndex)
        contexts.erase(contexts.begin() + index);
    else
        ; // log error
}

void Application::destroyContext(std::string label) // temporary solution
{
    for (int i = 0; i < contexts.size(); i++)
    {
        if (contexts[i].getLabel() == label)
        {
            if (i != currentContextIndex)
                contexts.erase(contexts.begin() + i);
            else
                ; // log error
            return;
        }
    }
    // log error
}

void Application::clearContexts()
{
    for (int i = 0; i < contexts.size(); i++)
    {
        if (i != currentContextIndex)
            contexts.erase(contexts.begin() + i);
    }
}

InputManager *Application::getInput()
{
    return &inputManager;
}

uInt Application::createObject2D(dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string verticesPath, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    std::vector<double> vertices = Utility::loadBinaryDoubles(verticesPath);

    double aspectRatio = double(windowSize.x) / double(windowSize.y);                                         // temporary solution
    position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1}); // temporary solution

    return contexts[currentContextIndex].createObject2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath);
}

Object2D *Application::getObject2D(uInt index)
{
    return contexts[currentContextIndex].getObject2D(index);
}

Object2D *Application::getObject2D(std::string label)
{
    return contexts[currentContextIndex].getObject2D(label);
}

void Application::destroyObject2D(uInt index)
{
    contexts[currentContextIndex].destroyObject2D(index);
}

void Application::destroyObject2D(std::string label)
{
    contexts[currentContextIndex].destroyObject2D(label);
}

void Application::clearObjects2D()
{
    contexts[currentContextIndex].clearObjects2D();
}

uInt Application::createText(std::string text, dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath)
{
    double aspectRatio = double(windowSize.x) / double(windowSize.y);                                         // temporary solution
    position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1}); // temporary solution

    return contexts[currentContextIndex].createText(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath);
}

Text *Application::getText(uInt index)
{
    return contexts[currentContextIndex].getText(index);
}

Text *Application::getText(std::string label)
{
    return contexts[currentContextIndex].getText(label);
}

void Application::destroyText(uInt index)
{
    contexts[currentContextIndex].destroyText(index);
}

void Application::destroyText(std::string label)
{
    contexts[currentContextIndex].destroyText(label);
}

void Application::clearTexts()
{
    contexts[currentContextIndex].clearTexts();
}

std::string Application::getWindowTitle()
{
    return windowTitle;
}

iVector2 Application::getWindowSize()
{
    return windowSize;
}

uInt Application::getCurrentContextIndex()
{
    return currentContextIndex;
}

double Application::getTime()
{
    return glfwGetTime();
}