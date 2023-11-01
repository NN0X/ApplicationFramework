#include "application.h"

Application::Application(iVector2 size, std::string title, bool fullscreen, bool resizable, bool decorated)
{
    glfwInit();

    this->size = size;
    this->title = title;
    currentContext = 0;

    contexts.push_back(Context());

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    if (fullscreen)
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    else if (resizable)
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    else if (!decorated)
        glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    window = glfwCreateWindow(size.x, size.y, title.data(), NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();

    glViewport(0, 0, size.x, size.y);
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Application::update()
{
    draw();

    glfwSwapBuffers(window);

    inputManager.update(window);
}

bool Application::isKeyPressed(int key)
{
    return inputManager.isKeyPressed(key);
}

bool Application::wasKeyReleased(int key)
{
    return inputManager.wasKeyReleased(key);
}

bool Application::isMousePressed(int button)
{
    return inputManager.isMousePressed(button);
}

bool Application::wasMouseReleased(int button)
{
    return inputManager.wasMouseReleased(button);
}

dVector2 Application::getMousePosition()
{
    return inputManager.getMousePosition();
}

void Application::addCamera(const Camera &camera)
{
    contexts[currentContext].addCamera(camera);
}

Camera *Application::getCamera(int index)
{
    return contexts[currentContext].getCamera(index);
}

void Application::destroyCamera(int index)
{
    contexts[currentContext].destroyCamera(index);
}

void Application::addObject2D(const Object2D &object)
{
    contexts[currentContext].addObject2D(object);
}

Object2D *Application::getObject2D(int index)
{
    return contexts[currentContext].getObject2D(index);
}

void Application::destroyObject2D(int index)
{
    contexts[currentContext].destroyObject2D(index);
}

void Application::addObject3D(const Object3D &object)
{
    contexts[currentContext].addObject3D(object);
}

Object3D *Application::getObject3D(int index)
{
    return contexts[currentContext].getObject3D(index);
}

void Application::destroyObject3D(int index)
{
    contexts[currentContext].destroyObject3D(index);
}

void Application::draw()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    contexts[currentContext].draw();
}

GLFWwindow *Application::getWindow()
{
    return window;
}

void Application::destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::createContext()
{
    Context context;
    contexts.push_back(context);
}

void Application::setCurrentContext(int index)
{
    currentContext = index;
}

Context *Application::getContext(int index)
{
    return &contexts[index];
}

void Application::destroyContext(int index)
{
    contexts.erase(contexts.begin() + index);
}

Input *Application::getInputManager()
{
    return &inputManager;
}

iVector2 Application::getSize()
{
    return size;
}
