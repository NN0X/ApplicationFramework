#include "vector.h"

// Vector

dVector2 Vector::convert(iVector2 vector)
{
    dVector2 result;

    result.x = vector.x;
    result.y = vector.y;

    return result;
}

dVector2 Vector::add(dVector2 vector1, dVector2 vector2)
{
    dVector2 result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;

    return result;
}

dVector2 Vector::subtract(dVector2 vector1, dVector2 vector2)
{
    dVector2 result;

    result.x = vector1.x - vector2.x;
    result.y = vector1.y - vector2.y;

    return result;
}

dVector2 Vector::multiply(dVector2 vector1, dVector2 vector2)
{
    dVector2 result;

    result.x = vector1.x * vector2.x;
    result.y = vector1.y * vector2.y;

    return result;
}

dVector2 Vector::normalize(dVector2 vector)
{
    dVector2 result;

    double length = sqrt(pow(vector.x, 2) + pow(vector.y, 2));
    result.x = vector.x / length;
    result.y = vector.y / length;

    return result;
}

dVector2 Vector::clamp(dVector2 vector, dVector2 min, dVector2 max)
{
    if (vector.x < min.x)
        vector.x = min.x;

    if (vector.x > max.x)
        vector.x = max.x;

    if (vector.y < min.y)
        vector.y = min.y;

    if (vector.y > max.y)
        vector.y = max.y;

    return vector;
}

dVector2 Vector::convertCoordinateSystem(dVector2 vector, dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB)
{
    vector.x = (vector.x - originPointA.x) / (originPointB.x - originPointA.x) * (targetPointB.x - targetPointA.x) + targetPointA.x;
    vector.y = (vector.y - originPointA.y) / (originPointB.y - originPointA.y) * (targetPointB.y - targetPointA.y) + targetPointA.y;

    return vector;
}

dVector3 Vector::add(dVector3 vector1, dVector3 vector2)
{
    dVector3 result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;

    return result;
}

dVector3 Vector::subtract(dVector3 vector1, dVector3 vector2)
{
    dVector3 result;

    result.x = vector1.x - vector2.x;
    result.y = vector1.y - vector2.y;
    result.z = vector1.z - vector2.z;

    return result;
}

dVector3 Vector::normalize(dVector3 vector)
{
    dVector3 result;

    double length = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
    result.x = vector.x / length;
    result.y = vector.y / length;
    result.z = vector.z / length;

    return result;
}

dVector3 Vector::crossProduct(dVector3 vector1, dVector3 vector2)
{
    dVector3 result;

    result.x = vector1.y * vector2.z - vector1.z * vector2.y;
    result.y = vector1.z * vector2.x - vector1.x * vector2.z;
    result.z = vector1.x * vector2.y - vector1.y * vector2.x;

    return result;
}

double Vector::dotProduct(dVector3 vector1, dVector3 vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

dVector4 Vector::add(dVector4 vector1, dVector4 vector2)
{
    dVector4 result;

    result.x = vector1.x + vector2.x;
    result.y = vector1.y + vector2.y;
    result.z = vector1.z + vector2.z;
    result.w = vector1.w + vector2.w;

    return result;
}

dVector4 Vector::multiply(dVector4 vector1, dVector4 vector2)
{
    dVector4 result;

    result.x = vector1.x * vector2.x;
    result.y = vector1.y * vector2.y;
    result.z = vector1.z * vector2.z;
    result.w = vector1.w * vector2.w;

    return result;
}

//----------------------------------------------------------------------------------------------
// iVector2

void iVector2::print()
{
    std::cout << "x=" << x << " y=" << y << "\n";
}

// dVector2

void dVector2::opposite()
{
    x = -x;
    y = -y;
}

void dVector2::normalize()
{
    double length = sqrt(pow(x, 2) + pow(y, 2));
    x /= length;
    y /= length;
}

void dVector2::clamp(dVector2 min, dVector2 max)
{
    if (x < min.x)
        x = min.x;

    if (x > max.x)
        x = max.x;

    if (y < min.y)
        y = min.y;

    if (y > max.y)
        y = max.y;
}

void dVector2::convertCoordinateSystem(dVector2 originMin, dVector2 originMax, dVector2 targetMin, dVector2 targetMax)
{
    x = (x - originMin.x) / (originMax.x - originMin.x) * (targetMax.x - targetMin.x) + targetMin.x;
    y = (y - originMin.y) / (originMax.y - originMin.y) * (targetMax.y - targetMin.y) + targetMin.y;
}

void dVector2::print()
{
    std::cout << "x=" << x << " y=" << y << "\n";
}

//----------------------------------------------------------------------------------------------
// dVector3

void dVector3::opposite()
{
    x = -x;
    y = -y;
    z = -z;
}

void dVector3::normalize()
{
    double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    x /= length;
    y /= length;
    z /= length;
}

void dVector3::crossProduct(dVector3 vector)
{
    dVector3 result;

    result.x = y * vector.z - z * vector.y;
    result.y = z * vector.x - x * vector.z;
    result.z = x * vector.y - y * vector.x;

    *this = result;
}

void dVector3::print()
{
    std::cout << "x=" << x << " y=" << y << " z=" << z << "\n";
}

//----------------------------------------------------------------------------------------------
// dVector4

void dVector4::normalize()
{
    double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));
    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

void dVector4::print()
{
    std::cout << x << " " << y << " " << z << " " << w << "\n";
}

//----------------------------------------------------------------------------------------------