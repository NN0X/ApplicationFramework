#include "context.h"

Context::Context()
{
    label = "";
    objectLabels = std::unordered_map<std::string, uInt>();
    objects = std::unordered_map<uInt, ObjectPtr>();
    Log::log("Context created");
}

Context::~Context()
{
    clearObjects();
    Log::log("Context destroyed");
}

void Context::draw()
{
    for (auto &object : objects)
    {
        if (object.second.type == ObjectType::OBJECT2D)
        {
            object.second.object2d->draw();
        }
        else if (object.second.type == ObjectType::TEXT)
        {
            object.second.text->draw();
        }
    }
}

ObjectPtr Context::getObject(uInt id)
{
    if (objects.find(id) != objects.end())
    {
        return objects[id];
    }
    Log::log("Object ID not found");
    return ObjectPtr();
}

ObjectPtr Context::getObject(const std::string &label) // temporary solution
{
    if (objectLabels.find(label) != objectLabels.end())
    {
        return objects[objectLabels[label]];
    }
    Log::log("Object label not found");
    return ObjectPtr();
}

bool Context::inObjectHitbox(uInt id, const dVector2 &position)
{
    if (objects.find(id) != objects.end())
    {
        if (objects[id].type == ObjectType::OBJECT2D)
        {
            return objects[id].object2d->inHitbox(position);
        }
        else if (objects[id].type == ObjectType::TEXT)
        {
            return objects[id].text->inHitbox(position);
        }
        else
            Log::log("Wrong object type");
    }
    Log::log("Object ID not found");
    return false;
}

uInt Context::createObject2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath)
{
    Object2D *object2d = new Object2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath);
    object2d->setID(Utility::genUniqueID());
    objects[object2d->getID()] = {ObjectType::OBJECT2D, object2d};
    return object2d->getID();
}

uInt Context::createText(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath)
{
    Text *textObject = new Text(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath);
    textObject->setID(Utility::genUniqueID());
    objects[textObject->getID()] = {ObjectType::TEXT, textObject};
    return textObject->getID();
}

void Context::setObjectLabel(uInt id, const std::string &label)
{
    if (objects.find(id) != objects.end())
    {
        if (objectLabels.find(label) != objectLabels.end())
        {
            Log::log("Object label already exists");
            return;
        }
        if (objects[id].type == ObjectType::OBJECT2D && objects[id].object2d->getLabel() == "")
        {
            objects[id].object2d->setLabel(label);
        }
        else if (objects[id].type == ObjectType::OBJECT2D)
        {
            objectLabels.erase(objects[id].object2d->getLabel());
            objects[id].object2d->setLabel(label);
        }
        else if (objects[id].type == ObjectType::TEXT && objects[id].text->getLabel() == "")
        {
            objects[id].text->setLabel(label);
        }
        else if (objects[id].type == ObjectType::TEXT)
        {
            objectLabels.erase(objects[id].text->getLabel());
            objects[id].text->setLabel(label);
        }

        objectLabels[label] = id;
        return;
    }
    Log::log("Object ID not found");
}

void Context::destroyObject(uInt id)
{
    if (objects.find(id) != objects.end())
    {
        if (objects[id].type == ObjectType::OBJECT2D)
        {
            delete objects[id].object2d;
            objects.erase(id);
            return;
        }
        else if (objects[id].type == ObjectType::TEXT)
        {
            delete objects[id].text;
            objects.erase(id);
            return;
        }
        else
            Log::log("Wrong object type");
    }
    Log::log("Object ID not found");
}

void Context::clearObjects()
{
    Log::log("Clearing objects");

    for (auto &object : objects)
    {
        if (object.second.type == ObjectType::OBJECT2D)
        {
            delete object.second.object2d;
        }
        else if (object.second.type == ObjectType::TEXT)
        {
            delete object.second.text;
        }
    }

    objects.clear();
    objectLabels.clear();

    Log::log("Objects cleared");
}

void Context::clearObjects2D()
{
    Log::log("Clearing objects 2D");

    for (auto &object : objects)
    {
        if (object.second.type == ObjectType::OBJECT2D)
        {
            delete object.second.object2d;
        }
    }

    for (auto it = objects.begin(); it != objects.end();)
    {
        if (it->second.type == ObjectType::OBJECT2D)
        {
            it = objects.erase(it);
        }
        else
        {
            it++;
        }
    }

    Log::log("Objects 2D cleared");
}

void Context::clearTexts()
{
    Log::log("Clearing texts");

    for (auto &object : objects)
    {
        if (object.second.type == ObjectType::TEXT)
        {
            delete object.second.text;
        }
    }

    for (auto it = objects.begin(); it != objects.end();)
    {
        if (it->second.type == ObjectType::TEXT)
        {
            it = objects.erase(it);
        }
        else
        {
            it++;
        }
    }

    Log::log("Texts cleared");
}

void Context::setID(uInt id)
{
    this->id = id;
}

uInt Context::getID()
{
    return id;
}

void Context::setLabel(const std::string &label)
{
    this->label = label;
}

std::string Context::getLabel()
{
    return label;
}