#include "application.h"
#include "context.h"
#include "input.h"
#include "object.h"
#include "vector.h"
#include "log.h"

namespace AF
{
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

    void addLabel(Application *app, uInt id, const std::string &label)
    {
        app->addLabel(label, id);
    }

    uInt getID(Application *app, const std::string &label)
    {
        return app->getID(label);
    }

    void setCurrentContext(Application *app, uInt id)
    {
        app->setCurrentContext(id);
    }

    void setCurrentContext(Application *app, const std::string &label)
    {
        app->setCurrentContext(app->getID(label));
    }

    uInt loadContext(Application *app, const std::string &path)
    {
        return app->loadContext(path);
    }

    void destroyContext(Application *app, uInt id)
    {
        app->destroyContext(id);
    }

    void destroyContext(Application *app, const std::string &label)
    {
        app->destroyContext(app->getID(label));
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

    double getApplicationTime(Application *app)
    {
        return app->getApplicationTime();
    }

    double getDeltaTime(Application *app)
    {
        return app->getDeltaTime();
    }

    double getFPS(Application *app)
    {
        return app->getFPS();
    }

    namespace Input
    {
        void setKeyPressed(Application *app, uInt key)
        {
            app->getInputManager()->setKeyPressed(key);
        }

        void setKeyReleased(Application *app, uInt key)
        {
            app->getInputManager()->setKeyReleased(key);
        }

        void setMouseButtonPressed(Application *app, uInt button)
        {
            app->getInputManager()->setMouseButtonPressed(button);
        }

        void setMouseButtonReleased(Application *app, uInt button)
        {
            app->getInputManager()->setMouseButtonReleased(button);
        }

        void setMousePosition(Application *app, const dVector2 &position)
        {
            app->getInputManager()->setMousePosition(position);
        }

        bool isKeyPressed(Application *app, uInt key)
        {
            return app->getInputManager()->isKeyPressed(key);
        }

        bool wasKeyReleased(Application *app, uInt key)
        {
            return app->getInputManager()->wasKeyReleased(key);
        }

        bool isMouseButtonPressed(Application *app, uInt button)
        {
            return app->getInputManager()->isMouseButtonPressed(button);
        }

        bool wasMouseButtonReleased(Application *app, uInt button)
        {
            return app->getInputManager()->wasMouseButtonReleased(button);
        }

        std::vector<uInt> getKeysPressed(Application *app)
        {
            return app->getInputManager()->getKeysPressed();
        }

        std::vector<uInt> getMouseButtonsPressed(Application *app)
        {
            return app->getInputManager()->getMouseButtonsPressed();
        }

        dVector2 getMousePositionScreen(Application *app)
        {
            return app->getInputManager()->getMousePositionScreen();
        }

        dVector2 getMousePositionWindow(Application *app)
        {
            return app->getInputManager()->getMousePositionWindow(app->getWindowSize());
        }

        dVector2 getMousePositionWorld(Application *app)
        {
            return app->getInputManager()->getMousePositionWorld(app->getWindowSize());
        }
    }

    namespace Object
    {
        uInt createObject2D(Application *app, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &verticesPath, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
        {
            return app->getCurrentContext()->createObject2D(position, scale, rotation, Utils::loadBinaryDoubles(verticesPath), app->getWindowSize(), texturePath, vertexPath, fragmentPath);
        }

        uInt createText(Application *app, const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
        {
            return app->getCurrentContext()->createText(text, position, scale, rotation, app->getWindowSize(), fontPath, vertexPath, fragmentPath);
        }

        void addChild(Application *app, uInt parentID, uInt childID)
        {
            app->getCurrentContext()->addChildToObject(parentID, childID);
        }

        void addChild(Application *app, const std::string &parentLabel, const std::string &childLabel)
        {
            app->getCurrentContext()->addChildToObject(app->getID(parentLabel), app->getID(childLabel));
        }

        void removeChild(Application *app, uInt parentID, uInt childID)
        {
            app->getCurrentContext()->removeChildFromObject(parentID, childID);
        }

        void removeChild(Application *app, const std::string &parentLabel, const std::string &childLabel)
        {
            app->getCurrentContext()->removeChildFromObject(app->getID(parentLabel), app->getID(childLabel));
        }

        void setText(Application *app, uInt id, const std::string &text)
        {
            app->getCurrentContext()->getObject(id).text->setText(text);
        }

        void setText(Application *app, const std::string &label, const std::string &text)
        {
            app->getCurrentContext()->getObject(app->getID(label)).text->setText(text);
        }

        void destroy(Application *app, uInt id)
        {
            app->getCurrentContext()->destroyObject(id);
        }

        void destroy(Application *app, const std::string &label)
        {
            app->getCurrentContext()->destroyObject(app->getID(label));
        }

        void clear(Application *app, uInt type)
        {
            Logger::log("Clearing objects of type " + std::to_string(type));

            switch (type)
            {
            case OBJECT2D:
                app->getCurrentContext()->clearObjects2D();
                break;
            case TEXT:
                app->getCurrentContext()->clearTexts();
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        bool isClicked(Application *app, uInt id)
        {
            bool clicked = false;
            if (app->getInputManager()->isMouseButtonPressed(MOUSE_LEFT))
            {
                switch (app->getCurrentContext()->getObject(id).type)
                {
                case OBJECT2D:
                    clicked = app->getCurrentContext()->inObjectHitbox(id, app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Logger::log("Object '" + std::to_string(id) + "' clicked");
                        return true;
                    }
                    break;
                case TEXT:
                    clicked = app->getCurrentContext()->inObjectHitbox(id, app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Logger::log("Object '" + std::to_string(id) + "' clicked");
                        return true;
                    }
                    break;
                default:
                    Logger::error("Unknown object type");
                }
            }
            return false;
        }

        bool isClicked(Application *app, const std::string &label)
        {
            bool clicked = false;
            if (app->getInputManager()->isMouseButtonPressed(MOUSE_LEFT))
            {
                switch (app->getCurrentContext()->getObject(app->getID(label)).type)
                {
                case OBJECT2D:
                    clicked = app->getCurrentContext()->inObjectHitbox(app->getID(label), app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Logger::log("Object '" + label + "' clicked");
                        return true;
                    }
                    break;
                case TEXT:
                    clicked = app->getCurrentContext()->inObjectHitbox(app->getID(label), app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                    if (clicked)
                    {
                        Logger::log("Object '" + label + "' clicked");
                        return true;
                    }
                    break;
                default:
                    Logger::error("Unknown object type");
                }
            }
            return false;
        }

        bool isHovered(Application *app, uInt id)
        {
            bool hovered = false;
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                hovered = app->getCurrentContext()->inObjectHitbox(id, app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Logger::log("Object '" + std::to_string(id) + "' hovered");
                    return true;
                }
                break;
            case TEXT:
                hovered = app->getCurrentContext()->inObjectHitbox(id, app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Logger::log("Object '" + std::to_string(id) + "' hovered");
                    return true;
                }
                break;
            default:
                Logger::error("Unknown object type");
            }
            return false;
        }

        bool isHovered(Application *app, const std::string &label)
        {
            bool hovered = false;
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                hovered = app->getCurrentContext()->inObjectHitbox(app->getID(label), app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Logger::log("Object '" + label + "' hovered");
                    return true;
                }
                break;
            case TEXT:
                hovered = app->getCurrentContext()->inObjectHitbox(app->getID(label), app->getInputManager()->getMousePositionWorld(app->getWindowSize()));
                if (hovered)
                {
                    Logger::log("Object '" + label + "' hovered");
                    return true;
                }
                break;
            default:
                Logger::error("Unknown object type");
            }
            return false;
        }

        void transformPosition(Application *app, uInt id, const dVector2 &transform)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->transformPosition(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->transformPosition(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void transformPosition(Application *app, const std::string &label, const dVector2 &transform)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->transformPosition(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->transformPosition(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void transformScale(Application *app, uInt id, const dVector2 &transform)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->transformScale(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->transformScale(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void transformScale(Application *app, const std::string &label, const dVector2 &transform)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->transformScale(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->transformScale(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void transformRotation(Application *app, uInt id, double transform)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->transformRotation(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->transformRotation(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void transformRotation(Application *app, const std::string &label, double transform)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->transformRotation(transform);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->transformRotation(transform);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setPositionWorld(Application *app, uInt id, const dVector2 &position)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->setPosition(position);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->setPosition(position);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setPositionWorld(Application *app, const std::string &label, const dVector2 &position)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->setPosition(position);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->setPosition(position);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setPositionWindow(Application *app, uInt id, const dVector2 &position)
        {
            double aspectRatio = 0;
            dVector2 positionWindow;
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                positionWindow = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(id).object2d->setPosition(positionWindow);
                break;
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                positionWindow = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(id).text->setPosition(positionWindow);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setPositionWindow(Application *app, const std::string &label, const dVector2 &position)
        {
            double aspectRatio = 0;
            dVector2 positionWindow;
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                positionWindow = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(app->getID(label)).object2d->setPosition(positionWindow);
                break;
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                positionWindow = Vector::convertCoordinateSystem(position, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(app->getID(label)).text->setPosition(positionWindow);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setScaleWorld(Application *app, uInt id, const dVector2 &scale)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->setScale(scale);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->setScale(scale);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setScaleWorld(Application *app, const std::string &label, const dVector2 &scale)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->setScale(scale);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->setScale(scale);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setScaleWindow(Application *app, uInt id, const dVector2 &scale)
        {
            double aspectRatio = 0;
            dVector2 scaleWindow;
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scaleWindow = Vector::convertCoordinateSystem(scale, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(id).object2d->setScale(scaleWindow);
                break;
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scaleWindow = Vector::convertCoordinateSystem(scale, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(id).text->setScale(scaleWindow);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setScaleWindow(Application *app, const std::string &label, const dVector2 &scale)
        {
            double aspectRatio = 0;
            dVector2 scaleWindow;
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scaleWindow = Vector::convertCoordinateSystem(scale, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(app->getID(label)).object2d->setScale(scaleWindow);
                break;
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scaleWindow = Vector::convertCoordinateSystem(scale, {0, 1}, {1, 0}, {-1, 2 / aspectRatio - 1}, {1, -1});
                app->getCurrentContext()->getObject(app->getID(label)).text->setScale(scaleWindow);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setRotation(Application *app, uInt id, double rotation)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(id).object2d->setRotation(rotation);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(id).text->setRotation(rotation);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        void setRotation(Application *app, const std::string &label, double rotation)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                app->getCurrentContext()->getObject(app->getID(label)).object2d->setRotation(rotation);
                break;
            case TEXT:
                app->getCurrentContext()->getObject(app->getID(label)).text->setRotation(rotation);
                break;
            default:
                Logger::error("Unknown object type");
            }
        }

        dVector2 getPositionWorld(Application *app, uInt id)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(id).object2d->getPosition();
            case TEXT:
                return app->getCurrentContext()->getObject(id).text->getPosition();
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getPositionWorld(Application *app, const std::string &label)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(app->getID(label)).object2d->getPosition();
            case TEXT:
                return app->getCurrentContext()->getObject(app->getID(label)).text->getPosition();
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, uInt id)
        {
            double aspectRatio = 0;
            dVector2 position;
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                position = app->getCurrentContext()->getObject(id).object2d->getPosition();
                return Vector::convertCoordinateSystem(position, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                position = app->getCurrentContext()->getObject(id).text->getPosition();
                return Vector::convertCoordinateSystem(position, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getPositionWindow(Application *app, const std::string &label)
        {
            double aspectRatio = 0;
            dVector2 position;
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                position = app->getCurrentContext()->getObject(app->getID(label)).object2d->getPosition();
                return Vector::convertCoordinateSystem(position, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                position = app->getCurrentContext()->getObject(app->getID(label)).text->getPosition();
                return Vector::convertCoordinateSystem(position, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, uInt id)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(id).object2d->getScale();
            case TEXT:
                return app->getCurrentContext()->getObject(id).text->getScale();
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getScaleWorld(Application *app, const std::string &label)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(app->getID(label)).object2d->getScale();
            case TEXT:
                return app->getCurrentContext()->getObject(app->getID(label)).text->getScale();
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, uInt id)
        {
            double aspectRatio = 0;
            dVector2 scale;
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scale = app->getCurrentContext()->getObject(id).object2d->getScale();
                return Vector::convertCoordinateSystem(scale, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scale = app->getCurrentContext()->getObject(id).text->getScale();
                return Vector::convertCoordinateSystem(scale, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        dVector2 getScaleWindow(Application *app, const std::string &label)
        {
            double aspectRatio = 0;
            dVector2 scale;
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scale = app->getCurrentContext()->getObject(app->getID(label)).object2d->getScale();
                return Vector::convertCoordinateSystem(scale, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            case TEXT:
                aspectRatio = (double)app->getWindowSize().x / app->getWindowSize().y;
                scale = app->getCurrentContext()->getObject(app->getID(label)).text->getScale();
                return Vector::convertCoordinateSystem(scale, {-1, 2 / aspectRatio - 1}, {1, -1}, {0, 1}, {1, 0});
            default:
                Logger::error("Unknown object type");
            }
            return dVector2();
        }

        double getRotation(Application *app, uInt id)
        {
            switch (app->getCurrentContext()->getObject(id).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(id).object2d->getRotation();
            case TEXT:
                return app->getCurrentContext()->getObject(id).text->getRotation();
            default:
                Logger::error("Unknown object type");
            }
            return 0;
        }

        double getRotation(Application *app, const std::string &label)
        {
            switch (app->getCurrentContext()->getObject(app->getID(label)).type)
            {
            case OBJECT2D:
                return app->getCurrentContext()->getObject(app->getID(label)).object2d->getRotation();
            case TEXT:
                return app->getCurrentContext()->getObject(app->getID(label)).text->getRotation();
            default:
                Logger::error("Unknown object type");
            }
            return 0;
        }
    }
    namespace Log
    {
        void init(const std::string &directory, bool withTime, const std::string &extension, bool print, bool save, bool enable)
        {
            Logger::init(directory, withTime, extension, print, save, enable);
        }

        void log(const std::string &message)
        {
            Logger::log(message);
        }

        void error(const std::string &message)
        {
            Logger::error(message);
        }

        void save(const std::string &path)
        {
            Logger::save(path);
        }

        void setFlags(bool print, bool save, bool enable)
        {
            Logger::setFlags(print, save, enable);
        }
    }

    namespace Utility
    {
        void wait(uInt milliseconds)
        {
            Utils::wait(milliseconds);
        }

        uInt genID()
        {
            return Utils::genID();
        }
    }
}