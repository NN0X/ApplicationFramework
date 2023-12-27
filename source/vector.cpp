#include "vector.h"

// Vector

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

void dVector2::print()
{
    std::cout << x << " " << y << "\n";
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
    std::cout << x << " " << y << " " << z << "\n";
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