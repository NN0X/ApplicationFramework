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

bool Context::inObjectHitbox(uInt index, dVector2 position)
{
    if (index < objects.size())
    {
        if (objects[index].type == ObjectType::OBJECT2D)
        {
            return objects2d[objects[index].index]->inHitbox(position);
        }
        else if (objects[index].type == ObjectType::TEXT)
        {
            return texts[objects[index].index]->inHitbox(position);
        }
        else
            Log::log("Unknown object type");
    }
    Log::log("Object index out of range");
    return false;
}

bool Context::inObjectHitbox(std::string label, dVector2 position) // temporary solution
{
    for (ObjectID object : objects)
    {
        if (object.type == ObjectType::OBJECT2D && objects2d[object.index]->getLabel() == label)
        {
            return objects2d[object.index]->inHitbox(position);
        }
        else if (object.type == ObjectType::TEXT && texts[object.index]->getLabel() == label)
        {
            return texts[object.index]->inHitbox(position);
        }
    }
    Log::log("Object label not found");
    return false;
}

uInt Context::createObject2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    objects2d.push_back(new Object2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath));
    objects.push_back({int(objects2d.size() - 1), ObjectType::OBJECT2D});
    return objects.size() - 1;
}

Object2D *Context::getObject2D(uInt index)
{
    if (index < objects.size())
    {
        if (objects[index].type == ObjectType::OBJECT2D)
            return objects2d[objects[index].index];
        else
            Log::log("Wrong object type");
    }
    Log::log("Object index out of range");
    return nullptr;
}

Object2D *Context::getObject2D(std::string label) // temporary solution
{
    for (Object2D *object2d : objects2d)
    {
        if (object2d->getLabel() == label)
        {
            return object2d;
        }
    }
    Log::log("Object label not found");
    return nullptr;
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

void Context::destroyObject2D(std::string label) // temporary solution
{
    for (int i = 0; i < objects2d.size(); i++)
    {
        if (objects2d[i]->getLabel() == label)
        {
            delete objects2d[i];
            objects2d.erase(objects2d.begin() + i);
            for (int j = 0; j < objects.size(); j++)
            {
                if (objects[j].type == ObjectType::OBJECT2D && objects[j].index == i)
                {
                    objects.erase(objects.begin() + j);
                    return;
                }
            }
        }
    }
    Log::log("Object label not found");
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
    if (index < objects.size())
    {
        if (objects[index].type == ObjectType::TEXT)
            return texts[objects[index].index];
        else
            Log::log("Wrong object type");
    }
    Log::log("Object index out of range");
    return nullptr;
}

Text *Context::getText(std::string label) // temporary solution
{
    for (Text *text : texts)
    {
        if (text->getLabel() == label)
        {
            return text;
        }
    }
    Log::log("Object label not found");
    return nullptr;
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

void Context::destroyText(std::string label) // temporary solution
{
    for (int i = 0; i < texts.size(); i++)
    {
        if (texts[i]->getLabel() == label)
        {
            delete texts[i];
            texts.erase(texts.begin() + i);
            for (int j = 0; j < objects.size(); j++)
            {
                if (objects[j].type == ObjectType::TEXT && objects[j].index == i)
                {
                    objects.erase(objects.begin() + j);
                    return;
                }
            }
        }
    }
    Log::log("Object label not found");
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