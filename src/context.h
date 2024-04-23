#ifndef CONTEXT_H
#define CONTEXT_H

#include "include.h"
#include "defines.h"
#include "vector.h"
#include "object.h"
#include "log.h"

class Context
{
private:
    uInt id;
    std::unordered_map<uInt, ObjectPtr> objects = std::unordered_map<uInt, ObjectPtr>();

public:
    Context(uInt id);
    ~Context();

    void draw();

    bool inObjectHitbox(uInt id, const dVector2 &position);

    uInt createObject2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    uInt createText(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);

    void addChildToObject(uInt parentID, uInt childID);
    void removeChildFromObject(uInt parentID, uInt childID);

    ObjectPtr getObject(uInt id);
    void destroyObject(uInt id);

    void clearObjects();
    void clearObjects2D();
    void clearTexts();
};

#endif // CONTEXT_H