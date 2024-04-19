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

    Application *init(const iVector2 &windowSize, const std::string &windowTitle, bool fullscreen, bool resizable, bool decorated, bool vsync)
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

    void setContextLabel(Application *app, uInt index, const std::string &label)
    {
        app->setContextLabel(index, label);
    }

    void setCurrentContext(Application *app, uInt index)
    {
        app->setCurrentContext(index);
    }

    void setCurrentContext(Application *app, const std::string &label)
    {
        app->setCurrentContext(label);
    }

    void loadContext(Application *app, const std::string &path)
    {
        app->loadContext(path);
    }

    void destroyContext(Application *app, uInt index)
    {
        app->destroyContext(index);
    }

    void destroyContext(Application *app, const std::string &label)
    {
        app->destroyContext(label);
    }

    void clearContexts(Application *app)
    {
        app->clearContexts();
    }

    const std::string &getWindowTitle(Application *app)
    {
        return app->getWindowTitle();
    }

    iVector2 getWindowSize(Application *app)
    {
        return app->getWindowSize();
    }

    uInt getCurrentContextID(Application *app)
    {
        return app->getCurrentContextID();
    }

    double getTime(Application *app)
    {
        return app->getTime();
    }

    double getDeltaTime(Application *app)
    {
        return app->getDeltaTime();
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

        void setMousePosition(Application *app, const dVector2 &position)
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
        uInt create(Application *app, uInt type, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
        {
            if (type == OBJECT2D)
                return app->createObject2D(position, scale, rotation, app->getWindowSize(), verticesPath, texturePath, vertexPath, fragmentPath);
            else if (type == TEXT)
                Log::log("Text object must be created with createText function");
            else
                Log::log("Unknown object type");
            return 0;
        }

        uInt create(Application *app, const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
        {
            return app->createText(text, position, scale, rotation, app->getWindowSize(), fontPath, vertexPath, fragmentPath);
        }

        void setLabel(Application *app, uInt id, const std::string &label)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setLabel(label);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setLabel(label);
            }
            else
                Log::log("Unknown object type");
        }

        void destroy(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->destroyObject(object.object2d->getID());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->destroyObject(object.text->getID());
            }
            else
                Log::log("Unknown object type");
        }

        void destroy(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                app->destroyObject(object.object2d->getID());
            }
            else if (object.type == ObjectType::TEXT)
            {
                app->destroyObject(object.text->getID());
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

        bool isClicked(Application *app, uInt id)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                ObjectPtr object = app->getObject(id);
                if (object.type == ObjectType::OBJECT2D)
                {
                    bool clicked = app->inObjectHitbox(object.object2d->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + std::to_string(id) + " clicked");
                        return true;
                    }
                }
                else if (object.type == ObjectType::TEXT)
                {
                    bool clicked = app->inObjectHitbox(object.text->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + std::to_string(id) + " clicked");
                        return true;
                    }
                }
                else
                    Log::log("Unknown object type");
                return false;
            }
            return false;
        }

        bool isClicked(Application *app, const std::string &label)
        {
            if (app->getInput()->isMouseButtonPressed(MOUSE_LEFT))
            {
                ObjectPtr object = app->getObject(label);
                if (object.type == ObjectType::OBJECT2D)
                {
                    bool clicked = app->inObjectHitbox(object.object2d->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Log::log("Object " + label + " clicked");
                        return true;
                    }
                }
                else if (object.type == ObjectType::TEXT)
                {
                    bool clicked = app->inObjectHitbox(object.text->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
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

        bool isHovered(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                bool hovered = app->inObjectHitbox(object.object2d->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + std::to_string(id) + " hovered");
                    return true;
                }
            }
            else if (object.type == ObjectType::TEXT)
            {
                bool hovered = app->inObjectHitbox(object.text->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + std::to_string(id) + " hovered");
                    return true;
                }
            }
            else
                Log::log("Unknown object type");
            return false;
        }

        bool isHovered(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                bool hovered = app->inObjectHitbox(object.object2d->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Log::log("Object " + label + " hovered");
                    return true;
                }
            }
            else if (object.type == ObjectType::TEXT)
            {
                bool hovered = app->inObjectHitbox(object.text->getID(), app->getInput()->getMousePositionWorld(app->getWindowSize()));
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

        void transformPosition(Application *app, uInt id, const dVector2 &transform)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformPosition(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformPosition(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformPosition(Application *app, const std::string &label, const dVector2 &transform)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformPosition(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformPosition(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformScale(Application *app, uInt id, const dVector2 &transform)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformScale(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformScale(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformScale(Application *app, const std::string &label, const dVector2 &transform)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformScale(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformScale(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformRotation(Application *app, uInt id, double transform)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformRotation(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformRotation(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void transformRotation(Application *app, const std::string &label, double transform)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->transformRotation(transform);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->transformRotation(transform);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWorld(Application *app, uInt id, const dVector2 &position)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setPositionWorld(position);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setPositionWorld(position);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWorld(Application *app, const std::string &label, const dVector2 &position)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setPositionWorld(position);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setPositionWorld(position);
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWindow(Application *app, uInt id, const dVector2 &position)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setPositionWindow(position, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setPositionWindow(position, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setPositionWindow(Application *app, const std::string &label, const dVector2 &position)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setPositionWindow(position, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setPositionWindow(position, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWorld(Application *app, uInt id, const dVector2 &scale)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setScaleWorld(scale);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setScaleWorld(scale);
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWorld(Application *app, const std::string &label, const dVector2 &scale)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setScaleWorld(scale);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setScaleWorld(scale);
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWindow(Application *app, uInt id, const dVector2 &scale)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setScaleWindow(scale, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setScaleWindow(scale, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setScaleWindow(Application *app, const std::string &label, const dVector2 &scale)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setScaleWindow(scale, app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setScaleWindow(scale, app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
        }

        void setRotation(Application *app, uInt id, double rotation)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setRotation(rotation);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setRotation(rotation);
            }
            else
                Log::log("Unknown object type");
        }

        void setRotation(Application *app, const std::string &label, double rotation)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                object.object2d->setRotation(rotation);
            }
            else if (object.type == ObjectType::TEXT)
            {
                object.text->setRotation(rotation);
            }
            else
                Log::log("Unknown object type");
        }

        dVector2 getPositionWorld(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getPositionWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getPositionWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWorld(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getPositionWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getPositionWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getPositionWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getPositionWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getPositionWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getPositionWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getScaleWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getScaleWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getScaleWorld();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getScaleWorld();
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getScaleWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getScaleWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getScaleWindow(app->getWindowSize());
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getScaleWindow(app->getWindowSize());
            }
            else
                Log::log("Unknown object type");
            return dVector2();
        }

        double getRotation(Application *app, uInt id)
        {
            ObjectPtr object = app->getObject(id);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getRotation();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getRotation();
            }
            else
                Log::log("Unknown object type");
            return 0;
        }

        double getRotation(Application *app, const std::string &label)
        {
            ObjectPtr object = app->getObject(label);
            if (object.type == ObjectType::OBJECT2D)
            {
                return object.object2d->getRotation();
            }
            else if (object.type == ObjectType::TEXT)
            {
                return object.text->getRotation();
            }
            else
                Log::log("Unknown object type");
            return 0;
        }
    }
    namespace Logs
    {
        void log(const std::string &message)
        {
            Log::log(message);
        }

        void error(const std::string &message)
        {
            Log::error(message);
        }

        void setFlags(Application *app, bool print, bool save, bool enable)
        {
            app->getLog()->setFlags(print, save, enable);
        }
    }

    namespace Utils
    {
        void wait(uInt milliseconds)
        {
            Utility::wait(milliseconds);
        }

        uInt genID()
        {
            return Utility::genID();
        }
    }
}