#ifndef VECTOR_H
#define VECTOR_H

#include "include.h"

struct iVector2
{
    int x, y;

    iVector2();
    iVector2(int x, int y);

    iVector2 operator+(iVector2 vector);
    iVector2 operator-(iVector2 vector);
    iVector2 operator*(iVector2 vector);
    iVector2 operator*(int scalar);

    iVector2 operator+=(iVector2 vector);
    iVector2 operator-=(iVector2 vector);
    iVector2 operator*=(iVector2 vector);
    iVector2 operator*=(int scalar);

    iVector2 operator=(iVector2 vector);

    bool operator==(iVector2 vector);
    bool operator!=(iVector2 vector);

    double length();

    void opposite();
    void clamp(iVector2 min, iVector2 max);

    void print();
};

struct dVector2
{
    double x, y;

    dVector2();
    dVector2(double x, double y);

    dVector2 operator+(dVector2 vector);
    dVector2 operator-(dVector2 vector);
    dVector2 operator*(dVector2 vector);
    dVector2 operator*(double scalar);
    dVector2 operator/(dVector2 vector);
    dVector2 operator/(double scalar);

    dVector2 operator+=(dVector2 vector);
    dVector2 operator-=(dVector2 vector);
    dVector2 operator*=(dVector2 vector);
    dVector2 operator*=(double scalar);
    dVector2 operator/=(dVector2 vector);
    dVector2 operator/=(double scalar);

    dVector2 operator=(dVector2 vector);

    double length();

    void opposite();
    void normalize();
    void clamp(dVector2 min, dVector2 max);
    void convertCoordinateSystem(dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB);

    void print();
};

struct dVector3
{
    double x, y, z;

    dVector3();
    dVector3(double x, double y, double z);

    dVector3 operator+(dVector3 vector);
    dVector3 operator-(dVector3 vector);
    dVector3 operator*(dVector3 vector);
    dVector3 operator*(double scalar);
    dVector3 operator/(dVector3 vector);
    dVector3 operator/(double scalar);

    dVector3 operator+=(dVector3 vector);
    dVector3 operator-=(dVector3 vector);
    dVector3 operator*=(dVector3 vector);
    dVector3 operator*=(double scalar);
    dVector3 operator/=(dVector3 vector);
    dVector3 operator/=(double scalar);

    dVector3 operator=(dVector3 vector);

    double length();

    void opposite();
    void normalize();
    void crossProduct(dVector3 vector);
    void clamp(dVector3 min, dVector3 max);
    void convertCoordinateSystem(dVector3 originPointA, dVector3 originPointB, dVector3 targetPointA, dVector3 targetPointB);

    void print();
};

struct dVector4
{
    double x, y, z, w;

    dVector4();
    dVector4(double x, double y, double z, double w);

    dVector4 operator+(dVector4 vector);
    dVector4 operator-(dVector4 vector);
    dVector4 operator*(dVector4 vector);
    dVector4 operator*(double scalar);
    dVector4 operator/(dVector4 vector);
    dVector4 operator/(double scalar);

    dVector4 operator+=(dVector4 vector);
    dVector4 operator-=(dVector4 vector);
    dVector4 operator*=(dVector4 vector);
    dVector4 operator*=(double scalar);
    dVector4 operator/=(dVector4 vector);
    dVector4 operator/=(double scalar);

    dVector4 operator=(dVector4 vector);

    double length();

    void opposite();
    void normalize();
    void clamp(dVector4 min, dVector4 max);
    void convertCoordinateSystem(dVector4 originPointA, dVector4 originPointB, dVector4 targetPointA, dVector4 targetPointB);

    void print();
};

namespace Vector
{
    dVector2 convert(iVector2 vector);

    dVector2 normalize(dVector2 vector);
    dVector2 clamp(dVector2 vector, dVector2 min, dVector2 max);
    dVector2 convertCoordinateSystem(dVector2 vector, dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB);

    dVector3 normalize(dVector3 vector);
    dVector3 crossProduct(dVector3 vectorA, dVector3 vectorB);

    double dotProduct(dVector3 vectorA, dVector3 vectorB);
}

#endif // VECTOR_H