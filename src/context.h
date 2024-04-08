#ifndef CONTEXT_H
#define CONTEXT_H

#include "include.h"
#include "defines.h"
#include "vector.h"
#include "object.h"

class Context
{
private:
    std::string label;
    std::vector<Object2D> objects2d;
    std::vector<Text> texts;

public:
    Context();
    ~Context();

    void draw();

    uInt createObject2D(); // WiP
    Object2D *getObject2D(uInt index);
    Object2D *getObject2D(std::string label);
    void destroyObject2D(uInt index);
    void destroyObject2D(std::string label);
    void clearObjects2D();

    uInt createText(); // WiP
    Text *getText(uInt index);
    Text *getText(std::string label);
    void destroyText(uInt index);
    void destroyText(std::string label);
    void clearTexts();

    void setLabel(std::string label);
    std::string getLabel();
};

#endif // CONTEXT_H