#pragma once

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vector.h"
#include "matrix.h"

#define KEY_SPACE 0
#define KEY_APOSTROPHE 1
#define KEY_COMMA 2
#define KEY_MINUS 3
#define KEY_PERIOD 4
#define KEY_SLASH 5
#define KEY_0 6
#define KEY_1 7
#define KEY_2 8
#define KEY_3 9
#define KEY_4 10
#define KEY_5 11
#define KEY_6 12
#define KEY_7 13
#define KEY_8 14
#define KEY_9 15
#define KEY_SEMICOLON 16
#define KEY_EQUAL 17
#define KEY_A 18
#define KEY_B 19
#define KEY_C 20
#define KEY_D 21
#define KEY_E 22
#define KEY_F 23
#define KEY_G 24
#define KEY_H 25
#define KEY_I 26
#define KEY_J 27
#define KEY_K 28
#define KEY_L 29
#define KEY_M 30
#define KEY_N 31
#define KEY_O 32
#define KEY_P 33
#define KEY_Q 34
#define KEY_R 35
#define KEY_S 36
#define KEY_T 37
#define KEY_U 38
#define KEY_V 39
#define KEY_W 40
#define KEY_X 41
#define KEY_Y 42
#define KEY_Z 43
#define KEY_LEFT_BRACKET 44
#define KEY_BACKSLASH 45
#define KEY_RIGHT_BRACKET 46
#define KEY_GRAVE_ACCENT 47
#define KEY_ESCAPE 48
#define KEY_ENTER 49
#define KEY_TAB 50
#define KEY_BACKSPACE 51
#define KEY_INSERT 52
#define KEY_DELETE 53
#define KEY_RIGHT 54
#define KEY_LEFT 55
#define KEY_DOWN 56
#define KEY_UP 57
#define KEY_PAGE_UP 58
#define KEY_PAGE_DOWN 59
#define KEY_HOME 60
#define KEY_END 61
#define KEY_CAPS_LOCK 62
#define KEY_SCROLL_LOCK 63
#define KEY_NUM_LOCK 64
#define KEY_PRINT_SCREEN 65
#define KEY_F1 66
#define KEY_F2 67
#define KEY_F3 68
#define KEY_F4 69
#define KEY_F5 70
#define KEY_F6 71
#define KEY_F7 72
#define KEY_F8 73
#define KEY_F9 74
#define KEY_F10 75
#define KEY_F11 76
#define KEY_F12 77
#define KEY_F13 78
#define KEY_F14 79
#define KEY_F15 80
#define KEY_F16 81
#define KEY_F17 82
#define KEY_F18 83
#define KEY_F19 84
#define KEY_F20 85
#define KEY_F21 86
#define KEY_F22 87
#define KEY_F23 88
#define KEY_F24 89
#define KEY_F25 90
#define KEY_KP_0 91
#define KEY_KP_1 92
#define KEY_KP_2 93
#define KEY_KP_3 94
#define KEY_KP_4 95
#define KEY_KP_5 96
#define KEY_KP_6 97
#define KEY_KP_7 98
#define KEY_KP_8 99
#define KEY_KP_9 100
#define KEY_KP_DECIMAL 101
#define KEY_KP_DIVIDE 102
#define KEY_KP_MULTIPLY 103
#define KEY_KP_SUBTRACT 104
#define KEY_KP_ADD 105
#define KEY_KP_ENTER 106
#define KEY_KP_EQUAL 107
#define KEY_LEFT_SHIFT 108
#define KEY_LEFT_CONTROL 109
#define KEY_LEFT_ALT 110
#define KEY_LEFT_SUPER 111
#define KEY_RIGHT_SHIFT 112
#define KEY_RIGHT_CONTROL 113
#define KEY_RIGHT_ALT 114
#define KEY_RIGHT_SUPER 115

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2

#define KEY_NUMBER 116
#define MOUSE_NUMBER 7

const int keyCodes[KEY_NUMBER] = {
    GLFW_KEY_SPACE,
    GLFW_KEY_APOSTROPHE,
    GLFW_KEY_COMMA,
    GLFW_KEY_MINUS,
    GLFW_KEY_PERIOD,
    GLFW_KEY_SLASH,
    GLFW_KEY_0,
    GLFW_KEY_1,
    GLFW_KEY_2,
    GLFW_KEY_3,
    GLFW_KEY_4,
    GLFW_KEY_5,
    GLFW_KEY_6,
    GLFW_KEY_7,
    GLFW_KEY_8,
    GLFW_KEY_9,
    GLFW_KEY_SEMICOLON,
    GLFW_KEY_EQUAL,
    GLFW_KEY_A,
    GLFW_KEY_B,
    GLFW_KEY_C,
    GLFW_KEY_D,
    GLFW_KEY_E,
    GLFW_KEY_F,
    GLFW_KEY_G,
    GLFW_KEY_H,
    GLFW_KEY_I,
    GLFW_KEY_J,
    GLFW_KEY_K,
    GLFW_KEY_L,
    GLFW_KEY_M,
    GLFW_KEY_N,
    GLFW_KEY_O,
    GLFW_KEY_P,
    GLFW_KEY_Q,
    GLFW_KEY_R,
    GLFW_KEY_S,
    GLFW_KEY_T,
    GLFW_KEY_U,
    GLFW_KEY_V,
    GLFW_KEY_W,
    GLFW_KEY_X,
    GLFW_KEY_Y,
    GLFW_KEY_Z,
    GLFW_KEY_LEFT_BRACKET,
    GLFW_KEY_BACKSLASH,
    GLFW_KEY_RIGHT_BRACKET,
    GLFW_KEY_GRAVE_ACCENT,
    GLFW_KEY_ESCAPE,
    GLFW_KEY_ENTER,
    GLFW_KEY_TAB,
    GLFW_KEY_BACKSPACE,
    GLFW_KEY_INSERT,
    GLFW_KEY_DELETE,
    GLFW_KEY_RIGHT,
    GLFW_KEY_LEFT,
    GLFW_KEY_DOWN,
    GLFW_KEY_UP,
    GLFW_KEY_PAGE_UP,
    GLFW_KEY_PAGE_DOWN,
    GLFW_KEY_HOME,
    GLFW_KEY_END,
    GLFW_KEY_CAPS_LOCK,
    GLFW_KEY_SCROLL_LOCK,
    GLFW_KEY_NUM_LOCK,
    GLFW_KEY_PRINT_SCREEN,
    GLFW_KEY_F1,
    GLFW_KEY_F2,
    GLFW_KEY_F3,
    GLFW_KEY_F4,
    GLFW_KEY_F5,
    GLFW_KEY_F6,
    GLFW_KEY_F7,
    GLFW_KEY_F8,
    GLFW_KEY_F9,
    GLFW_KEY_F10,
    GLFW_KEY_F11,
    GLFW_KEY_F12,
    GLFW_KEY_F13,
    GLFW_KEY_F14,
    GLFW_KEY_F15,
    GLFW_KEY_F16,
    GLFW_KEY_F17,
    GLFW_KEY_F18,
    GLFW_KEY_F19,
    GLFW_KEY_F20,
    GLFW_KEY_F21,
    GLFW_KEY_F22,
    GLFW_KEY_F23,
    GLFW_KEY_F24,
    GLFW_KEY_F25,
    GLFW_KEY_KP_0,
    GLFW_KEY_KP_1,
    GLFW_KEY_KP_2,
    GLFW_KEY_KP_3,
    GLFW_KEY_KP_4,
    GLFW_KEY_KP_5,
    GLFW_KEY_KP_6,
    GLFW_KEY_KP_7,
    GLFW_KEY_KP_8,
    GLFW_KEY_KP_9,
    GLFW_KEY_KP_DECIMAL,
    GLFW_KEY_KP_DIVIDE,
    GLFW_KEY_KP_MULTIPLY,
    GLFW_KEY_KP_SUBTRACT,
    GLFW_KEY_KP_ADD,
    GLFW_KEY_KP_ENTER,
    GLFW_KEY_KP_EQUAL,
    GLFW_KEY_LEFT_SHIFT,
    GLFW_KEY_LEFT_CONTROL,
    GLFW_KEY_LEFT_ALT,
    GLFW_KEY_LEFT_SUPER,
    GLFW_KEY_RIGHT_SHIFT,
    GLFW_KEY_RIGHT_CONTROL,
    GLFW_KEY_RIGHT_ALT,
    GLFW_KEY_RIGHT_SUPER};

const int mouseCodes[MOUSE_NUMBER] = {
    GLFW_MOUSE_BUTTON_1,
    GLFW_MOUSE_BUTTON_2,
    GLFW_MOUSE_BUTTON_3,
    GLFW_MOUSE_BUTTON_4,
    GLFW_MOUSE_BUTTON_5,
    GLFW_MOUSE_BUTTON_6,
    GLFW_MOUSE_BUTTON_7};

class Input
{
private:
    bool keysPressed[KEY_NUMBER] = {false};
    bool keysReleased[KEY_NUMBER] = {false};

    bool mousePressed[MOUSE_NUMBER] = {false};
    bool mouseReleased[MOUSE_NUMBER] = {false};

    dVector2 mousePosition;

public:
    void update(GLFWwindow *window);

    void setKeyPressed(int key);

    bool isKeyPressed(int key);
    bool wasKeyReleased(int key);

    std::vector<int> getKeysPressed();
    std::vector<int> getKeysReleased();

    void setMousePressed(int button);

    bool isMousePressed(int button);
    bool wasMouseReleased(int button);

    std::vector<int> getMousePressed();
    std::vector<int> getMouseReleased();

    dVector2 getMousePosition();
};