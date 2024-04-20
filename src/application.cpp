#include "application.h"

Application::Application()
{
    logManager = new LogManager("logs/log", true, "txt", true, true, true);

    if (!glfwInit())
    {
        Log::log("GLFW initialization failed");
    }

    windowSize = FHD;
    windowTitle = "Application";
    startTime = glfwGetTime();
    frames = 0;
    isRunningInternal = true;

    currentContextID = createContext();

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

    inputManager = new InputManager();

    Log::log("Application initialized");
}

Application::Application(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync)
{
    logManager = new LogManager("logs/log", true, "txt", true, true, true);

    if (!glfwInit())
    {
        Log::log("GLFW initialization failed");
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

    Log::log("Application initialized");
}

Application::~Application()
{
    clearContexts();
    delete contexts[currentContextID];

    double sum = glfwGetTime() - startTime;
    Log::log("Application destroyed");
    logManager->logQueue(frames);
    Log::log("Frames: " + std::to_string(frames));
    Log::log("Average FPS: " + std::to_string(frames / sum));
    logManager->logQueue();

    delete logManager;
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::update()
{
    previousTime = currentTime;
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    contexts[currentContextID]->draw();

    glfwSwapBuffers(window);

    inputManager->update(window);
    logManager->logQueue(frames);

    frames++;
    currentTime = glfwGetTime();
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
    Context *context = new Context();
    context->setID(contexts.size());
    contexts[context->getID()] = context;
    return context->getID();
}

void Application::setContextLabel(uInt id, const std::string &label)
{
    if (contexts.find(id) != contexts.end())
    {
        contexts[id]->setLabel(label);
        contextLabels[label] = id;
        return;
    }
    if (contextLabels.find(label) != contextLabels.end())
    {
        Log::log("Context label already exists");
        return;
    }
    if (contexts[currentContextID]->getLabel() != "")
    {
        contextLabels.erase(contexts[currentContextID]->getLabel());
        contexts[currentContextID]->setLabel(label);
        contextLabels[label] = currentContextID;
        return;
    }
    Log::log("Context ID not found");
}

void Application::setCurrentContext(uInt id)
{
    if (contexts.find(id) != contexts.end())
    {
        currentContextID = id;
        return;
    }
    Log::log("Context ID not found");
}

void Application::setCurrentContext(const std::string &label) // temporary solution
{
    for (auto &context : contexts)
    {
        if (context.second->getLabel() == label)
        {
            currentContextID = context.first;
            return;
        }
    }
    Log::log("Context label not found");
}

void Application::loadContext(const std::string &path) // WiP
{
    Log::log("Loading context from '" + path + "'");

    NDS nds(path);
    nds.loadNDL();

    for (std::string group : nds.getGroupNames())
    {
        std::string type = nds.getString("type", group);
        if (type == "OBJECT2D")
        {
            dVector2 position = dVector2(nds.getDoubleList("positionWindow", group)[0], nds.getDoubleList("positionWindow", group)[1]);
            position.convertCoordinateSystem({0, 0}, {1, 1}, {-1, -1}, {1, 1});
            dVector2 scale = dVector2(nds.getDoubleList("scaleWorld", group)[0], nds.getDoubleList("scaleWorld", group)[1]);
            position -= scale / dVector2(2, 1); // temporary solution
            double rotation = nds.getDouble("rotation", group);
            std::string texturePath = nds.getString("texturePath", group);
            std::string verticesPath = nds.getString("verticesPath", group);
            std::string vertexPath = nds.getString("vertexPath", group);
            std::string fragmentPath = nds.getString("fragmentPath", group);

            uInt id = createObject2D(position, scale, rotation, windowSize, verticesPath, texturePath, vertexPath, fragmentPath);
            contexts[currentContextID]->setObjectLabel(id, group);
        }
        else if (type == "TEXT")
        {
            std::string text = nds.getString("text", group);
            dVector2 position = dVector2(nds.getDoubleList("positionWindow", group)[0], nds.getDoubleList("positionWindow", group)[1]);
            // position.convertCoordinateSystem({0, 0}, {1, 1}, {-1, -1}, {1, 1}); why changes position to 0 0?
            dVector2 scale = dVector2(nds.getDoubleList("scaleWorld", group)[0], nds.getDoubleList("scaleWorld", group)[1]);
            double rotation = nds.getDouble("rotation", group);
            std::string fontPath = nds.getString("fontPath", group);
            std::string vertexPath = nds.getString("vertexPath", group);
            std::string fragmentPath = nds.getString("fragmentPath", group);

            uInt id = createText(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath);
            contexts[currentContextID]->setObjectLabel(id, group);
        }
        else
        {
            Log::log("Unknown type");
        }
    }

    Log::log("Context loaded from '" + path + "'");
}

void Application::destroyContext(uInt id)
{
    if (id != currentContextID)
    {
        delete contexts[id];
        contexts.erase(id);
        return;
    }
    Log::log("Cannot destroy current context");
}

void Application::destroyContext(const std::string &label)
{
    for (auto &context : contexts)
    {
        if (context.second->getLabel() == label)
        {
            if (context.first != currentContextID)
            {
                delete context.second;
                contexts.erase(context.first);
                return;
            }
            Log::log("Cannot destroy current context");
        }
    }
    Log::log("Context label not found");
}

void Application::clearContexts()
{
    Log::log("Clearing contexts");

    for (auto &context : contexts)
    {
        if (context.first != currentContextID)
            delete context.second;
    }

    contexts.clear();
}

InputManager *Application::getInput()
{
    return inputManager;
}

LogManager *Application::getLog()
{
    return logManager;
}

ObjectPtr Application::getObject(uInt id)
{
    return contexts[currentContextID]->getObject(id);
}

ObjectPtr Application::getObject(const std::string &label)
{
    return contexts[currentContextID]->getObject(label);
}

bool Application::inObjectHitbox(uInt id, const dVector2 &position)
{
    return contexts[currentContextID]->inObjectHitbox(id, position);
}

bool Application::inObjectHitbox(const std::string &label, const dVector2 &position)
{
    return contexts[currentContextID]->inObjectHitbox(label, position);
}

uInt Application::createObject2D(dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
{
    std::vector<double> vertices = Utility::loadBinaryDoubles(verticesPath);

    double aspectRatio = double(windowSize.x) / double(windowSize.y);                                         // temporary solution
    position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1}); // temporary solution

    return contexts[currentContextID]->createObject2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath);
}

uInt Application::createText(const std::string &text, dVector2 position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
{
    double aspectRatio = double(windowSize.x) / double(windowSize.y);                                         // temporary solution
    position = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1}); // temporary solution

    return contexts[currentContextID]->createText(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath);
}

void Application::destroyObject(uInt id)
{
    contexts[currentContextID]->destroyObject(id);
}

void Application::clearObjects()
{
    contexts[currentContextID]->clearObjects();
}

void Application::clearObjects2D()
{
    contexts[currentContextID]->clearObjects2D();
}

void Application::clearTexts()
{
    contexts[currentContextID]->clearTexts();
}

std::string Application::getWindowTitle()
{
    return windowTitle;
}

iVector2 Application::getWindowSize()
{
    return windowSize;
}

uInt Application::getCurrentContextID()
{
    return currentContextID;
}

double Application::getTime()
{
    return currentTime;
}

double Application::getDeltaTime()
{
    return currentTime - previousTime;
}

double Application::getFPS()
{
    return 1 / getDeltaTime();
}