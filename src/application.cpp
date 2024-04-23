#include "application.h"

Application::Application(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync)
{
    if (!Logger::checkInit())
        Logger::init("logs", true, "txt", false, true, true);

    Logger::log("Initializing application");

    if (!glfwInit())
    {
        Logger::error("GLFW initialization failed");
        return;
    }

    GLFWmonitor *monitor = glfwGetPrimaryMonitor();

    this->windowSize = windowSize;
    this->windowTitle = windowTitle;
    currentContextID = createContext();
    startTime = glfwGetTime();
    frames = 0;
    isRunningInternal = true;

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
    glfwSwapInterval(vsync);
    gladLoadGL();

    glViewport(0, 0, windowSize.x, windowSize.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    inputManager = new InputManager();

    Logger::log("Application initialized");
}

Application::~Application()
{
    clearContexts();
    clearLabels();
    delete contexts[currentContextID];
    delete inputManager;

    Logger::log("Total frames: '" + std::to_string(frames) + "'");
    Logger::log("Total time: '" + std::to_string(applicationTime - startTime) + "'");
    Logger::log("Average FPS: '" + std::to_string(frames / (applicationTime - startTime)) + "'");

    Logger::log("Application destroyed");
    Logger::quit();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::update()
{
    previousTime = applicationTime;
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    contexts[currentContextID]->draw();

    glfwSwapBuffers(window);

    inputManager->update(window);

    frames++;
    applicationTime = glfwGetTime();
    Logger::update(frames);
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
    uInt id = Utils::genUniqueID();
    contexts[id] = new Context(id);
    return id;
}

void Application::setCurrentContext(uInt id)
{
    if (contexts.find(id) == contexts.end())
    {
        Logger::error("Context '" + std::to_string(id) + "' not found");
        return;
    }
    currentContextID = id;
    Logger::log("Current context set to '" + std::to_string(id) + "'");
}

uInt Application::loadContext(const std::string &path) // WiP
{
    Logger::log("Loading context from '" + path + "'");

    NDS nds(path);
    nds.loadNDL();

    uInt id = createContext();

    for (std::string group : nds.getGroupNames())
    {
        std::string type = nds.getString("type", group);
        if (type == "OBJECT2D")
        {
            dVector2 position = dVector2(nds.getDoubleList("positionWindow", group)[0], nds.getDoubleList("positionWindow", group)[1]);
            dVector2 scale = dVector2(nds.getDoubleList("scaleWorld", group)[0], nds.getDoubleList("scaleWorld", group)[1]);
            position -= scale / dVector2(2, 1); // temporary solution
            double aspectRatio = double(windowSize.x) / double(windowSize.y);
            position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
            double rotation = nds.getDouble("rotation", group);
            std::string texturePath = nds.getString("texturePath", group);
            std::string verticesPath = nds.getString("verticesPath", group);
            std::string vertexPath = nds.getString("vertexPath", group);
            std::string fragmentPath = nds.getString("fragmentPath", group);

            uInt objectID = contexts[id]->createObject2D(position, scale, rotation, Utils::loadBinaryDoubles(verticesPath), windowSize, texturePath, vertexPath, fragmentPath);
            addLabel(group, objectID);

            Logger::log("Object2D '" + group + "' loaded with ID '" + std::to_string(objectID) + "'");
        }
        else if (type == "TEXT")
        {
            std::string text = nds.getString("text", group);
            dVector2 position = dVector2(nds.getDoubleList("positionWindow", group)[0], nds.getDoubleList("positionWindow", group)[1]);
            dVector2 scale = dVector2(nds.getDoubleList("scaleWorld", group)[0], nds.getDoubleList("scaleWorld", group)[1]);
            double aspectRatio = double(windowSize.x) / double(windowSize.y);
            position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
            double rotation = nds.getDouble("rotation", group);
            std::string fontPath = nds.getString("fontPath", group);
            std::string vertexPath = nds.getString("vertexPath", group);
            std::string fragmentPath = nds.getString("fragmentPath", group);

            uInt objectID = contexts[id]->createText(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath);
            addLabel(group, objectID);

            Logger::log("Text object '" + group + "' loaded with ID '" + std::to_string(objectID) + "'");
        }
        else
        {
            Logger::error("Invalid object type '" + type + "'");
        }
    }

    Logger::log("Context '" + std::to_string(id) + "' loaded from '" + path + "'");

    return id;
}

void Application::destroyContext(uInt id)
{
    if (id == currentContextID)
    {
        Logger::error("Cannot destroy current context");
        return;
    }
    delete contexts[id];
    contexts.erase(id);
    removeLabel(id);
}

void Application::clearContexts()
{
    Logger::log("Clearing contexts");

    for (auto &context : contexts)
    {
        if (context.first == currentContextID)
        {
            continue;
        }
        delete context.second;
        removeLabel(context.first);
    }
    contexts.clear();

    Logger::log("Contexts cleared");
}

Context *Application::getCurrentContext()
{
    return contexts[currentContextID];
}

Context *Application::getContext(uInt id)
{
    if (contexts.find(id) == contexts.end())
    {
        Logger::error("Context '" + std::to_string(id) + "' not found");
        return NULL;
    }
    return contexts[id];
}

InputManager *Application::getInputManager()
{
    return inputManager;
}

void Application::addLabel(const std::string &label, uInt id)
{
    if (labels.find(label) != labels.end())
    {
        Logger::error("Label '" + label + "' already points to '" + std::to_string(labels[label]) + "'");
        return;
    }
    labels[label] = id;

    Logger::log("Label '" + label + "' pointing to '" + std::to_string(id) + "' added");
}

void Application::removeLabel(uInt id)
{
    for (auto &label : labels)
    {
        if (label.second == id)
        {
            labels.erase(label.first);

            Logger::log("Label '" + label.first + "' pointing to '" + std::to_string(id) + "' removed");

            return;
        }
    }

    Logger::error("Label pointing to '" + std::to_string(id) + "' not found");
}

void Application::clearLabels()
{
    Logger::log("Clearing labels");
    labels.clear();
    Logger::log("Labels cleared");
}

uInt Application::getID(const std::string &label)
{
    if (labels.find(label) == labels.end())
    {
        Logger::error("Label '" + label + "' not found");
        return -1;
    }
    return labels[label];
}

std::string Application::getWindowTitle()
{
    return windowTitle;
}

iVector2 Application::getWindowSize()
{
    return windowSize;
}

double Application::getApplicationTime()
{
    return applicationTime;
}

double Application::getDeltaTime()
{
    return applicationTime - previousTime;
}

double Application::getFPS()
{
    double deltaTime = getDeltaTime();
    if (deltaTime == 0)
    {
        Logger::error("Delta time is 0");
        return 0;
    }
    return 1 / getDeltaTime();
}