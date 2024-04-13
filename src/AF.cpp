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
        uInt create(Application *app, uInt type, dVector2 position, dVector2 scale, double rotation, std::string verticesPath, std::string texturePath, std::string vertexPath, std::string fragmentPath)
        {
            if (type == OBJECT2D)
                return app->createObject2D(position, scale, rotation, app->getWindowSize(), verticesPath, texturePath, vertexPath, fragmentPath);
            else if (type == TEXT)
                Log::log("Text object must be created with createText function");
            else
                Log::log("Unknown object type");
            return 0;
        }

        uInt create(Application *app, std::string text, dVector2 position, dVector2 scale, double rotation, std::string fontPath, std::string vertexPath, std::string fragmentPath)
        {
            return app->createText(text, position, scale, rotation, app->getWindowSize(), fontPath, vertexPath, fragmentPath);
        }

        void destroy(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->destroyObject2D(object.index);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->destroyText(object.index);
            }
            else
                Log::log("Unknown object type");
        }

        void destroy(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->destroyObject2D(object.index);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->destroyText(object.index);
            }
            else
                Log::log("Unknown object type");
        }

        void clear(Application *app, uInt type)
        {
            if (type == OBJECT2D)
            {
                app->clearObjects2D();
            }
            else if (type == TEXT)
            {
                app->clearTexts();
            }
            else
                Log::log("Unknown object type");
        }

        bool isClicked(Application *app, uInt index)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                ObjectID object = app->getObjectID(index);
                if (object.type == ObjectType::OBJECT2D)
                {
                    bool clicked = app->inObject2DHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + std::to_string(index) + " clicked");
                        return true;
                    }
                }
                else if (object.type == ObjectType::TEXT)
                {
                    bool clicked = app->inTextHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + std::to_string(index) + " clicked");
                        return true;
                    }
                }
                else
                    Log::log("Unknown object type");
                return false;
            }
            return false;
        }

        bool isClicked(Application *app, std::string label)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                ObjectID object = app->getObjectID(label);
                if (object.type == ObjectType::OBJECT2D)
                {
                    bool clicked = app->inObject2DHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + label + " clicked");
                        return true;
                    }
                }
                else if (object.type == ObjectType::TEXT)
                {
                    bool clicked = app->inTextHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + label + " clicked");
                        return true;
                    }
                }
                else
                    Log::log("Unknown object type");
                return false;
            }
            return false;
        }

        bool isHovered(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                bool hovered = app->inObject2DHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + std::to_string(index) + " hovered");
                    return true;
                }
            }
            else if (object.type == ObjectType::TEXT)
            {
                bool hovered = app->inTextHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + std::to_string(index) + " hovered");
                    return true;
                }
            }
            else
                Log::log("Unknown object type");
            return false;
        }

        bool isHovered(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                bool hovered = app->inObject2DHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + label + " hovered");
                    return true;
                }
            }
            else if (object.type == ObjectType::TEXT)
            {
                bool hovered = app->inTextHitbox(object.index, app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + label + " hovered");
                    return true;
                }
            }
            else
                Log::log("Unknown object type");
            return false;
        }

        void transformPosition(Application *app, uInt index, dVector2 transform)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformPosition(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformPosition(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformPosition(Application *app, std::string label, dVector2 transform)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformPosition(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformPosition(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformScale(Application *app, uInt index, dVector2 transform)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformScale(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformScale(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformScale(Application *app, std::string label, dVector2 transform)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformScale(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformScale(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformRotation(Application *app, uInt index, double transform)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformRotation(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformRotation(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformRotation(Application *app, std::string label, double transform)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->transformRotation(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->transformRotation(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWorld(Application *app, uInt index, dVector2 position)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setPositionWorld(position);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setPositionWorld(position);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWorld(Application *app, std::string label, dVector2 position)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setPositionWorld(position);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setPositionWorld(position);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWindow(Application *app, uInt index, dVector2 position)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setPositionWindow(position, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setPositionWindow(position, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWindow(Application *app, std::string label, dVector2 position)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setPositionWindow(position, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setPositionWindow(position, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWorld(Application *app, uInt index, dVector2 scale)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setScaleWorld(scale);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setScaleWorld(scale);
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWorld(Application *app, std::string label, dVector2 scale)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setScaleWorld(scale);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setScaleWorld(scale);
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWindow(Application *app, uInt index, dVector2 scale)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setScaleWindow(scale, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setScaleWindow(scale, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWindow(Application *app, std::string label, dVector2 scale)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setScaleWindow(scale, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setScaleWindow(scale, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setRotation(Application *app, uInt index, double rotation)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setRotation(rotation);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setRotation(rotation);
            }
            else
                Log::log("Unknown object type");
        }

        void setRotation(Application *app, std::string label, double rotation)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->getObject2D(object.index)->setRotation(rotation);
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->getText(object.index)->setRotation(rotation);
            }
            else
                Log::log("Unknown object type");
        }

        dVector2 getPositionWorld(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getPositionWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getPositionWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWorld(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getPositionWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getPositionWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getPositionWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getPositionWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getPositionWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getPositionWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getScaleWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getScaleWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getScaleWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getScaleWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getScaleWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getScaleWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getScaleWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getScaleWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        double getRotation(Application *app, uInt index)
        {
            ObjectID object = app->getObjectID(index);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getRotation();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getRotation();
            }
            else
                Log::log("Unknown object type");
            return 0;
        }

        double getRotation(Application *app, std::string label)
        {
            ObjectID object = app->getObjectID(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return app->getObject2D(object.index)->getRotation();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return app->getText(object.index)->getRotation();
            }
            else
                Log::log("Unknown object type");
            return 0;
        }
    }
    namespace Logs
    {
        void log(std::string message)
        {
            Log::log(message);
        }

        void error(std::string message)
        {
            Log::error(message);
        }

        void setFlags(Application *app, bool print, bool save, bool enable)
        {
            app->getLog()->setFlags(print, save, enable);
        }
    }
}