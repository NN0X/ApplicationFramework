#ifndef OBJECT_H
#define OBJECT_H

#include "include.h"
#include "vector.h"
#include "matrix.h"
#include "utility.h"
#include "log.h"

enum ObjectType
{
    OBJECT = -1,
    OBJECT2D = 0,
    TEXT
};

class Object
{
protected:
    uInt id;
    std::string label;

public:
    Object();
    ~Object();

    void setID(uInt id);
    uInt getID();

    void setLabel(const std::string &label);
    std::string getLabel();
};

class Object2D : public Object
{
protected:
    dVector2 position = dVector2();
    dVector2 scale = dVector2();
    std::vector<dVector2> hitbox = std::vector<dVector2>();
    double rotation;
    fMatrix4 translationMatrix = fMatrix4();
    fMatrix4 rotationMatrix = fMatrix4();
    fMatrix4 scaleMatrix = fMatrix4();
    fMatrix4 projectionMatrix = fMatrix4();
    GLuint vertices;
    GLuint attributes;
    GLuint texture;
    GLuint shader;
    uInt sizeOfVertices;
    uInt sizeOfIndices;

public:
    Object2D();
    Object2D(const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
    ~Object2D();

    void draw();

    void transformPosition(const dVector2 &transform);
    void transformScale(const dVector2 &transform);
    void transformRotation(double transform);

    void genVertices(const std::vector<double> &vertices);
    void genHitbox(const std::vector<double> &vertices);
    void genTexture(const std::string &texturePath);
    void genShader(const std::string &vertexPath, const std::string &fragmentPath);
    void genAttributes();

    bool inHitbox(const dVector2 &point);

    void setPositionWorld(const dVector2 &position);
    void setScaleWorld(const dVector2 &scale);

    void setPositionWindow(dVector2 position, const iVector2 &windowSize);
    void setScaleWindow(dVector2 scale, const iVector2 &windowSize);

    void setRotation(double rotation);

    std::vector<dVector2> getHitbox();

    dVector2 getPositionWorld();
    dVector2 getScaleWorld();

    dVector2 getPositionWindow(const iVector2 &windowSize);
    dVector2 getScaleWindow(const iVector2 &windowSize);

    double getRotation();
};

class Text : public Object2D
{
private:
    std::string text;
    std::string fontPath;

public:
    Text(const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    ~Text();

    void genText(const std::string &text);

    void setText(const std::string &text);
    std::string getText();

    void setFont(const std::string &fontPath);
    std::string getFont();
};

#endif // OBJECT_H