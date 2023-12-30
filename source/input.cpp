#include "input.h"

// ----------------------------------------------
// Input

void Input::update(GLFWwindow *window)
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
            mousePressed[i] = true;
            mouseReleased[i] = false;
        }
        else
        {
            if (mousePressed[i] == true)
                mouseReleased[i] = true;
            mousePressed[i] = false;
        }

        i++;
    }

    mousePosition = dVector2();
    glfwGetCursorPos(window, &mousePosition.x, &mousePosition.y);
}

void Input::setKeyPressed(int key)
{
    keysPressed[key] = true;
}

bool Input::isKeyPressed(int key)
{
    return keysPressed[key];
}

bool Input::wasKeyReleased(int key)
{
    bool temp = keysReleased[key];
    keysReleased[key] = false;
    return temp;
}

std::vector<int> Input::getKeysPressed()
{
    std::vector<int> keys;
    for (int i = 0; i < KEY_NUMBER; i++)
    {
        if (keysPressed[i])
            keys.push_back(i);
    }
    return keys;
}

std::vector<int> Input::getKeysReleased()
{
    std::vector<int> keys;
    for (int i = 0; i < KEY_NUMBER; i++)
    {
        if (keysReleased[i])
            keys.push_back(i);
    }
    return keys;
}

void Input::setMousePressed(int button)
{
    mousePressed[button] = true;
}

bool Input::isMousePressed(int button)
{
    return mousePressed[button];
}

bool Input::wasMouseReleased(int button)
{
    bool temp = mouseReleased[button];
    mouseReleased[button] = false;
    return temp;
}

std::vector<int> Input::getMousePressed()
{
    std::vector<int> buttons;
    for (int i = 0; i < MOUSE_NUMBER; i++)
    {
        if (mousePressed[i])
            buttons.push_back(i);
    }
    return buttons;
}

std::vector<int> Input::getMouseReleased()
{
    std::vector<int> buttons;
    for (int i = 0; i < MOUSE_NUMBER; i++)
    {
        if (mouseReleased[i])
            buttons.push_back(i);
    }
    return buttons;
}

dVector2 Input::getMousePositionScreen()
{
    return mousePosition;
}

dVector2 Input::getMousePositionWindow(dVector2 window)
{
    return Vector::convertCoordinateSystem(mousePosition, {0, 0}, {window.x, window.y}, {0, 1}, {1, 0});
}

dVector2 Input::getMousePositionWorld(dVector2 window)
{
    double aspectRatio = window.x / window.y;
    return Vector::convertCoordinateSystem(mousePosition, {0, 0}, {window.x, window.y}, {-1, 2 / aspectRatio - 1}, {1, -1});
}