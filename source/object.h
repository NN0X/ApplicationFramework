#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb/stb_image.h>

#include "utility.h"
#include "vector.h"
#include "matrix.h"

class Object
{
protected:
    int index;
    int parent;
    std::vector<int> children;

public:
    void setIndex(int index);
    int getIndex();

    void setParent(int parent);
    int getParent();

    void addChild(int child);
    void removeChild(int child);
};

class Object2D : public Object
{
protected:
    dVector2 position;
    dVector2 scale;
    std::vector<dVector2> hitbox;
    double rotation;
    fMatrix4 translationM;
    fMatrix4 rotationM;
    fMatrix4 scaleM;
    fMatrix4 projectionM;
    GLuint vertices;
    GLuint attributes;
    GLuint texture;
    GLuint shader;
    int sizeOfVertices;
    int sizeOfIndices;

public:
    Object2D();
    Object2D(std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    Object2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);

    void transformPosition(dVector2 position);
    void transformScale(dVector2 scale);
    void transformRotation(double rotation);

    void draw();

    void genVertices(std::vector<double> &vertices);
    void genHitbox(std::vector<double> &vertices);
    void genTexture(std::string texturePath);
    void genShader(std::string vertexPath, std::string fragmentPath);
    void genAttributes();

    bool inHitbox(dVector2 point);

    void setPositionWorld(dVector2 position);
    void setPositionWindow(dVector2 position, iVector2 windowSize);
    void setScaleWorld(dVector2 scale);
    void setScaleWindow(dVector2 scale, iVector2 windowSize);
    void setRotation(double rotation);

    std::vector<dVector2> getHitbox();
    dVector2 getPositionWorld();
    dVector2 getPositionWindow(iVector2 windowSize);
    dVector2 getScale();
    double getRotation();
};

// make a file with vertices corresponding to specific characters
// make a mega texture with all the characters

class Font : public Object2D
{
protected:
    std::string text;
    std::string fontPath;
    std::vector<double> verticesAll;
    std::vector<double> verticesText;

public:
    Font(std::string text, std::string fontPath, iVector2 windowSize, std::string vertexPath, std::string fragmentPath);

    void setText(std::string text);
    void setFont(std::string fontPath);

    std::string getText();
    std::string getFont();
};