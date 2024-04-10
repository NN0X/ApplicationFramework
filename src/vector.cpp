#include "vector.h"

iVector2::iVector2()
{
    x = 0;
    y = 0;
}

iVector2::iVector2(int x, int y)
{
    this->x = x;
    this->y = y;
}

iVector2 iVector2::operator+(iVector2 vector)
{
    iVector2 result;

    result.x = x + vector.x;
    result.y = y + vector.y;

    return result;
}

iVector2 iVector2::operator-(iVector2 vector)
{
    iVector2 result;

    result.x = x - vector.x;
    result.y = y - vector.y;

    return result;
}

iVector2 iVector2::operator*(iVector2 vector)
{
    iVector2 result;

    result.x = x * vector.x;
    result.y = y * vector.y;

    return result;
}

iVector2 iVector2::operator*(int scalar)
{
    iVector2 result;

    result.x = x * scalar;
    result.y = y * scalar;

    return result;
}

iVector2 iVector2::operator+=(iVector2 vector)
{
    x += vector.x;
    y += vector.y;

    return *this;
}

iVector2 iVector2::operator-=(iVector2 vector)
{
    x -= vector.x;
    y -= vector.y;

    return *this;
}

iVector2 iVector2::operator*=(iVector2 vector)
{
    x *= vector.x;
    y *= vector.y;

    return *this;
}

iVector2 iVector2::operator*=(int scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

iVector2 iVector2::operator=(iVector2 vector)
{
    x = vector.x;
    y = vector.y;

    return *this;
}

bool iVector2::operator==(iVector2 vector)
{
    return x == vector.x && y == vector.y;
}

bool iVector2::operator!=(iVector2 vector)
{
    return x != vector.x || y != vector.y;
}

double iVector2::length()
{
    return sqrt(x * x + y * y);
}

void iVector2::opposite()
{
    x = -x;
    y = -y;
}

void iVector2::clamp(iVector2 min, iVector2 max)
{
    x = std::max(min.x, std::min(max.x, x));
    y = std::max(min.y, std::min(max.y, y));
}

void iVector2::print()
{
    std::cout << "(" << x << ", " << y << ")\n";
}

dVector2::dVector2()
{
    x = 0;
    y = 0;
}

dVector2::dVector2(double x, double y)
{
    this->x = x;
    this->y = y;
}

dVector2 dVector2::operator+(dVector2 vector)
{
    dVector2 result;

    result.x = x + vector.x;
    result.y = y + vector.y;

    return result;
}

dVector2 dVector2::operator-(dVector2 vector)
{
    dVector2 result;

    result.x = x - vector.x;
    result.y = y - vector.y;

    return result;
}

dVector2 dVector2::operator*(dVector2 vector)
{
    dVector2 result;

    result.x = x * vector.x;
    result.y = y * vector.y;

    return result;
}

dVector2 dVector2::operator*(double scalar)
{
    dVector2 result;

    result.x = x * scalar;
    result.y = y * scalar;

    return result;
}

dVector2 dVector2::operator/(dVector2 vector)
{
    dVector2 result;

    result.x = x / vector.x;
    result.y = y / vector.y;

    return result;
}

dVector2 dVector2::operator/(double scalar)
{
    dVector2 result;

    result.x = x / scalar;
    result.y = y / scalar;

    return result;
}

dVector2 dVector2::operator+=(dVector2 vector)
{
    x += vector.x;
    y += vector.y;

    return *this;
}

dVector2 dVector2::operator-=(dVector2 vector)
{
    x -= vector.x;
    y -= vector.y;

    return *this;
}

dVector2 dVector2::operator*=(dVector2 vector)
{
    x *= vector.x;
    y *= vector.y;

    return *this;
}

dVector2 dVector2::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;

    return *this;
}

dVector2 dVector2::operator/=(dVector2 vector)
{
    x /= vector.x;
    y /= vector.y;

    return *this;
}

dVector2 dVector2::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;

    return *this;
}

dVector2 dVector2::operator=(dVector2 vector)
{
    x = vector.x;
    y = vector.y;

    return *this;
}

double dVector2::length()
{
    return sqrt(x * x + y * y);
}

void dVector2::opposite()
{
    x = -x;
    y = -y;
}

void dVector2::normalize()
{
    double length = sqrt(x * x + y * y);

    x /= length;
    y /= length;
}

void dVector2::clamp(dVector2 min, dVector2 max)
{
    x = std::max(min.x, std::min(max.x, x));
    y = std::max(min.y, std::min(max.y, y));
}

void dVector2::convertCoordinateSystem(dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB)
{
    x = (x - originPointA.x) / (originPointB.x - originPointA.x) * (targetPointB.x - targetPointA.x) + targetPointA.x;
    y = (y - originPointA.y) / (originPointB.y - originPointA.y) * (targetPointB.y - targetPointA.y) + targetPointA.y;
}

void dVector2::print()
{
    std::cout << "(" << x << ", " << y << ")\n";
}

dVector3::dVector3()
{
    x = 0;
    y = 0;
    z = 0;
}

dVector3::dVector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

dVector3 dVector3::operator+(dVector3 vector)
{
    dVector3 result;

    result.x = x + vector.x;
    result.y = y + vector.y;
    result.z = z + vector.z;

    return result;
}

dVector3 dVector3::operator-(dVector3 vector)
{
    dVector3 result;

    result.x = x - vector.x;
    result.y = y - vector.y;
    result.z = z - vector.z;

    return result;
}

dVector3 dVector3::operator*(dVector3 vector)
{
    dVector3 result;

    result.x = x * vector.x;
    result.y = y * vector.y;
    result.z = z * vector.z;

    return result;
}

dVector3 dVector3::operator*(double scalar)
{
    dVector3 result;

    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;

    return result;
}

dVector3 dVector3::operator/(dVector3 vector)
{
    dVector3 result;

    result.x = x / vector.x;
    result.y = y / vector.y;
    result.z = z / vector.z;

    return result;
}

dVector3 dVector3::operator/(double scalar)
{
    dVector3 result;

    result.x = x / scalar;
    result.y = y / scalar;
    result.z = z / scalar;

    return result;
}

dVector3 dVector3::operator+=(dVector3 vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;

    return *this;
}

dVector3 dVector3::operator-=(dVector3 vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;

    return *this;
}

dVector3 dVector3::operator*=(dVector3 vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;

    return *this;
}

dVector3 dVector3::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

dVector3 dVector3::operator/=(dVector3 vector)
{
    x /= vector.x;
    y /= vector.y;
    z /= vector.z;

    return *this;
}

dVector3 dVector3::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

dVector3 dVector3::operator=(dVector3 vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;

    return *this;
}

double dVector3::length()
{
    return sqrt(x * x + y * y + z * z);
}

void dVector3::opposite()
{
    x = -x;
    y = -y;
    z = -z;
}

void dVector3::normalize()
{
    double length = sqrt(x * x + y * y + z * z);

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

void dVector3::clamp(dVector3 min, dVector3 max)
{
    x = std::max(min.x, std::min(max.x, x));
    y = std::max(min.y, std::min(max.y, y));
    z = std::max(min.z, std::min(max.z, z));
}

void dVector3::convertCoordinateSystem(dVector3 originPointA, dVector3 originPointB, dVector3 targetPointA, dVector3 targetPointB)
{
    x = (x - originPointA.x) / (originPointB.x - originPointA.x) * (targetPointB.x - targetPointA.x) + targetPointA.x;
    y = (y - originPointA.y) / (originPointB.y - originPointA.y) * (targetPointB.y - targetPointA.y) + targetPointA.y;
    z = (z - originPointA.z) / (originPointB.z - originPointA.z) * (targetPointB.z - targetPointA.z) + targetPointA.z;
}

void dVector3::print()
{
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
}

dVector4::dVector4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

dVector4::dVector4(double x, double y, double z, double w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

dVector4 dVector4::operator+(dVector4 vector)
{
    dVector4 result;

    result.x = x + vector.x;
    result.y = y + vector.y;
    result.z = z + vector.z;
    result.w = w + vector.w;

    return result;
}

dVector4 dVector4::operator-(dVector4 vector)
{
    dVector4 result;

    result.x = x - vector.x;
    result.y = y - vector.y;
    result.z = z - vector.z;
    result.w = w - vector.w;

    return result;
}

dVector4 dVector4::operator*(dVector4 vector)
{
    dVector4 result;

    result.x = x * vector.x;
    result.y = y * vector.y;
    result.z = z * vector.z;
    result.w = w * vector.w;

    return result;
}

dVector4 dVector4::operator*(double scalar)
{
    dVector4 result;

    result.x = x * scalar;
    result.y = y * scalar;
    result.z = z * scalar;
    result.w = w * scalar;

    return result;
}

dVector4 dVector4::operator/(dVector4 vector)
{
    dVector4 result;

    result.x = x / vector.x;
    result.y = y / vector.y;
    result.z = z / vector.z;
    result.w = w / vector.w;

    return result;
}

dVector4 dVector4::operator/(double scalar)
{
    dVector4 result;

    result.x = x / scalar;
    result.y = y / scalar;
    result.z = z / scalar;
    result.w = w / scalar;

    return result;
}

dVector4 dVector4::operator+=(dVector4 vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    w += vector.w;

    return *this;
}

dVector4 dVector4::operator-=(dVector4 vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    w -= vector.w;

    return *this;
}

dVector4 dVector4::operator*=(dVector4 vector)
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    w *= vector.w;

    return *this;
}

dVector4 dVector4::operator*=(double scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

dVector4 dVector4::operator/=(dVector4 vector)
{
    x /= vector.x;
    y /= vector.y;
    z /= vector.z;
    w /= vector.w;

    return *this;
}

dVector4 dVector4::operator/=(double scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;

    return *this;
}

dVector4 dVector4::operator=(dVector4 vector)
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
    w = vector.w;

    return *this;
}

double dVector4::length()
{
    return sqrt(x * x + y * y + z * z + w * w);
}

void dVector4::opposite()
{
    x = -x;
    y = -y;
    z = -z;
    w = -w;
}

void dVector4::normalize()
{
    double length = sqrt(x * x + y * y + z * z + w * w);

    x /= length;
    y /= length;
    z /= length;
    w /= length;
}

void dVector4::clamp(dVector4 min, dVector4 max)
{
    x = std::max(min.x, std::min(max.x, x));
    y = std::max(min.y, std::min(max.y, y));
    z = std::max(min.z, std::min(max.z, z));
    w = std::max(min.w, std::min(max.w, w));
}

void dVector4::convertCoordinateSystem(dVector4 originPointA, dVector4 originPointB, dVector4 targetPointA, dVector4 targetPointB)
{
    x = (x - originPointA.x) / (originPointB.x - originPointA.x) * (targetPointB.x - targetPointA.x) + targetPointA.x;
    y = (y - originPointA.y) / (originPointB.y - originPointA.y) * (targetPointB.y - targetPointA.y) + targetPointA.y;
    z = (z - originPointA.z) / (originPointB.z - originPointA.z) * (targetPointB.z - targetPointA.z) + targetPointA.z;
    w = (w - originPointA.w) / (originPointB.w - originPointA.w) * (targetPointB.w - targetPointA.w) + targetPointA.w;
}

void dVector4::print()
{
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")\n";
}

dVector2 Vector::convert(iVector2 vector)
{
    return dVector2(vector.x, vector.y);
}

dVector2 Vector::normalize(dVector2 vector)
{
    vector.normalize();
    return vector;
}

dVector2 Vector::clamp(dVector2 vector, dVector2 min, dVector2 max)
{
    vector.clamp(min, max);
    return vector;
}

dVector2 Vector::convertCoordinateSystem(dVector2 vector, dVector2 originPointA, dVector2 originPointB, dVector2 targetPointA, dVector2 targetPointB)
{
    vector.convertCoordinateSystem(originPointA, originPointB, targetPointA, targetPointB);
    return vector;
}

dVector3 Vector::normalize(dVector3 vector)
{
    vector.normalize();
    return vector;
}

dVector3 Vector::crossProduct(dVector3 vectorA, dVector3 vectorB)
{
    vectorA.crossProduct(vectorB);
    return vectorA;
}

double Vector::dotProduct(dVector3 vectorA, dVector3 vectorB)
{
    return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}