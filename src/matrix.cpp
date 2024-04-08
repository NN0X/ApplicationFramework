#include "matrix.h"

fMatrix4::fMatrix4()
{
    empty();
}

fMatrix4::fMatrix4(std::vector<std::vector<double>> matrix)
{
    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            this->matrix[i][j] = matrix[i][j];
        }
    }
}

fMatrix4 fMatrix4::operator+(fMatrix4 matrix)
{
    fMatrix4 result = *this;

    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            result.matrix[i][j] += matrix.matrix[i][j];
        }
    }

    return result;
}

fMatrix4 fMatrix4::operator-(fMatrix4 matrix)
{
    fMatrix4 result = *this;

    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            result.matrix[i][j] -= matrix.matrix[i][j];
        }
    }

    return result;
}

fMatrix4 fMatrix4::operator*(fMatrix4 matrix) // could be optimized?
{
    fMatrix4 result;
    result.empty();

    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            for (uInt k = 0; k < 4; k++)
            {
                result.matrix[i][j] += this->matrix[i][k] * matrix.matrix[k][j];
            }
        }
    }

    return result;
}

fMatrix4 fMatrix4::operator+=(fMatrix4 matrix)
{
    *this = *this + matrix;
    return *this;
}

fMatrix4 fMatrix4::operator-=(fMatrix4 matrix)
{
    *this = *this - matrix;
    return *this;
}

fMatrix4 fMatrix4::operator*=(fMatrix4 matrix)
{
    *this = *this * matrix;
    return *this;
}

fMatrix4 fMatrix4::operator=(fMatrix4 matrix)
{
    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            this->matrix[i][j] = matrix.matrix[i][j];
        }
    }

    return *this;
}

void fMatrix4::empty()
{
    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            matrix[i][j] = 0;
        }
    }
}

void fMatrix4::identity()
{
    empty();
    matrix[0][0] = 1;
    matrix[1][1] = 1;
    matrix[2][2] = 1;
    matrix[3][3] = 1;
}

void fMatrix4::transpose()
{
    fMatrix4 temp = *this;

    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            matrix[i][j] = temp.matrix[j][i];
        }
    }
}

void fMatrix4::translate(dVector3 vector)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][3] = vector.x;
    temp.matrix[1][3] = vector.y;
    temp.matrix[2][3] = vector.z;

    *this *= temp;
}

void fMatrix4::scale(dVector3 vector)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][0] = vector.x;
    temp.matrix[1][1] = vector.y;
    temp.matrix[2][2] = vector.z;

    *this *= temp;
}

void fMatrix4::rotate(double xAngle, double yAngle, double zAngle)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][0] = cos(yAngle) * cos(zAngle);
    temp.matrix[0][1] = cos(yAngle) * sin(zAngle);
    temp.matrix[0][2] = -sin(yAngle);

    temp.matrix[1][0] = sin(xAngle) * sin(yAngle) * cos(zAngle) - cos(xAngle) * sin(zAngle);
    temp.matrix[1][1] = sin(xAngle) * sin(yAngle) * sin(zAngle) + cos(xAngle) * cos(zAngle);
    temp.matrix[1][2] = sin(xAngle) * cos(yAngle);

    temp.matrix[2][0] = cos(xAngle) * sin(yAngle) * cos(zAngle) + sin(xAngle) * sin(zAngle);
    temp.matrix[2][1] = cos(xAngle) * sin(yAngle) * sin(zAngle) - sin(xAngle) * cos(zAngle);
    temp.matrix[2][2] = cos(xAngle) * cos(yAngle);

    *this *= temp;
}

void fMatrix4::orthographic(double left, double right, double bottom, double top, double near, double far)
{
    fMatrix4 result;
    result.identity();

    std::vector<double> vector = {left, right, bottom, top};
    double max = *max_element(vector.begin(), vector.end());
    left = left * 2 / max - 1;
    right = right * 2 / max - 1;
    bottom = bottom * 2 / max - 1;
    top = top * 2 / max - 1;

    result.matrix[0][0] = 2 / (right - left);
    result.matrix[1][1] = 2 / (top - bottom);
    result.matrix[2][2] = -2 / (far - near);

    result.matrix[0][3] = -(right + left) / (right - left);
    result.matrix[1][3] = -(top + bottom) / (top - bottom);
    result.matrix[2][3] = -(far + near) / (far - near);

    *this = result;
}

void fMatrix4::print()
{
    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

fMatrix4 Matrix::transpose(fMatrix4 matrix)
{
    fMatrix4 temp = matrix;

    for (uInt i = 0; i < 4; i++)
    {
        for (uInt j = 0; j < 4; j++)
        {
            matrix.matrix[i][j] = temp.matrix[j][i];
        }
    }

    return matrix;
}

fMatrix4 Matrix::translate(fMatrix4 matrix, dVector3 vector)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][3] = vector.x;
    temp.matrix[1][3] = vector.y;
    temp.matrix[2][3] = vector.z;

    return matrix *= temp;
}

fMatrix4 Matrix::scale(fMatrix4 matrix, dVector3 vector)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][0] = vector.x;
    temp.matrix[1][1] = vector.y;
    temp.matrix[2][2] = vector.z;

    return matrix *= temp;
}

fMatrix4 Matrix::rotate(fMatrix4 matrix, double xAngle, double yAngle, double zAngle)
{
    fMatrix4 temp;
    temp.identity();

    temp.matrix[0][0] = cos(yAngle) * cos(zAngle);
    temp.matrix[0][1] = cos(yAngle) * sin(zAngle);
    temp.matrix[0][2] = -sin(yAngle);

    temp.matrix[1][0] = sin(xAngle) * sin(yAngle) * cos(zAngle) - cos(xAngle) * sin(zAngle);
    temp.matrix[1][1] = sin(xAngle) * sin(yAngle) * sin(zAngle) + cos(xAngle) * cos(zAngle);
    temp.matrix[1][2] = sin(xAngle) * cos(yAngle);

    temp.matrix[2][0] = cos(xAngle) * sin(yAngle) * cos(zAngle) + sin(xAngle) * sin(zAngle);
    temp.matrix[2][1] = cos(xAngle) * sin(yAngle) * sin(zAngle) - sin(xAngle) * cos(zAngle);
    temp.matrix[2][2] = cos(xAngle) * cos(yAngle);

    return matrix *= temp;
}

dVector4 Matrix::multiply(fMatrix4 matrix, dVector4 vector) // could be optimized?
{
    dVector4 result;

    result.x = matrix.matrix[0][0] * vector.x + matrix.matrix[0][1] * vector.y + matrix.matrix[0][2] * vector.z + matrix.matrix[0][3] * vector.w;
    result.y = matrix.matrix[1][0] * vector.x + matrix.matrix[1][1] * vector.y + matrix.matrix[1][2] * vector.z + matrix.matrix[1][3] * vector.w;
    result.z = matrix.matrix[2][0] * vector.x + matrix.matrix[2][1] * vector.y + matrix.matrix[2][2] * vector.z + matrix.matrix[2][3] * vector.w;
    result.w = matrix.matrix[3][0] * vector.x + matrix.matrix[3][1] * vector.y + matrix.matrix[3][2] * vector.z + matrix.matrix[3][3] * vector.w;

    return result;
}