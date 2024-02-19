#include "context.h"

Context::Context()
{
}

Context::~Context()
{
    instances.clear();
    objects2d.clear();
}

void Context::createParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case OBJECT2D:
        objects2d[instances[child].second].setParent(parent);
        break;
    }

    switch (instances[parent].first)
    {
    case OBJECT2D:
        objects2d[instances[parent].second].addChild(child);
        break;
    }
}

void Context::destroyParentage(int parent, int child)
{
    switch (instances[child].first)
    {
    case OBJECT2D:
        objects2d[instances[child].second].setParent(-1);
        break;
    }

    switch (instances[parent].first)
    {
    case OBJECT2D:
        objects2d[instances[parent].second].removeChild(child);
        break;
    }
}

int Context::addObject2D(const Object2D &object)
{
    objects2d.push_back(object);
    instances.push_back({OBJECT2D, int(objects2d.size()) - 1});
    objects2d[objects2d.size() - 1].setIndex(instances.size() - 1);

    return instances.size() - 1;
}

Object2D *Context::getObject2D(int index)
{
    return &objects2d[instances[index].second];
}

Object2D *Context::getObject2D(std::string label)
{
    for (auto instance : instances)
    {
        if (instance.first == OBJECT2D && objects2d[instance.second].getLabel() == label)
        {
            return &objects2d[instance.second];
        }
    }

    return nullptr;
}

int Context::addFont(const Font &font)
{
    fonts.push_back(font);
    instances.push_back({FONT, int(fonts.size()) - 1});
    fonts[fonts.size() - 1].setIndex(instances.size() - 1);

    return instances.size() - 1;
}

Font *Context::getFont(int index)
{
    return &fonts[instances[index].second];
}

Font *Context::getFont(std::string label)
{
    for (auto instance : instances)
    {
        if (instance.first == FONT && fonts[instance.second].getLabel() == label)
        {
            return &fonts[instance.second];
        }
    }

    return nullptr;
}

void Context::destroyInstance(int index)
{
    switch (instances[index].first)
    {
    case OBJECT2D:
        objects2d.erase(objects2d.begin() + instances[index].second);
        for (int i = 0; i < instances.size(); i++)
        {
            if (instances[i].first == OBJECT2D && instances[i].second > instances[index].second)
            {
                instances[i].second--;
            }
        }
        break;
    case FONT:
        fonts.erase(fonts.begin() + instances[index].second);
        for (int i = 0; i < instances.size(); i++)
        {
            if (instances[i].first == FONT && instances[i].second > instances[index].second)
            {
                instances[i].second--;
            }
        }
        break;
    }

    instances[index] = {-1, -1};
}

void Context::clearInstances()
{
    instances.clear();
    objects2d.clear();
    fonts.clear();
}

std::vector<std::pair<int, int>> Context::getInstances()
{
    return instances;
}

void Context::draw()
{
    for (auto instance : instances)
    {
        switch (instance.first)
        {
        case OBJECT2D:
            objects2d[instance.second].draw();
            break;
        case FONT:
            fonts[instance.second].draw();
            break;
        }
    }
}
