// CHANGE TO TEMPLATES

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include "vector.h"

struct fMatrix4
{
    float m[4][4] = {0};

    fMatrix4();
    fMatrix4(std::vector<std::vector<double>> matrix);

    void empty();
    void identity();
    void orthographic(double left, double right, double bottom, double top, double near, double far);
    void transpose();
    void translate(dVector3 vector);
    void add(fMatrix4 matrix);
    void multiply(fMatrix4 matrix);
    void scale(dVector3 vector);
    void rotate(double xAngle, double yAngle, double zAngle);
    void print();
};

namespace Matrix
{
    fMatrix4 transpose(fMatrix4 matrix);
    fMatrix4 translate(fMatrix4 matrix, dVector3 vector);
    fMatrix4 add(fMatrix4 matrix1, fMatrix4 matrix2);
    fMatrix4 multiply(fMatrix4 matrix1, fMatrix4 matrix2);
    fMatrix4 scale(fMatrix4 matrix, dVector3 vector);
    fMatrix4 rotate(fMatrix4 matrix, double xAngle, double yAngle, double zAngle);
}