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
private:
    dVector2 position;
    dVector2 center;
    dVector2 scale;
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
    Object2D(std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    Object2D(dVector2 position, dVector2 scale, double rotation, std::vector<double> &vertices, iVector2 windowSize, std::string texturePath, std::string vertexPath, std::string fragmentPath);

    void transformPosition(dVector2 position);
    void transformScale(dVector2 scale);
    void transformRotation(double rotation);

    void draw();

    void genVertices(std::vector<double> &vertices);
    void genTexture(std::string texturePath);
    void genShader(std::string vertexPath, std::string fragmentPath);
    void genAttributes();

    void setPosition(dVector2 position);
    void setScale(dVector2 scale);
    void setRotation(double rotation);
};

class Object3D : public Object
{
private:
    dVector3 position;
    dVector3 center;
    dVector3 scale;
    dVector3 rotation;
    fMatrix4 translationM;
    fMatrix4 rotationM;
    fMatrix4 scaleM;
    GLuint vertices;
    GLuint attributes;
    GLuint texture;
    GLuint shader;
    int sizeOfVertices;
    int sizeOfIndices;

public:
    Object3D(std::vector<double> &vertices, std::string texturePath, std::string vertexPath, std::string fragmentPath);
    Object3D(dVector3 position, dVector3 scale, dVector3 rotation, std::vector<double> &vertices, std::string texturePath, std::string vertexPath, std::string fragmentPath);

    void transformPosition(dVector3 position);
    void transformScale(dVector3 scale);
    void transformRotation(dVector3 rotation);

    void draw(fMatrix4 cameraM);

    void genVertices(std::vector<double> &vertices);
    void genTexture(std::string texturePath);
    void genShader(std::string vertexPath, std::string fragmentPath);
    void genAttributes();

    void setPosition(dVector3 position);
    void setScale(dVector3 scale);
    void setRotation(dVector3 rotation);

    dVector3 getScale();
};

class Camera : public Object
{
private:
    dVector3 position;
    dVector3 rotation;
    fMatrix4 projectionM;
    fMatrix4 viewM;

public:
    Camera(dVector3 position, dVector3 rotation, double fov, double aspectRatio, double near, double far);

    void transformPosition(dVector3 position);
    void transformRotation(dVector3 rotation);

    fMatrix4 getCameraMatrix();
};