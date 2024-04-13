#include "context.h"

Context::Context()
{
    label = "";
    objects2d = std::vector<Object2D *>();
    texts = std::vector<Text *>();
    Log::log("Context created");
}

Context::~Context()
{
    clearObjects2D();
    clearTexts();
    Log::log("Context destroyed");
}

void Context::draw()
{
    for (uInt i = 0; i < objects2d.size(); i++)
    {
        objects2d[i]->draw();
    }
    for (uInt i = 0; i < texts.size(); i++)
    {
        texts[i]->draw();
    }
}

ObjectID Context::getObjectID(uInt index)
{
    if (index < objects.size())
    {
        return objects[index];
    }
    Log::log("Object index out of range");
    return ObjectID(-1, -1);
}

ObjectID Context::getObjectID(std::string label) // temporary solution
{
    for (ObjectID object : objects)
    {
        if (object.type == ObjectType::OBJECT2D && objects2d[object.index]->getLabel() == label)
        {
            return object;
        }
        else if (object.type == ObjectType::TEXT && texts[object.index]->getLabel() == label)
        {
            return object;
        }
    }
    Log::log("Object label not found");
    return ObjectID(-1, -1);
}

bool Context::inObject2DHitbox(uInt index, dVector2 position)
{
    return objects2d[objects[index].index]->inHitbox(position);
}

bool Context::inTextHitbox(uInt index, dVector2 position)
{
    return texts[objects[index].index]->inHitbox(position);
}

uInt Context::createObject2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    objects2d.push_back(new Object2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath));
    objects.push_back({int(objects2d.size() - 1), ObjectType::OBJECT2D});
    return objects.size() - 1;
}

Object2D *Context::getObject2D(uInt index)
{
    return objects2d[objects[index].index];
}

void Context::destroyObject2D(uInt index)
{
    if (index < objects.size())
    {
        if (objects[index].type == ObjectType::OBJECT2D)
        {
            delete objects2d[objects[index].index];
            objects2d.erase(objects2d.begin() + objects[index].index);
            objects.erase(objects.begin() + index);
            return;
        }
        else
            Log::log("Wrong object type");
    }
    Log::log("Object index out of range");
}

void Context::clearObjects2D()
{
    Log::log("Clearing objects 2D");

    for (Object2D *object2d : objects2d)
    {
        delete object2d;
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].type == ObjectType::OBJECT2D)
        {
            objects.erase(objects.begin() + i);
            i--;
        }
    }

    objects2d.clear();

    Log::log("Objects 2D cleared");
}

uInt Context::createText(std::string text, dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath)
{
    texts.push_back(new Text(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath));
    objects.push_back({int(texts.size() - 1), ObjectType::TEXT});
    return objects.size() - 1;
}

Text *Context::getText(uInt index)
{
    return texts[objects[index].index];
}

void Context::destroyText(uInt index)
{
    if (index < objects.size())
    {
        if (objects[index].type == ObjectType::TEXT)
        {
            delete texts[objects[index].index];
            texts.erase(texts.begin() + objects[index].index);
            objects.erase(objects.begin() + index);
            return;
        }
        else
            Log::log("Wrong object type");
    }
    Log::log("Object index out of range");
}

void Context::clearTexts()
{
    Log::log("Clearing texts");

    for (Text *text : texts)
    {
        delete text;
    }

    for (int i = 0; i < objects.size(); i++)
    {
        if (objects[i].type == ObjectType::TEXT)
        {
            objects.erase(objects.begin() + i);
            i--;
        }
    }

    texts.clear();

    Log::log("Texts cleared");
}

void Context::setLabel(std::string label)
{
    this->label = label;
}

std::string Context::getLabel()
{
    return label;
}