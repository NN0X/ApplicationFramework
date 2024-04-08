#ifndef OBJECT_H
#define OBJECT_H

#include "include.h"
#include "vector.h"
#include "matrix.h"
#include "utility.h"

class Object
{
protected:
    uInt index;
    std::string label;

public:
    Object();
    ~Object();

    void setIndex(uInt index);
    uInt getIndex();

    void setLabel(std::string label);
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
    Object2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    ~Object2D();

    void draw();

    void transformPosition(dVector2 transform);
    void transformScale(dVector2 transform);
    void transformRotation(double transform);

    void genVertices(std::vector<double> &vertices);
    void genHitbox(std::vector<double> &vertices);
    void genTexture(std::string texturePath);
    void genShader(std::string vertexPath, std::string fragmentPath);
    void genAttributes();

    bool inHitbox(dVector2 point);

    void setPositionWorld(dVector2 position);
    void setScaleWorld(dVector2 scale);

    void setPositionWindow(dVector2 position, iVector2 windowSize);
    void setScaleWindow(dVector2 scale, iVector2 windowSize);

    void setRotation(double rotation);

    std::vector<dVector2> getHitbox();

    dVector2 getPositionWorld();
    dVector2 getScaleWorld();

    dVector2 getPositionWindow(iVector2 windowSize);
    dVector2 getScaleWindow(iVector2 windowSize);

    double getRotation();
};

class Text : public Object2D
{
private:
    std::string text;
    std::string fontPath;
    std::set<std::string> map = std::set<std::string>(); // rethink

public:
    Text(std::string text, dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string fontPath, std::string vertexPath, std::string fragmentPath);
    ~Text();

    void genText(std::string text);

    void setText(std::string text);
    std::string getText();

    void setFont(std::string fontPath);
    std::string getFont();
};

#endif // OBJECT_H