#include "application.h"
#include "context.h"
#include "input.h"
#include "object.h"
#include "vector.h"
#include "log.h"

namespace AF
{
    Application *init()
    {
        return new Application();
    }

    Application *init(iVector2 windowSize, std::string windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync)
    {
        return new Application(windowSize, windowTitle, fullscreen, resizable, decorated, vsync);
    }

    void quit(Application *app)
    {
        delete app;
    }

    void update(Application *app)
    {
        app->update();
    }

    bool isRunning(Application *app)
    {
        return app->isRunning();
    }

    void setIsRunning(Application *app, bool isRunning)
    {
        app->setIsRunning(isRunning);
    }

    uInt createContext(Application *app)
    {
        return app->createContext();
    }

    void setCurrentContext(Application *app, uInt index)
    {
        app->setCurrentContext(index);
    }

    void setCurrentContext(Application *app, std::string label)
    {
        app->setCurrentContext(label);
    }

    void loadContext(Application *app, std::string path)
    {
        app->loadContext(path);
    }

    void destroyContext(Application *app, uInt index)
    {
        app->destroyContext(index);
    }

    void destroyContext(Application *app, std::string label)
    {
        app->destroyContext(label);
    }

    void clearContexts(Application *app)
    {
        app->clearContexts();
    }

    InputManager *getInput(Application *app)
    {
        return app->getInput();
    }

    std::string getWindowTitle(Application *app)
    {
        return app->getWindowTitle();
    }

    iVector2 getWindowSize(Application *app)
    {
        return app->getWindowSize();
    }

    uInt getCurrentContextIndex(Application *app)
    {
        return app->getCurrentContextIndex();
    }

    double getTime(Application *app)
    {
        return app->getTime();
    }

    namespace Input
    {
        void setKeyPressed(Application *app, uInt key)
        {
            app->getInput()->setKeyPressed(key);
        }

        void setKeyReleased(Application *app, uInt key)
        {
            app->getInput()->setKeyReleased(key);
        }

        void setMouseButtonPressed(Application *app, uInt button)
        {
            app->getInput()->setMouseButtonPressed(button);
        }

        void setMouseButtonReleased(Application *app, uInt button)
        {
            app->getInput()->setMouseButtonReleased(button);
        }

        void setMousePosition(Application *app, dVector2 position)
        {
            app->getInput()->setMousePosition(position);
        }

        bool isKeyPressed(Application *app, uInt key)
        {
            return app->getInput()->isKeyPressed(key);
        }

        bool wasKeyReleased(Application *app, uInt key)
        {
            return app->getInput()->wasKeyReleased(key);
        }

        bool isMouseButtonPressed(Application *app, uInt button)
        {
            return app->getInput()->isMouseButtonPressed(button);
        }

        bool wasMouseButtonReleased(Application *app, uInt button)
        {
            return app->getInput()->wasMouseButtonReleased(button);
        }

        std::vector<uInt> getKeysPressed(Application *app)
        {
            return app->getInput()->getKeysPressed();
        }

        std::vector<uInt> getMouseButtonsPressed(Application *app)
        {
            return app->getInput()->getMouseButtonsPressed();
        }

        dVector2 getMousePositionScreen(Application *app)
        {
            return app->getInput()->getMousePositionScreen();
        }

        dVector2 getMousePositionWindow(Application *app)
        {
            return app->getInput()->getMousePositionWindow(app->getWindowSize());
        }

        dVector2 getMousePositionWorld(Application *app)
        {
            return app->getInput()->getMousePositionWorld(app->getWindowSize());
        }
    }

    namespace Object
    {
        uInt create2D(Application *app, dVector2 position, dVector2 scale, double rotation, std::string verticesPath, std::string texturePath, std::string vertexPath, std::string fragmentPath)
        {
            return app->createObject2D(position, scale, rotation, app->getWindowSize(), verticesPath, texturePath, vertexPath, fragmentPath);
        }

        void destroy2D(Application *app, uInt index)
        {
            app->destroyObject2D(index);
        }

        void destroy2D(Application *app, std::string label)
        {
            app->destroyObject2D(label);
        }

        void clear2D(Application *app)
        {
            app->clearObjects2D();
        }

        uInt createText(Application *app, std::string text, dVector2 position, dVector2 scale, double rotation, std::string fontPath, std::string vertexPath, std::string fragmentPath)
        {
            return app->createText(text, position, scale, rotation, app->getWindowSize(), fontPath, vertexPath, fragmentPath);
        }

        void destroyText(Application *app, uInt index)
        {
            app->destroyText(index);
        }

        void destroyText(Application *app, std::string label)
        {
            app->destroyText(label);
        }

        void clearTexts(Application *app)
        {
            app->clearTexts();
        }

        bool isClicked(Application *app, uInt index)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                bool clicked = app->inObjectHitbox(index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (clicked)
                {
                    Log::log("Object " + std::to_string(index) + " clicked");
                    return true;
                }
            }
            return false;
        }

        bool isClicked(Application *app, std::string label)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                bool clicked = app->inObjectHitbox(label, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (clicked)
                {
                    Log::log("Object " + label + " clicked");
                    return true;
                }
            }
            return false;
        }

        bool isHovered(Application *app, uInt index)
        {
            bool hovered = app->inObjectHitbox(index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
            if (hovered)
            {
                Log::log("Object " + std::to_string(index) + " hovered");
                return true;
            }
            return false;
        }

        bool isHovered(Application *app, std::string label)
        {
            bool hovered = app->inObjectHitbox(label, app->getInput()->getMousePositionWorld(app->getWindowSize()));
            if (hovered)
            {
                Log::log("Object " + label + " hovered");
                return true;
            }
            return false;
        }
    }

    namespace Logs
    {
        void log(std::string message)
        {
            Log::log(message);
        }
    }

}