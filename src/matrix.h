#ifndef MATRIX_H
#define MATRIX_H

#include "include.h"
#include "defines.h"
#include "vector.h"

struct fMatrix4
{
    float matrix[4][4]; // [column][row] column-major

    fMatrix4();
    fMatrix4(std::vector<std::vector<double>> matrix);

    fMatrix4 operator+(fMatrix4 matrix);
    fMatrix4 operator-(fMatrix4 matrix);
    fMatrix4 operator*(fMatrix4 matrix);

    fMatrix4 operator+=(fMatrix4 matrix);
    fMatrix4 operator-=(fMatrix4 matrix);
    fMatrix4 operator*=(fMatrix4 matrix);

    fMatrix4 operator=(fMatrix4 matrix);

    void empty();
    void identity();
    void transpose();
    void translate(dVector3 vector);
    void scale(dVector3 vector);
    void rotate(double xAngle, double yAngle, double zAngle);
    void orthographic(double left, double right, double bottom, double top, double near, double far);
    void print();
};

namespace Matrix
{
    fMatrix4 transpose(fMatrix4 matrix);
    fMatrix4 translate(fMatrix4 matrix, dVector3 vector);
    fMatrix4 scale(fMatrix4 matrix, dVector3 vector);
    fMatrix4 rotate(fMatrix4 matrix, double xAngle, double yAngle, double zAngle);

    dVector4 multiply(fMatrix4 matrix, dVector4 vector);
}

#endif // MATRIX_H