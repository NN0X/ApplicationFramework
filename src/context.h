#ifndef CONTEXT_H
#define CONTEXT_H

#include "include.h"
#include "defines.h"
#include "vector.h"
#include "object.h"
#include "log.h"

struct ObjectPtr
{
    int type;

    union
    {
        Object2D *object2d;
        Text *text;
    };
};

class Context
{
private:
    uInt id;
    std::string label;
    std::unordered_map<std::string, uInt> objectLabels;
    std::unordered_map<uInt, ObjectPtr> objects;

public:
    Context();
    ~Context();

    void draw();

    ObjectPtr getObject(uInt id);
    ObjectPtr getObject(const std::string &label);

    bool inObjectHitbox(uInt id, const dVector2 &position);
    bool inObjectHitbox(const std::string &label, const dVector2 &position);

    uInt createObject2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    uInt createText(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    void setObjectLabel(uInt id, const std::string &label);
    void destroyObject(uInt id);
    void clearObjects();
    void clearObjects2D();
    void clearTexts();

    void setID(uInt id);
    uInt getID();

    void setLabel(const std::string &label);
    std::string getLabel();
};

#endif // CONTEXT_H