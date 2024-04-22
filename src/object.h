#ifndef OBJECT_H
#define OBJECT_H

#include "include.h"
#include "vector.h"
#include "matrix.h"
#include "utility.h"
#include "log.h"

class Object
{
protected:
    uInt id;
    uInt parentID;
    std::vector<uInt> childrenIDs = std::vector<uInt>();

public:
    Object();
    ~Object();

    void addChild(uInt childID);
    void removeChild(uInt childID);
    std::vector<uInt> getChildren();
    void clearChildren();
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
    Object2D(uInt id, const dVector2 &position, const dVector2 &scale, double rotation, const std::vector<double> &vertices, const iVector2 &windowSize, const std::string &texturePath, const std::string &vertexPath, const std::string &fragmentPath);
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

    void setPosition(const dVector2 &position);
    void setScale(const dVector2 &scale);
    void setRotation(double rotation);

    dVector2 getPosition();
    dVector2 getScale();
    double getRotation();
};

class Text : public Object2D
{
private:
    std::string text;
    std::string fontPath;

public:
    Text(uInt id, const std::string &text, const dVector2 &position, const dVector2 &scale, double rotation, const iVector2 &windowSize, const std::string &fontPath, const std::string &vertexPath, const std::string &fragmentPath);
    ~Text();

    void genText(const std::string &text);

    void setText(const std::string &text);
    std::string getText();

    void setFont(const std::string &fontPath);
    std::string getFont();
};

#endif // OBJECT_H