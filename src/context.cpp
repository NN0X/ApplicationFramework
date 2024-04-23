#include "context.h"

Context::Context(uInt id)
{
    this->id = id;
    Logger::log("Context '" + std::to_string(id) + "' created");
}

Context::~Context()
{
    clearObjects();
    Logger::log("Context '" + std::to_string(id) + "' destroyed");
}

void Context::draw()
{
    for (auto &object : objects)
    {
        switch (object.second.type)
        {
        case NONE:
            break;

        case OBJECT:
            break;

        case OBJECT2D:
            object.second.object2d->draw();
            break;

        case TEXT:
            object.second.text->draw();
            break;

        case DATA:
            break;

        default:
            break;
        }
    }
}

bool Context::inObjectHitbox(uInt id, const dVector2 &position)
{
    if (objects.find(id) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(id) + "' not found");
        return false;
    }

    switch (objects[id].type)
    {
    case NONE:
        return false;

    case OBJECT:
        return false;

    case OBJECT2D:
        return objects[id].object2d->inHitbox(position);

    case TEXT:
        return objects[id].text->inHitbox(position);

    case DATA:
        return false;

    default:
        return false;
    }
}

uInt Context::createObject2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
{
    uInt id = Utils::genUniqueID();
    objects[id] = {OBJECT2D, new Object2D(id, position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath)};
    return id;
}

uInt Context::createText(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
{
    uInt id = Utils::genUniqueID();
    objects[id] = {TEXT, new Text(id, text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath)};
    return id;
}

void Context::addChildToObject(uInt parentID, uInt childID)
{
    if (objects.find(parentID) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(parentID) + "' not found");
        return;
    }

    if (objects.find(childID) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(childID) + "' not found");
        return;
    }

    if (objects[childID].object2d->getParent() != 0)
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(childID) + "' already has a parent");
        return;
    }

    objects[parentID].object2d->addChild(childID, objects[childID]);
    objects[childID].object2d->setParent(parentID);
}

void Context::removeChildFromObject(uInt parentID, uInt childID)
{
    if (objects.find(parentID) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(parentID) + "' not found");
        return;
    }

    if (objects.find(childID) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(childID) + "' not found");
        return;
    }

    if (objects[childID].object2d->getParent() != parentID)
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(childID) + "' is not a child of object '" + std::to_string(parentID) + "'");
        return;
    }

    objects[parentID].object2d->removeChild(childID);
    objects[childID].object2d->setParent(0);
}

ObjectPtr Context::getObject(uInt id)
{
    if (objects.find(id) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(id) + "' not found");
        return ObjectPtr();
    }

    return objects[id];
}

void Context::destroyObject(uInt id)
{
    if (objects.find(id) == objects.end())
    {
        Logger::error("Context '" + std::to_string(id) + "': Object '" + std::to_string(id) + "' not found");
        return;
    }

    switch (objects[id].type)
    {
    case NONE:
        break;

    case OBJECT:
        delete objects[id].object;
        break;

    case OBJECT2D:
        delete objects[id].object2d;
        break;

    case TEXT:
        delete objects[id].text;
        break;

    case DATA:
        break;
    }
}

void Context::clearObjects()
{
    Logger::log("Context '" + std::to_string(id) + "': Clearing objects");

    for (auto &object : objects)
    {
        switch (object.second.type)
        {
        case NONE:
            break;

        case OBJECT:
            delete object.second.object;
            break;

        case OBJECT2D:
            delete object.second.object2d;
            break;

        case TEXT:
            delete object.second.text;
            break;

        case DATA:
            break;
        }
    }

    objects.clear();

    Logger::log("Context '" + std::to_string(id) + "': Objects cleared");
}

void Context::clearObjects2D()
{
    Logger::log("Context '" + std::to_string(id) + "': Clearing 2D objects");

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].type == OBJECT2D)
        {
            delete objects[i].object2d;
            objects.erase(i);
            i--;
        }
    }

    Logger::log("Context '" + std::to_string(id) + "': 2D objects cleared");
}

void Context::clearTexts()
{
    Logger::log("Context '" + std::to_string(id) + "': Clearing text objects");

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].type == TEXT)
        {
            delete objects[i].text;
            objects.erase(i);
            i--;
        }
    }

    Logger::log("Context '" + std::to_string(id) + "': Text objects cleared");
}