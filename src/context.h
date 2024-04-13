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
class Context
{
private:
    std::string label;
    std::vector<ObjectID> objects;
    std::vector<Object2D *> objects2d;
    std::vector<Text *> texts;

public:
    Context();
    ~Context();

    void draw();

    ObjectID getObjectID(uInt index);
    ObjectID getObjectID(std::string label);

    bool inObject2DHitbox(uInt index, dVector2 position);
    bool inTextHitbox(uInt index, dVector2 position);

    uInt createObject2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    Object2D *getObject2D(uInt index);
    void destroyObject2D(uInt index);
    void clearObjects2D();

    uInt createText(std::string text, dVector2 position, dVector2 scale, double rotation, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath);
    Text *getText(uInt index);
    void destroyText(uInt index);
    void clearTexts();

    void setLabel(std::string label);
    std::string getLabel();
};

#endif // CONTEXT_H