#include "context.h"

Context::Context()
{
    label = "";
    objects2d = std::vector<Object2D *>();
    texts = std::vector<Text *>();
    // log
}

Context::~Context()
{
    objects2d.clear();
    texts.clear();
    // log
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

uInt Context::createObject2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath)
{
    objects2d.push_back(new Object2D(position, scale, rotation, vertices, windowSize, texturePath, vertexPath, fragmentPath));
    return objects2d.size() - 1;
}

Object2D *Context::getObject2D(uInt index)
{
    if (index < objects2d.size())
    {
        return objects2d[index];
    }
    // log error
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
    // log error
    return nullptr;
}

void Context::destroyObject2D(uInt index)
{
    if (index < objects2d.size())
    {
        delete objects2d[index];
        objects2d.erase(objects2d.begin() + index);
        return;
    }
    // log error
}

void Context::destroyObject2D(std::string label) // temporary solution
{
    for (int i = 0; i < objects2d.size(); i++)
    {
        if (objects2d[i]->getLabel() == label)
        {
            delete objects2d[i];
            objects2d.erase(objects2d.begin() + i);
            return;
        }
    }
    // log error
}

void Context::clearObjects2D()
{
    for (Object2D *object2d : objects2d)
    {
        delete object2d;
    }
    objects2d.clear();
}

uInt Context::createText(std::string text, dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath)
{
    texts.push_back(new Text(text, position, scale, rotation, windowSize, fontPath, vertexPath, fragmentPath));
    return texts.size() - 1;
}

Text *Context::getText(uInt index)
{
    if (index < texts.size())
    {
        return texts[index];
    }
    // log error
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
    // log error
    return nullptr;
}

void Context::destroyText(uInt index)
{
    if (index < texts.size())
    {
        delete texts[index];
        texts.erase(texts.begin() + index);
        return;
    }
    // log error
}

void Context::destroyText(std::string label) // temporary solution
{
    for (int i = 0; i < texts.size(); i++)
    {
        if (texts[i]->getLabel() == label)
        {
            delete texts[i];
            texts.erase(texts.begin() + i);
            return;
        }
    }
    // log error
}

void Context::clearTexts()
{
    for (Text *text : texts)
    {
        delete text;
    }
    texts.clear();
}

void Context::setLabel(std::string label)
{
    this->label = label;
}

std::string Context::getLabel()
{
    return label;
}