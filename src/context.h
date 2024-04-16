#ifndef CONTEXT_H
#define CONTEXT_H

#include "include.h"
#include "defines.h"
#include "vector.h"
#include "object.h"
#include "log.h"

struct ObjectID
{
    int index;
    int type;

    ObjectID(int index, int type)
    {
        this->index = index;
        this->type = type;
    }
};

union ObjectPtr
{
    Object2D *object2d;
    Text *text;
};
class Context
{
private:
    std::string label;
    std::vector<ObjectID> objects; // temporary solution
    // use below instead of vectors
    // std::unordered_map<std::string, uInt> objectLabels;
    // std::unordered_map<uInt, ObjectPtr> objects; - uInt is the id of the object
    std::vector<Object2D *> objects2d; // temporary solution
    std::vector<Text *> texts;         // temporary solution

public:
    Context();
    ~Context();

    void draw();

    ObjectID getObjectID(uInt index);
    ObjectID getObjectID(const std::string &label);

    bool inObject2DHitbox(uInt index, const dVector2 &position);
    bool inTextHitbox(uInt index, const dVector2 &position);

    uInt createObject2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    Object2D *getObject2D(uInt index);
    void destroyObject2D(uInt index);
    void clearObjects2D();

    uInt createText(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    Text *getText(uInt index);
    void destroyText(uInt index);
    void clearTexts();

    void setLabel(const std::string &label);
    std::string getLabel();
};

#endif // CONTEXT_H