#include "context.h"

Context::Context()
{
    label = "";
    objects2d = std::vector<Object2D>();
    texts = std::vector<Text>();
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
        objects2d[i].draw();
    }
    for (uInt i = 0; i < texts.size(); i++)
    {
        texts[i].draw();
    }
}

uInt Context::createObject2D() // WiP
{
    return 0;
}

Object2D *Context::getObject2D(uInt index)
{
    if (index < objects2d.size())
    {
        return &objects2d[index];
    }
    // log error
    return nullptr;
}

Object2D *Context::getObject2D(std::string label) // temporary solution
{
    for (Object2D &object2d : objects2d)
    {
        if (object2d.getLabel() == label)
        {
            return &object2d;
        }
    }
    // log error
    return nullptr;
}

void Context::destroyObject2D(uInt index)
{
    if (index < objects2d.size())
    {
        objects2d.erase(objects2d.begin() + index);
        return;
    }
    // log error
}

void Context::destroyObject2D(std::string label) // temporary solution
{
    for (uInt i = 0; i < objects2d.size(); i++)
    {
        if (objects2d[i].getLabel() == label)
        {
            objects2d.erase(objects2d.begin() + i);
            return;
        }
    }
    // log error
}

void Context::clearObjects2D()
{
    objects2d.clear();
}

uInt Context::createText() // WiP
{
    return 0;
}

Text *Context::getText(uInt index)
{
    if (index < texts.size())
    {
        return &texts[index];
    }
    // log error
    return nullptr;
}

Text *Context::getText(std::string label) // temporary solution
{
    for (Text &text : texts)
    {
        if (text.getLabel() == label)
        {
            return &text;
        }
    }
    // log error
    return nullptr;
}

void Context::destroyText(uInt index)
{
    if (index < texts.size())
    {
        texts.erase(texts.begin() + index);
        return;
    }
    // log error
}

void Context::destroyText(std::string label) // temporary solution
{
    for (uInt i = 0; i < texts.size(); i++)
    {
        if (texts[i].getLabel() == label)
        {
            texts.erase(texts.begin() + i);
            return;
        }
    }
    // log error
}

void Context::clearTexts()
{
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