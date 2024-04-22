#include "input.h"

InputManager::InputManager()
{
    for (int i = 0; i < KEYS_NUMBER; i++)
    {
        keysPressed[i] = false;
        keysReleased[i] = false;
    }

    for (int i = 0; i < MOUSE_BUTTONS_NUMBER; i++)
    {
        mouseButtonsPressed[i] = false;
        mouseButtonsReleased[i] = false;
    }

    Logger::log("Input manager initialized");
}

InputManager::~InputManager()
{
    Logger::log("Input manager destroyed");
}

void InputManager::update(GLFWwindow *window)
{
    glfwPollEvents();

    int i = 0;
    for (int keyCode : keyCodes)
    {
        int state = glfwGetKey(window, keyCode);
        if (state == GLFW_PRESS)
        {
            keysPressed[i] = true;
            keysReleased[i] = false;
        }
        else
        {
            if (keysPressed[i] == true)
                keysReleased[i] = true;
            keysPressed[i] = false;
        }

        i++;
    }

    i = 0;
    for (int mouseCode : mouseCodes)
    {
        int state = glfwGetMouseButton(window, mouseCode);
        if (state == GLFW_PRESS)
        {
            mouseButtonsPressed[i] = true;
            mouseButtonsReleased[i] = false;
        }
        else
        {
            if (mouseButtonsPressed[i] == true)
                mouseButtonsReleased[i] = true;
            mouseButtonsPressed[i] = false;
        }

        i++;
    }

    mousePosition = dVector2();
    glfwGetCursorPos(window, &mousePosition.x, &mousePosition.y);
}

void InputManager::setKeyPressed(uInt key)
{
    if (key < KEYS_NUMBER)
    {
        keysPressed[key] = true;
        keysReleased[key] = false;
        return;
    }

    Logger::error("Key code out of range: '" + std::to_string(key) + "'");
}

void InputManager::setKeyReleased(uInt key)
{
    if (key < KEYS_NUMBER)
    {
        keysPressed[key] = false;
        keysReleased[key] = true;
        return;
    }

    Logger::error("Key code out of range: '" + std::to_string(key) + "'");
}

void InputManager::setMouseButtonPressed(uInt button)
{
    if (button < MOUSE_BUTTONS_NUMBER)
    {
        mouseButtonsPressed[button] = true;
        mouseButtonsReleased[button] = false;
        return;
    }

    Logger::error("Mouse button code out of range: '" + std::to_string(button) + "'");
}

void InputManager::setMouseButtonReleased(uInt button)
{
    if (button < MOUSE_BUTTONS_NUMBER)
    {
        mouseButtonsPressed[button] = false;
        mouseButtonsReleased[button] = true;
        return;
    }

    Logger::error("Mouse button code out of range: '" + std::to_string(button) + "'");
}

void InputManager::setMousePosition(const dVector2 &position)
{
    mousePosition = position;
}

bool InputManager::isKeyPressed(uInt key)
{
    if (key < KEYS_NUMBER)
    {
        return keysPressed[key];
    }

    Logger::error("Key code out of range: '" + std::to_string(key) + "'");

    return false;
}

bool InputManager::wasKeyReleased(uInt key)
{
    if (key < KEYS_NUMBER)
    {
        bool temp = keysReleased[key]; // is this needed?
        keysReleased[key] = false;
        return temp;
    }

    Logger::error("Key code out of range: '" + std::to_string(key) + "'");

    return false;
}

bool InputManager::isMouseButtonPressed(uInt button)
{
    if (button < MOUSE_BUTTONS_NUMBER)
    {
        return mouseButtonsPressed[button];
    }

    Logger::error("Mouse button code out of range: '" + std::to_string(button) + "'");

    return false;
}

bool InputManager::wasMouseButtonReleased(uInt button)
{
    if (button < MOUSE_BUTTONS_NUMBER)
    {
        bool temp = mouseButtonsReleased[button]; // is this needed?
        mouseButtonsReleased[button] = false;
        return temp;
    }

    Logger::error("Mouse button code out of range: '" + std::to_string(button) + "'");

    return false;
}

std::vector<uInt> InputManager::getKeysPressed()
{
    std::vector<uInt> keys;
    for (uInt i = 0; i < KEYS_NUMBER; i++)
    {
        if (keysPressed[i])
            keys.push_back(i);
    }
    return keys;
}

std::vector<uInt> InputManager::getMouseButtonsPressed()
{
    std::vector<uInt> buttons;
    for (uInt i = 0; i < MOUSE_BUTTONS_NUMBER; i++)
    {
        if (mouseButtonsPressed[i])
            buttons.push_back(i);
    }
    return buttons;
}

dVector2 InputManager::getMousePositionScreen()
{
    return mousePosition;
}

dVector2 InputManager::getMousePositionWindow(const iVector2 &windowSize)
{
    return Vector::convertCoordinateSystem(mousePosition, {0, 0}, Vector::convert(windowSize), {0, 1}, {1, 0});
}

dVector2 InputManager::getMousePositionWorld(const iVector2 &windowSize)
{
    dVector2 windowSizeD = Vector::convert(windowSize);
    double aspectRatio = windowSizeD.x / windowSizeD.y;
    return Vector::convertCoordinateSystem(mousePosition, {0, 0}, windowSizeD, {-1, 2 / aspectRatio - 1}, {1, -1});
}