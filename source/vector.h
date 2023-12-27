// CHANGE TO TEMPLATES

#pragma once

#include <iostream>
#include <math.h>

struct iVector2
{
    int x, y;
};

struct dVector2
{
    double x, y;

    void opposite();
    void normalize();
    void clamp(dVector2 min, dVector2 max);
    void convertCoordinateSystem(dVector2 originMin, dVector2 originMax, dVector2 targetMin, dVector2 targetMax);
    void print();
};

struct dVector3
{
    double x, y, z;

    void opposite();
    void normalize();
    void crossProduct(dVector3 vector);
    void print();
};

struct dVector4
{
    double x, y, z, w;

    void normalize();
    void print();
};

namespace Vector
{
    dVector2 add(dVector2 vector1, dVector2 vector2);
    dVector2 subtract(dVector2 vector1, dVector2 vector2);
    dVector2 multiply(dVector2 vector1, dVector2 vector2);
    dVector2 normalize(dVector2 vector);
    dVector2 clamp(dVector2 vector, dVector2 min, dVector2 max);
    dVector2 convertCoordinateSystem(dVector2 vector, dVector2 originMin, dVector2 originMax, dVector2 targetMin, dVector2 targetMax);

    dVector3 add(dVector3 vector1, dVector3 vector2);
    dVector3 subtract(dVector3 vector1, dVector3 vector2);
    dVector3 normalize(dVector3 vector);
    dVector3 crossProduct(dVector3 vector1, dVector3 vector2);

    double dotProduct(dVector3 vector1, dVector3 vector2);

    dVector4 add(dVector4 vector1, dVector4 vector2);
    dVector4 multiply(dVector4 vector1, dVector4 vector2);
}